#ifndef SCENEGRAPHPANEL_H
#define SCENEGRAPHPANEL_H

#include "Inspector/InspectorPanel.h"
#include "StdAfx.h"

class MainFrame;
class SceneGraphPanel : public wxPanel
{
public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор панели.</param>
	SceneGraphPanel(wxWindow* parent, wxWindowID id = wxID_ANY);

	/// <summary>Деструктор класса.</summary>
	~SceneGraphPanel(void);

	void Rebuild(void);

	InspectorPanel* GetInspectorPanel(void);
	Scene::ISceneGraphBase* GetSceneGraph(void) { return sceneGraph; }
	Render::IRenderSystemBase* GetRenderSystem(void) { return renderSystem; }

private:
	MainFrame* parentWindow;
	wxTreeCtrl* sceneGraphTreeCtrl;
	wxImageList* imageList;

	Scene::ISceneGraphBase* sceneGraph;
	Render::IRenderSystemBase* renderSystem;
};

#endif // SCENEGRAPHPANEL_H