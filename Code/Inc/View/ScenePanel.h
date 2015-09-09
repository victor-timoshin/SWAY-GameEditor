#ifndef SCENEPANEL_H
#define SCENEPANEL_H

#include "../View/ViewContext.h"
#include "../StdAfx.h"

class MainFrame;
class ScenePanel : public wxPanel
{
	DECLARE_EVENT_TABLE()

public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор панели.</param>
	ScenePanel(wxWindow* parent, wxWindowID id);

	/// <summary>Деструктор класса.</summary>
	~ScenePanel(void);

	void CreateRenderDevice(void);

	void SetSceneGraph(Scene::ISceneGraphBase* scene) { sceneGraph = scene; }
	void SetRenderSystem(Render::IRenderSystemBase* render) { renderSystem = render; }

#pragma region WX Event callbacks

	void OnSize(wxSizeEvent& event);

	void OnPaint(wxPaintEvent& event);

	void OnEraseBackground(wxEraseEvent& event);
	void OnRenderTimer(wxTimerEvent& event);

	void OnMouse(wxMouseEvent& event);
	void OnMouseDown(wxMouseEvent& event);
	void OnMouseMotion(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);

#pragma endregion

	void DrawGrid(void) { }
	void DrawAxis(void) { }

	void SetEnableGrid(bool) { }
	void SetEnableAxis(bool) { }

private:
	ViewContext viewContext;

	Scene::ISceneGraphBase* sceneGraph;
	Render::IRenderSystemBase* renderSystem;

	wxTimer	timer;
	wxPoint prevPosition;
};

#endif // SCENEPANEL_H