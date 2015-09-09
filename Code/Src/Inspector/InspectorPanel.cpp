#include "../../Inc/Inspector/InspectorPanel.h"
#include "../../Inc/Inspector/InspectorPropertyGridPage.h"

/// <summary>Конструктор класса.</summary>
/// <param name="parent">Указатель на родительское окно.</param>
/// <param name="id">Уникальный идентификатор панели.</param>
InspectorPanel::InspectorPanel(wxWindow* parent, wxWindowID id, const wxPoint& position, const wxSize& size, long style) : wxPanel(parent, id, position, size, style)
{
	notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	propertyManager = new wxPropertyGridManager(notebook, wxID_ANY);
	propertyManager->SetExtraStyle(wxPG_EX_NATIVE_DOUBLE_BUFFERING | wxPG_EX_HELP_AS_TOOLTIPS);

	notebook->AddPage(propertyManager, "Properties", false);
	notebook->SetPageToolTip(0, "first page");

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(notebook, 1, wxALL | wxEXPAND, 0);

	SetSizer(topSizer);
}

void InspectorPanel::SetSceneNode(Scene::ISceneNodeBase* node) {
	sceneNode = node;

	propertyManager->Clear();

	InspectorPropertyGridPage* pageGrid = new InspectorPropertyGridPage(sceneNode);
	propertyManager->AddPage(wxEmptyString, wxPG_NULL_BITMAP, pageGrid);

	pageGrid->Populate();

	propertyManager->Refresh();
}