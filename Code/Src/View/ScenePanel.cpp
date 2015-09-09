#include "../../Inc/View/ScenePanel.h"
#include "../../Inc/MainFrame.h"

const long ID_RENDERTIMER = wxNewId();

BEGIN_EVENT_TABLE(ScenePanel, wxPanel)
	EVT_ERASE_BACKGROUND(ScenePanel::OnEraseBackground)
	EVT_TIMER(ID_RENDERTIMER, ScenePanel::OnRenderTimer)

	EVT_SIZE(ScenePanel::OnSize)
	EVT_PAINT(ScenePanel::OnPaint)
	EVT_LEFT_DOWN(ScenePanel::OnMouseDown)
	EVT_MIDDLE_DOWN(ScenePanel::OnMouseDown)
	EVT_RIGHT_DOWN(ScenePanel::OnMouseDown)
	EVT_MOTION(ScenePanel::OnMouseMotion)
	EVT_MOUSEWHEEL(ScenePanel::OnMouseWheel)
END_EVENT_TABLE()

/// <summary>Конструктор класса.</summary>
/// <param name="parent">Указатель на родительское окно.</param>
/// <param name="id">Уникальный идентификатор панели.</param>
ScenePanel::ScenePanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
	, timer(this, ID_RENDERTIMER)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	if (timer.IsRunning())
		timer.Stop();

	timer.Start(10);
}

/// <summary>Деструктор класса.</summary>
ScenePanel::~ScenePanel(void)
{
}

void ScenePanel::CreateRenderDevice(void)
{
	if (renderSystem->CreateDevice(GetHWND()))
		renderSystem->CreateMaterial("../../../Assets/Shaders/basic.vs", "../../../Assets/Shaders/basic.fs");
}

void ScenePanel::OnSize(wxSizeEvent& WXUNUSED(event))
{
	int width, height;
	GetClientSize(&width, &height);

	if (renderSystem)
		renderSystem->GetDevice()->SetViewport(width, height);
}

void ScenePanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC deviceContext(this);
}

void ScenePanel::OnEraseBackground(wxEraseEvent& event)
{
}

void ScenePanel::OnRenderTimer(wxTimerEvent& WXUNUSED(event))
{
	if (renderSystem && sceneGraph)
	{
		renderSystem->GetDevice()->MakeCurrentContext();
		renderSystem->FrameDrawed(sceneGraph->GetActiveCamera());
	}
}

void ScenePanel::OnMouse(wxMouseEvent& WXUNUSED(event))
{
	int width, height;
	GetClientSize(&width, &height);
}

void ScenePanel::OnMouseDown(wxMouseEvent& event)
{
	prevPosition = event.GetPosition();
	event.Skip();
}

void ScenePanel::OnMouseMotion(wxMouseEvent& event)
{
	if (event.Dragging())
	{
		wxPoint position = event.GetPosition();
		wxPoint change = position - prevPosition;

		if (event.LeftIsDown())
		{
			float yaw = -(float)change.x / (event.ShiftDown() ? 50.0f : 10.0f);
			float pitch = -(float)change.y / (event.ShiftDown() ? 50.0f : 10.0f);

			sceneGraph->GetActiveCamera()->Rotation(Math::DegreesToRadians(yaw), Math::DegreesToRadians(pitch), 0.0f);
		}
		else if (event.MiddleIsDown())
		{
		}
		else if (event.RightIsDown())
		{
		}

		prevPosition = position;
	}
}

void ScenePanel::OnMouseWheel(wxMouseEvent& WXUNUSED(event))
{
}