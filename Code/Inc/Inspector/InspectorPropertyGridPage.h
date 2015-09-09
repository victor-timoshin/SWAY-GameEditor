#ifndef INSPECTORPROPERTYGRIDPAGE_H
#define INSPECTORPROPERTYGRIDPAGE_H

#include "../StdAfx.h"

using namespace Math;

class MyVariant : public wxVariantData {
	Vector3 m_vector3;
public:
	MyVariant(Vector3 v) : wxVariantData(), m_vector3(v) { }

	bool Eq(wxVariantData &data) const {
		MyVariant *value_ptr = dynamic_cast<MyVariant*>(&data);
		return (value_ptr != 0) && ((*value_ptr).m_vector3 == m_vector3);
	}
	wxString GetType() const { return wxString("MyVariant"); }

	Vector3 GetVector3() const { return m_vector3; }
};

WX_PG_DECLARE_VARIANT_DATA(Vector3);

class nsVector3Property : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(nsVector3Property)
public:
	nsVector3Property(const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL, const Vector3& data = Vector3());
	virtual ~nsVector3Property();

	virtual wxVariant ChildChanged(wxVariant& thisValue, int childIndex, wxVariant& childValue) const;

	virtual void RefreshChildren(void);
};

//class InspectorPropertyController;
class InspectorPropertyGridPage : public wxPropertyGridPage
{
	DECLARE_EVENT_TABLE()

public:
	InspectorPropertyGridPage(Scene::ISceneNodeBase* node/*InspectorPropertyController* ctrl*/);

	~InspectorPropertyGridPage(void);

	void Populate(void);

protected:
	void CreateGeneralCategory(void);

	void CreateTransformCategory(void);

	void OnPropertyChanged(wxPropertyGridEvent& event);

private:
	//InspectorPropertyController* propertyCtrl;
	Scene::ISceneNodeBase* sceneNode;
	wxPGProperty* nameID;
	wxPGProperty* typeID;

	wxPGProperty* positionID;
	wxPGProperty* scaleID;
};

#endif