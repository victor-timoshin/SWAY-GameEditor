#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../Inc/SceneGraphPanel.h"
#include "../Inc/Inspector/InspectorPanel.h"
#include "../Inc/View/ScenePanel.h"
#include "../Inc/TransformPanel.h"
#include "../Inc/ConsolePanel.h"
#include "../Inc/AssetBrowserCtrl.h"
#include "StdAfx.h"

class MainFrame : public wxFrame, public Utils::TSingleton<MainFrame>
{
	DECLARE_EVENT_TABLE()

public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор фрейма.</param>
	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString,
		const wxPoint& position = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE);

	/// <summary>Деструктор класса.</summary>
	~MainFrame(void);

	Render::IRenderSystemBase* GetRenderSystem(void) { return renderSystem; }

	Scene::ISceneGraphBase* GetSceneGraph(void) { return sceneGraph; }

	SceneGraphPanel* GetBrowserPanel(void) { return browserPanel; }

	InspectorPanel* GetInspectorPanel(void) { return inspectorPanel; }

	TransformPanel* GetTransformPanel(void) { return transformPanel; }

protected:
	void OnToggleLogWindow(wxCommandEvent& event);

	void OnToggleLogWindowUpdateUI(wxUpdateUIEvent& event);

	bool GetPaneVisibility(wxString name);

	void TogglePaneVisibility(wxString name);

	wxWindow* CreateDesignerWindow(wxWindow* parent);

	wxWindow* CreateBrowserPanel(wxWindow* parent);

	wxWindow* CreateInspectorPanel(wxWindow* parent);

	wxWindow* CreateTransformPanel(wxWindow* parent);

	wxWindow* CreateConsole(wxWindow* parent);

private:
	wxAuiManager* auiManager;
	wxAuiNotebook* auiNotebook;
	wxAuiToolBar* auiToolBar;

	Render::IRenderSystemBase* renderSystem;
	Scene::ISceneGraphBase* sceneGraph;

	SceneGraphPanel* browserPanel;
	InspectorPanel* inspectorPanel;
	TransformPanel* transformPanel;
};

#endif