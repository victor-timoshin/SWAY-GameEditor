#include "../../Inc/Inspector/InspectorPropertyGridPage.h"
//#include "../../Inc/Inspector/InspectorPropertyController.h"

WX_PG_IMPLEMENT_PROPERTY_CLASS(nsVector3Property, wxPGProperty, Vector3, const Vector3&, TextCtrl);
WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(Vector3);

nsVector3Property::nsVector3Property(const wxString& label, const wxString& name, const Math::Vector3& value) : wxPGProperty(label, name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild(new wxFloatProperty(wxT("x"), wxPG_LABEL, value._x));
	AddPrivateChild(new wxFloatProperty(wxT("y"), wxPG_LABEL, value._y));
	AddPrivateChild(new wxFloatProperty(wxT("z"), wxPG_LABEL, value._z));
}

nsVector3Property::~nsVector3Property()
{
}

void nsVector3Property::RefreshChildren(void)
{
	if (!GetChildCount()) return;

	const Vector3& vector = Vector3RefFromVariant(m_value);
	Item(0)->SetValue(vector._x);
	Item(1)->SetValue(vector._y);
	Item(2)->SetValue(vector._z);
}

wxVariant nsVector3Property::ChildChanged(wxVariant& thisValue, int childIndex, wxVariant& childValue) const
{
	Vector3 vector;
	vector << thisValue;
	switch (childIndex)
	{
	case 0: vector._x = childValue.GetDouble(); break;
	case 1: vector._y = childValue.GetDouble(); break;
	case 2: vector._z = childValue.GetDouble(); break;
	}
	wxVariant newVariant;
	newVariant << vector;
	return newVariant;
}






BEGIN_EVENT_TABLE(InspectorPropertyGridPage, wxPropertyGridPage)
	EVT_PG_CHANGED(-1, InspectorPropertyGridPage::OnPropertyChanged)
END_EVENT_TABLE()

InspectorPropertyGridPage::InspectorPropertyGridPage(Scene::ISceneNodeBase* node/*InspectorPropertyController* ctrl*/)
	: sceneNode(node) //: propertyCtrl(ctrl)
{
}

InspectorPropertyGridPage::~InspectorPropertyGridPage(void)
{
}

void InspectorPropertyGridPage::Populate(void)
{
	CreateGeneralCategory();
	CreateTransformCategory();
}

void InspectorPropertyGridPage::CreateGeneralCategory(void)
{
	wxPGProperty* propertyCategoryID = Append(new wxPropertyCategory("General"));
	nameID = AppendIn(propertyCategoryID, new wxStringProperty(wxT("Name"), wxPG_LABEL, "mainCamera"));
	SetPropertyHelpString(nameID, "Unique name for the camera");

	wxPGChoices typeChoices;
	typeChoices.Add(wxT("Cube"), 1);
	typeChoices.Add(wxT("Sphere"), 2);
	typeChoices.Add(wxT("Mesh"), 3);

	typeID = AppendIn(propertyCategoryID, new wxEnumProperty(wxT("Type"), wxPG_LABEL, typeChoices));
}

void InspectorPropertyGridPage::CreateTransformCategory(void)
{
	if (sceneNode)
	{
		wxPGProperty* csprop = Append(new wxPropertyCategory(wxT("Transform"), wxT("transform")));
		positionID = AppendIn(csprop, new nsVector3Property(wxT("Position"), wxT("position"), sceneNode->GetPosition()));
		scaleID = AppendIn(csprop, new nsVector3Property(wxT("Scale"), wxT("scale"), sceneNode->GetScale()));
		csprop->SetExpanded(false);
	}
}

void InspectorPropertyGridPage::OnPropertyChanged(wxPropertyGridEvent& event)
{
	wxPGProperty* property = event.GetProperty();
	if (property == nameID)
	{
		sceneNode->SetNodeName(std::string(property->GetValue().GetString().c_str()));
	}
	else if (property == positionID)
	{
		Vector3 val = Vector3RefFromVariant(property->GetValue());
		sceneNode->SetPosition(val._x, val._y, val._z);
	}
	else if (property == scaleID)
	{
		Vector3 val = Vector3RefFromVariant(property->GetValue());
		sceneNode->SetScale(val._x, val._y, val._z);
	}
}