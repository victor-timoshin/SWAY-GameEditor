#ifndef CONSOLEPANEL_H
#define CONSOLEPANEL_H

#include "StdAfx.h"

class ConsolePanel : public wxPanel
{
public:
	/// <summary>Конструктор класса.</summary>
	/// <param name="parent">Указатель на родительское окно.</param>
	/// <param name="id">Уникальный идентификатор панели.</param>
	ConsolePanel(wxWindow* parent, wxWindowID id = wxID_ANY);

	/// <summary>Деструктор класса.</summary>
	~ConsolePanel(void);

private:
	wxTextCtrl* logTextCtrl;
	wxTextCtrl* commandTextCtrl;
};

#endif