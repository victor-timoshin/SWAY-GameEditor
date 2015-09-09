#include "../Inc/SceneGraphTreeCtrl.h"
#include "../Inc/MainFrame.h"

IMPLEMENT_DYNAMIC_CLASS(SceneGraphTreeCtrl, wxTreeCtrl);

BEGIN_EVENT_TABLE(SceneGraphTreeCtrl, wxTreeCtrl)
	EVT_TREE_SEL_CHANGED(ID_TREECTRL, SceneGraphTreeCtrl::OnSelChanged)
	EVT_TREE_ITEM_ACTIVATED(ID_TREECTRL, SceneGraphTreeCtrl::OnItemActivated)
	EVT_TREE_ITEM_MENU(ID_TREECTRL, SceneGraphTreeCtrl::OnContextMenu)
	EVT_TREE_BEGIN_LABEL_EDIT(ID_TREECTRL, SceneGraphTreeCtrl::OnBeginLabelEdit)
	EVT_TREE_END_LABEL_EDIT(ID_TREECTRL, SceneGraphTreeCtrl::OnEndLabelEdit)
	EVT_MENU(ID_TREE_MENU_ITEM_ADDNODE_CHILD, SceneGraphTreeCtrl::OnAddNodeChild)
	EVT_MENU(ID_TREE_MENU_ITEM_ADDNODE_SIBLING, SceneGraphTreeCtrl::OnAddNodeSibling)
	EVT_MENU(ID_TREE_MENU_ITEM_DELNODE, SceneGraphTreeCtrl::OnDelNode)
	EVT_MENU(ID_TREE_MENU_ITEM_RENAME, SceneGraphTreeCtrl::OnRename)
END_EVENT_TABLE()

/// <summary>Конструктор класса.</summary>
/// <param name="parent">Указатель на родительское окно.</param>
/// <param name="id">Уникальный идентификатор дерева.</param>
SceneGraphTreeCtrl::SceneGraphTreeCtrl(wxWindow* parent, wxWindowID id) : wxTreeCtrl(parent, id)
{
	wxTreeItemId rootItemId = AddRoot(MainFrame::GetInstancePtr()->GetSceneGraph()->GetRootSceneNode()->GetNodeName().c_str(),
		BROWSERTREEICON::EBTI_NODE, 0, new SceneGraphTreeItemData(MainFrame::GetInstancePtr()->GetSceneGraph()->GetRootSceneNode()));
	bool hasChildren = HasChildren(rootItemId);

	selectedItemData = NULL;
}

/// <summary>Деструктор класса.</summary>
SceneGraphTreeCtrl::~SceneGraphTreeCtrl(void)
{
}

void SceneGraphTreeCtrl::OnSelChanged(wxTreeEvent& event)
{
	wxTreeItemId id = event.GetItem();
	if (id.IsOk())
	{
		selectedItemData = (SceneGraphTreeItemData*)GetItemData(id);
		MainFrame::GetInstancePtr()->GetInspectorPanel()->SetSceneNode(selectedItemData->GetNode());
	}
}

void SceneGraphTreeCtrl::AddChildSceneNode(const wxTreeItemId& parent, const wxString& name)
{
	Scene::ISceneComponentBase* component = MainFrame::GetInstancePtr()->GetSceneGraph()->CreateBox(wxString::Format("%s_component", name));
	Scene::ISceneNodeBase* node = MainFrame::GetInstancePtr()->GetSceneGraph()->GetRootSceneNode()->CreateChild(wxString::Format("%s_node", name));
	node->Attach(component);

	MainFrame::GetInstancePtr()->GetRenderSystem()->SetRenderableComponent(component);

	AppendItem(parent, node->GetNodeName().c_str(), -1, -1, new SceneGraphTreeItemData(node));
}

void SceneGraphTreeCtrl::OnContextMenu(wxTreeEvent& event)
{
	if (GetEditControl() == NULL)
	{
		wxMenu menu;
		menu.Append(ID_TREE_MENU_ITEM_ADDNODE_CHILD, wxT("Add Child"));
		menu.Append(ID_TREE_MENU_ITEM_ADDNODE_SIBLING, wxT("Add Sibling"));
		menu.Append(ID_TREE_MENU_ITEM_DELNODE, wxT("Delete"));
		menu.AppendSeparator();
		menu.Append(ID_TREE_MENU_ITEM_RENAME, wxT("Rename"));

		PopupMenu(&menu, event.GetPoint());
	}
	else
		event.Skip();
}

void SceneGraphTreeCtrl::OnAddNodeChild(wxCommandEvent& WXUNUSED(event))
{
	wxTreeItemId item = GetFocusedItem();
	AddChildSceneNode(item, wxT("Test"));
}

void SceneGraphTreeCtrl::OnAddNodeSibling(wxCommandEvent& WXUNUSED(event))
{
}

void SceneGraphTreeCtrl::OnDelNode(wxCommandEvent& WXUNUSED(event))
{
}

void SceneGraphTreeCtrl::OnRename(wxCommandEvent& WXUNUSED(event))
{
	wxTreeItemId item = GetFocusedItem();
	wxString text = GetItemText(item);

	text = wxGetTextFromUser(wxT("New name: "), wxEmptyString, text, this);
	if (!text.empty())
		SetItemText(item, text);

	(void)EditLabel(item);
}

void SceneGraphTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
}

void SceneGraphTreeCtrl::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
}

void SceneGraphTreeCtrl::OnEndLabelEdit(wxTreeEvent& event)
{
	event.Allow();
}

Scene::ISceneNodeBase* SceneGraphTreeCtrl::GetSelectedItem(void)
{
	if (selectedItemData != NULL)
		return selectedItemData->GetNode();

	return NULL;
}