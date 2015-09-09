#ifndef TRANSFORMPANEL_H
#define TRANSFORMPANEL_H

#include "StdAfx.h"

class TransformPanel : public wxPanel
{
	DECLARE_EVENT_TABLE()

public:
	/// <summary>����������� ������.</summary>
	/// <param name="parent">��������� �� ������������ ����.</param>
	/// <param name="id">���������� ������������� ������.</param>
	TransformPanel(wxWindow* parent, wxWindowID id = wxID_ANY);

	/// <summary>���������� ������.</summary>
	~TransformPanel(void);

	wxBoxSizer* BuildViewMatrix(void);
	wxBoxSizer* BuildProjectionMatrix(void);

	void UpdateMatrices(void);

	void SetSceneGraph(Scene::ISceneGraphBase* scene) { sceneGraph = scene; }

	void OnIdle(wxIdleEvent& WXUNUSED(event));

protected:
	void OnSliderMouseWheel(wxMouseEvent& event);

	void OnPositionXChanged(wxSpinDoubleEvent& event);
	void OnPositionYChanged(wxSpinDoubleEvent& event);
	void OnPositionZChanged(wxSpinDoubleEvent& event);

private:
	wxBoxSizer* CreateGroupControl(wxObjectEventFunction func, const wxString& label);

private:
	Scene::ISceneGraphBase* sceneGraph;

	wxStaticText* viewMatrix[16];
	wxStaticText* projectionMatrix[16];
};

#endif // TRANSFORMPANEL_H