#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "../../Inc/Inspector/InspectorPropertyGridPage.h"
#include "../StdAfx.h"

class InspectorPanel : public wxPanel
{
public:
	/// <summary>����������� ������.</summary>
	/// <param name="parent">��������� �� ������������ ����.</param>
	/// <param name="id">���������� ������������� ������.</param>
	InspectorPanel(wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& position = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);

	/// <summary>���������� ������.</summary>
	~InspectorPanel(void) { }

	void SetSceneNode(Scene::ISceneNodeBase* node);

protected:

private:
	wxAuiNotebook* notebook;
	wxPropertyGridManager* propertyManager;

	Scene::ISceneNodeBase* sceneNode;
};

#endif // INSPECTORPANEL_H