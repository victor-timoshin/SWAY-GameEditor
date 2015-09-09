#include "../Inc/MainFrame.h"
#include "../Inc/MainMenu.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_TOGGLE_LOGWINDOW, MainFrame::OnToggleLogWindow)
	EVT_UPDATE_UI(ID_TOGGLE_LOGWINDOW, MainFrame::OnToggleLogWindowUpdateUI)
END_EVENT_TABLE()

/// <summary>Конструктор класса.</summary>
/// <param name="parent">Указатель на родительское окно.</param>
/// <param name="id">Уникальный идентификатор фрейма.</param>
MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& position, const wxSize& size, long style) : wxFrame(parent, id, title, position, size, style)
{
	SetTitle("SWAY-GameEditor");

	SetMenuBar(new MainMenu());

	CreateStatusBar(3);
	SetStatusBarPane(0);
	int widths[3] = { -1, -1, 300 };
	SetStatusWidths(sizeof(widths) / sizeof(int), widths);

	sceneGraph = Scene::RegisterSceneGraph();

	renderSystem = Render::RegisterRenderSystem();
	renderSystem->Initialize("GapiOpenGL_Win32_Debug");

	wxWindow* designerCtrl = CreateDesignerWindow(this);
	wxWindow* browserCtrl = CreateBrowserPanel(this);
	wxWindow* inspectorCtrl = CreateInspectorPanel(this);
	wxWindow* transformCtrl = CreateTransformPanel(this);
	AssetBrowserCtrl* contentCtrl = new AssetBrowserCtrl(this);
	contentCtrl->OpenFolder(("C:\\Users\\Bonus\\Documents\\GitHub\\SWAY-GameEditor\\Build\\Windows\\Debug\\Assets\\Images"));

	wxWindow* consoleCtrl = CreateConsole(this);

	wxAuiPaneInfo auiPaneInfo;
	auiManager = new wxAuiManager(this);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name(wxT("editor"));
	auiPaneInfo.Caption("Editor").CaptionVisible(false);
	auiPaneInfo.CentrePane();
	auiPaneInfo.CloseButton(false).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(true);
	auiPaneInfo.PaneBorder(false);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Dock().DockFixed().Center();
	auiPaneInfo.BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false);
	auiPaneInfo.Resizable().Movable(false).Floatable(false);
	auiManager->AddPane(designerCtrl, auiPaneInfo);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name(wxT("tree"));
	auiPaneInfo.Caption("Object Tree").CaptionVisible(true);
	auiPaneInfo.CloseButton(false).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(true);
	auiPaneInfo.PaneBorder(true);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Dock().DockFixed(false).Left();
	auiPaneInfo.BottomDockable(false).TopDockable(false).LeftDockable(true).RightDockable(true);
	auiPaneInfo.Resizable().Movable(true).Floatable(true);
	auiPaneInfo.FloatingSize(wxSize(300, 400));
	auiPaneInfo.BestSize(wxSize(300, -1));
	auiPaneInfo.Row(1);
	auiPaneInfo.Layer(0);
	auiManager->AddPane(browserCtrl, auiPaneInfo);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name(wxT("inspector"));
	auiPaneInfo.Caption("Object Properties").CaptionVisible(true);
	auiPaneInfo.CloseButton(false).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(true);
	auiPaneInfo.PaneBorder(true);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Dock().DockFixed(false).Right();
	auiPaneInfo.BottomDockable(false).TopDockable(false).LeftDockable(true).RightDockable(true);
	auiPaneInfo.Resizable().Movable(true).Floatable(true);
	auiPaneInfo.FloatingSize(wxSize(300, 400));
	auiPaneInfo.BestSize(wxSize(300, -1));
	auiPaneInfo.Row(1);
	auiPaneInfo.Layer(0);
	auiManager->AddPane(inspectorCtrl, auiPaneInfo);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name("transform");
	auiPaneInfo.Caption("Transform").CaptionVisible(true);
	auiPaneInfo.CloseButton(true).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(true);
	auiPaneInfo.PaneBorder(true);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Float();
	auiPaneInfo.FloatingSize(600, 400);
	auiPaneInfo.FloatingPosition(100, 100);
	auiPaneInfo.MinSize(-1, 192);
	auiManager->AddPane(transformCtrl, auiPaneInfo);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name("content");
	auiPaneInfo.Caption("Content").CaptionVisible(true);
	auiPaneInfo.CloseButton(true).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(true);
	auiPaneInfo.PaneBorder(true);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Float();
	auiPaneInfo.FloatingSize(600, 400);
	auiPaneInfo.FloatingPosition(100, 100);
	auiPaneInfo.MinSize(-1, 192);
	auiManager->AddPane(contentCtrl, auiPaneInfo);

	auiPaneInfo.DefaultPane();
	auiPaneInfo.Name("console");
	auiPaneInfo.Caption("Console").CaptionVisible(true);
	auiPaneInfo.CloseButton(true).MaximizeButton(false).MinimizeButton(false).PinButton(false);
	auiPaneInfo.Show(false);
	auiPaneInfo.PaneBorder(true);
	auiPaneInfo.Gripper(false);
	auiPaneInfo.Float();
	auiPaneInfo.FloatingSize(600, 400);
	auiPaneInfo.FloatingPosition(100, 100);
	auiPaneInfo.MinSize(-1, 192);
	auiManager->AddPane(consoleCtrl, auiPaneInfo);

	auiManager->SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_DRAG);
	auiManager->Update();
}

