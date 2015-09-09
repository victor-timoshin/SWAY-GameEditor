#include "../Inc/TransformPanel.h"
#include <sstream>
#include <iomanip>

BEGIN_EVENT_TABLE(TransformPanel, wxPanel)
	EVT_IDLE(TransformPanel::OnIdle)
END_EVENT_TABLE()

TransformPanel::TransformPanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
	wxBoxSizer* verticalBoxSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBox* itemStaticBox = new wxStaticBox(this, wxID_ANY, "Transform");
	wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxVERTICAL);
	verticalBoxSizer->Add(itemStaticBoxSizer, 0, wxGROW | wxALL, 5);

	verticalBoxSizer->Add(BuildViewMatrix(), 0, wxALL | wxEXPAND, 5);
	verticalBoxSizer->Add(BuildProjectionMatrix(), 0, wxALL | wxEXPAND, 5);

	itemStaticBoxSizer->Add(CreateGroupControl(wxSpinDoubleEventHandler(TransformPanel::OnPositionXChanged), "X:"), 0, wxALL | wxEXPAND, 5);
	itemStaticBoxSizer->Add(CreateGroupControl(wxSpinDoubleEventHandler(TransformPanel::OnPositionYChanged), "Y:"), 0, wxALL | wxEXPAND, 5);
	itemStaticBoxSizer->Add(CreateGroupControl(wxSpinDoubleEventHandler(TransformPanel::OnPositionZChanged), "Z:"), 0, wxALL | wxEXPAND, 5);

	SetSizer(verticalBoxSizer);
}

TransformPanel::~TransformPanel(void)
{
}

wxBoxSizer* TransformPanel::BuildViewMatrix(void)
{
	wxBoxSizer* verticalBoxSizer = new wxBoxSizer(wxVERTICAL);

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		viewMatrix[0] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[0], 1, wxALL | wxEXPAND, 5);
		viewMatrix[1] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[1], 1, wxALL | wxEXPAND, 5);
		viewMatrix[2] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[2], 1, wxALL | wxEXPAND, 5);
		viewMatrix[3] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[3], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		viewMatrix[4] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[4], 1, wxALL | wxEXPAND, 5);
		viewMatrix[5] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[5], 1, wxALL | wxEXPAND, 5);
		viewMatrix[6] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[6], 1, wxALL | wxEXPAND, 5);
		viewMatrix[7] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[7], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		viewMatrix[8] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[8], 1, wxALL | wxEXPAND, 5);
		viewMatrix[9] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[9], 1, wxALL | wxEXPAND, 5);
		viewMatrix[10] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[10], 1, wxALL | wxEXPAND, 5);
		viewMatrix[11] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[11], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		viewMatrix[12] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[12], 1, wxALL | wxEXPAND, 5);
		viewMatrix[13] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[13], 1, wxALL | wxEXPAND, 5);
		viewMatrix[14] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[14], 1, wxALL | wxEXPAND, 5);
		viewMatrix[15] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(viewMatrix[15], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	return verticalBoxSizer;
}

wxBoxSizer* TransformPanel::BuildProjectionMatrix(void)
{
	wxBoxSizer* verticalBoxSizer = new wxBoxSizer(wxVERTICAL);

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		projectionMatrix[0] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[0], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[1] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[1], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[2] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[2], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[3] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[3], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		projectionMatrix[4] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[4], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[5] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[5], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[6] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[6], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[7] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[7], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		projectionMatrix[8] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[8], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[9] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[9], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[10] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[10], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[11] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[11], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	{
		wxBoxSizer* horizontalBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
		projectionMatrix[12] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[12], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[13] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[13], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[14] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[14], 1, wxALL | wxEXPAND, 5);
		projectionMatrix[15] = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, 0);
		horizontalBoxSizer4->Add(projectionMatrix[15], 1, wxALL | wxEXPAND, 5);

		verticalBoxSizer->Add(horizontalBoxSizer4, 1, wxALL | wxEXPAND, 5);
	}

	return verticalBoxSizer;
}

void TransformPanel::UpdateMatrices(void)
{
	Math::Matrix4 matrix;
	std::wstringstream wss;

	wss << std::fixed << std::setprecision(2);

	matrix = sceneGraph->GetActiveCamera()->GetViewMatrix();

	int viewMatrixIndex = 0;
	for (UInt row = 0; row < 4; ++row)
	{
		for (UInt col = 0; col < 4; ++col)
		{
			wss.str(L"");
			wss << matrix[row][col] << std::ends;

			viewMatrix[viewMatrixIndex]->SetLabelText(wss.str().c_str());
			viewMatrixIndex += 1;
		}
	}

	matrix = sceneGraph->GetActiveCamera()->GetProjectionMatrix();

	int projectionMatrixIndex = 0;
	for (UInt row = 0; row < 4; ++row)
	{
		for (UInt col = 0; col < 4; ++col)
		{
			wss.str(L"");
			wss << matrix[row][col] << std::ends;

			projectionMatrix[projectionMatrixIndex]->SetLabelText(wss.str().c_str());
			projectionMatrixIndex += 1;
		}
	}

	wss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
}

void TransformPanel::OnSliderMouseWheel(wxMouseEvent& event)
{
	wxSpinCtrlDouble* spinCtrl = (wxSpinCtrlDouble*)event.GetEventObject();

	if (event.GetWheelRotation() > 0)
	{
		if (spinCtrl->GetValue() < spinCtrl->GetMax())
			spinCtrl->SetValue(spinCtrl->GetValue() + 1);
	}
	else
	{
		if (spinCtrl->GetValue() > spinCtrl->GetMin())
			spinCtrl->SetValue(spinCtrl->GetValue() - 1);
	}
}

void TransformPanel::OnPositionXChanged(wxSpinDoubleEvent& event)
{
	double value = event.GetValue();
	sceneGraph->GetActiveCamera()->Rotation((float)value, 0.0f, 0.0f);
}

void TransformPanel::OnPositionYChanged(wxSpinDoubleEvent& event)
{
	double value = event.GetValue();
	sceneGraph->GetActiveCamera()->Rotation(0.0f, (float)value, 0.0f);
}

void TransformPanel::OnPositionZChanged(wxSpinDoubleEvent& event)
{
	double value = event.GetValue();
	sceneGraph->GetActiveCamera()->Rotation(0.0f, 0.0f, (float)value);
}

void TransformPanel::OnIdle(wxIdleEvent& WXUNUSED(event))
{
	UpdateMatrices();
}

wxBoxSizer* TransformPanel::CreateGroupControl(wxObjectEventFunction func, const wxString& label)
{
	wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* staticText = new wxStaticText(this, wxID_STATIC, label, wxDefaultPosition, wxDefaultSize, 0);
	boxSizer->Add(staticText, 0, wxALL, 5);

	wxSpinCtrlDouble* spinCtrl = new wxSpinCtrlDouble(this, wxID_ANY, "0.0", wxDefaultPosition, wxDefaultSize);
	spinCtrl->Connect(wxEVT_COMMAND_SPINCTRLDOUBLE_UPDATED, func, NULL, this);
	spinCtrl->Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(TransformPanel::OnSliderMouseWheel), NULL, this);
	boxSizer->Add(spinCtrl, 1, wxALL | wxEXPAND, 5);
	
	return boxSizer;
}