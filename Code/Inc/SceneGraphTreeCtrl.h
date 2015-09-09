#ifndef SCENEGRAPHTREECTRL_H
#define SCENEGRAPHTREECTRL_H

#include "../Inc/SceneGraphPanel.h"
#include "../Inc/SceneGraphTreeItemData.h"
#include "StdAfx.h"

class SceneGraphTreeCtrl : public wxTreeCtrl
{
	DECLARE_DYNAMIC_CLASS(SceneGraphTreeCtrl)
	DECLARE_EVENT_TABLE()

public:
	/// <summary>Конструктор класса.</summary>
	SceneGraphTreeCtrl(void) { }

	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор дерева.</param>
	SceneGraphTreeCtrl(wxWindow* parent, wxWindowID id = ID_TREECTRL);

	/// <summary>Деструктор класса.</summary>
	~SceneGraphTreeCtrl(void);

	void OnSelChanged(wxTreeEvent& event);

	void AddChildSceneNode(const wxTreeItemId& parent, const wxString& name);

	void OnContextMenu(wxTreeEvent& event);

	void OnAddNodeChild(wxCommandEvent& event);

	void OnAddNodeSibling(wxCommandEvent& event);

	void OnDelNode(wxCommandEvent& event);

	void OnRename(wxCommandEvent& event);

	void OnItemActivated(wxTreeEvent& event);

	void OnBeginLabelEdit(wxTreeEvent& event);

	void OnEndLabelEdit(wxTreeEvent& event);

	Scene::ISceneNodeBase* GetSelectedItem(void);

private:
	SceneGraphTreeItemData* selectedItemData;
};

#endif // SCENEGRAPHTREECTRL_H