/// <summary>Деструктор класса.</summary>
MainFrame::~MainFrame(void)
{
	SAFE_DELETE(renderSystem);

	sceneGraph->Clear();
	SAFE_DELETE(sceneGraph);

	auiManager->UnInit();
}

void MainFrame::OnToggleLogWindow(wxCommandEvent& WXUNUSED(event))
{
	TogglePaneVisibility("console");
}

void MainFrame::OnToggleLogWindowUpdateUI(wxUpdateUIEvent& event)
{
	event.Check(GetPaneVisibility("console"));
}

bool MainFrame::GetPaneVisibility(wxString name)
{
	wxAuiPaneInfoArray& panes = auiManager->GetAllPanes();
	for (size_t i = 0; i < panes.GetCount(); ++i)
	{
		if (panes.Item(i).name == name)
			return panes.Item(i).IsShown();
	}

	return false;
}

void MainFrame::TogglePaneVisibility(wxString name)
{
	wxAuiPaneInfoArray& panes = auiManager->GetAllPanes();
	for (size_t i = 0; i < panes.GetCount(); ++i)
	{
		if (panes.Item(i).name == name)
		{
			panes.Item(i).Show(!panes.Item(i).IsShown());
			auiManager->Update();
			break;
		}
	}
}

wxWindow* MainFrame::CreateDesignerWindow(wxWindow* parent)
{
	long style = 0;
	wxConfigBase* config = wxConfigBase::Get();
	config->Read("/mainframe/editor/notebook_style", &style, wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_TOP);

	auto notebook = new wxAuiNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style);
	auto canvas = new ScenePanel(notebook, wxID_ANY);
	canvas->SetSceneGraph(sceneGraph);
	canvas->SetRenderSystem(renderSystem);
	canvas->CreateRenderDevice();

	notebook->AddPage(canvas, "Designer", false, NULL);
	notebook->SetSelection(0);

	return notebook;
}

wxWindow* MainFrame::CreateBrowserPanel(wxWindow* parent)
{
	browserPanel = new SceneGraphPanel(parent, wxID_ANY);
	return browserPanel;
}

wxWindow* MainFrame::CreateInspectorPanel(wxWindow* parent)
{
	inspectorPanel = new InspectorPanel(parent, wxID_ANY);
	return inspectorPanel;
}

wxWindow* MainFrame::CreateTransformPanel(wxWindow* parent)
{
	transformPanel = new TransformPanel(parent, wxID_ANY);
	transformPanel->SetSceneGraph(sceneGraph);

	return transformPanel;
}

wxWindow* MainFrame::CreateConsole(wxWindow* parent)
{
	return new ConsolePanel(parent, wxID_ANY);
}