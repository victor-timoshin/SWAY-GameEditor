#ifndef CONSOLEPANEL_H
#define CONSOLEPANEL_H

#include "StdAfx.h"

class ConsolePanel : public wxPanel
{
public:
	/// <summary>����������� ������.</summary>
	/// <param name="parent">��������� �� ������������ ����.</param>
	/// <param name="id">���������� ������������� ������.</param>
	ConsolePanel(wxWindow* parent, wxWindowID id = wxID_ANY);

	/// <summary>���������� ������.</summary>
	~ConsolePanel(void);

private:
	wxTextCtrl* logTextCtrl;
	wxTextCtrl* commandTextCtrl;
};

#endif