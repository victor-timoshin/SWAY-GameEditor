#include "../Inc/SceneGraphPanel.h"
#include "../Inc/SceneGraphTreeCtrl.h"
#include "../Inc/MainFrame.h"

/// <summary>Конструктор класса.</summary>
/// <param name="parent">Указатель на родительское окно.</param>
/// <param name="id">Уникальный идентификатор панели.</param>
SceneGraphPanel::SceneGraphPanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
	, parentWindow(static_cast<MainFrame*>(parent))
{
	imageList = NULL;
	imageList = new wxImageList(16, 16, true);
	imageList->Add(wxIcon("Assets/Art/mesh.ico", wxBITMAP_TYPE_ICO));
	imageList->Add(wxIcon("Assets/Art/submesh.ico", wxBITMAP_TYPE_ICO));
	imageList->Add(wxIcon("Assets/Art/light.ico", wxBITMAP_TYPE_ICO));
	imageList->Add(wxIcon("Assets/Art/node.ico", wxBITMAP_TYPE_ICO));
	imageList->Add(wxIcon("Assets/Art/camera.ico", wxBITMAP_TYPE_ICO));

	Scene::ICameraBase* activeCamera = parentWindow->GetSceneGraph()->CreateCamera("camera");
	activeCamera->LookAt();
	activeCamera->Perspective(CAMERA_FOV, SCREEN_WIDTH / SCREEN_HEIGHT, CAMERA_ZNEAR, CAMERA_ZFAR);
	activeCamera->SetPosition(Math::Vector3(0.0f, 0.0f, 0.0f));
	activeCamera->Move(Math::Vector3(0.0f, 0.0f, 10.0f));
	activeCamera->Rotation(0.0f, 0.0f, 0.0f);

	sceneGraphTreeCtrl = new SceneGraphTreeCtrl(this, ID_TREECTRL);
	sceneGraphTreeCtrl->AssignImageList(imageList);
	sceneGraphTreeCtrl->SetWindowStyle(wxTR_DEFAULT_STYLE | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxSIMPLE_BORDER);
	//sceneGraphTreeCtrl->SetWindowStyle(wxTR_DEFAULT_STYLE | wxTR_EDIT_LABELS);
	//sceneGraphTreeCtrl->Expand(sceneGraphTreeCtrl->GetRootItem());

	wxBoxSizer* verticalBoxSizer = new wxBoxSizer(wxVERTICAL);
	verticalBoxSizer->Add(sceneGraphTreeCtrl, 1, wxEXPAND, 0);
	verticalBoxSizer->Fit(this);
	verticalBoxSizer->SetSizeHints(this);

	SetAutoLayout(true);
	SetSizer(verticalBoxSizer);
}

/// <summary>Деструктор класса.</summary>
SceneGraphPanel::~SceneGraphPanel(void)
{
}

void SceneGraphPanel::Rebuild(void)
{
}

InspectorPanel* SceneGraphPanel::GetInspectorPanel(void)
{
	return parentWindow->GetInspectorPanel();
}