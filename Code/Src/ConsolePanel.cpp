#include "../Inc/ConsolePanel.h"

ConsolePanel::ConsolePanel(wxWindow* parent, wxWindowID id) : wxPanel(parent, id)
{
	logTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	commandTextCtrl = new wxTextCtrl(this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	wxBoxSizer* verticalBoxSizer = new wxBoxSizer(wxVERTICAL);
	verticalBoxSizer->Add(logTextCtrl, 1, wxEXPAND | wxALL, 4);
	verticalBoxSizer->Add(commandTextCtrl, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 4);

	SetSizer(verticalBoxSizer);
}

ConsolePanel::~ConsolePanel(void)
{
}