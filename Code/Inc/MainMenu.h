#ifndef MAINMENU_H
#define MAINMENU_H

#include "StdAfx.h"

class MainMenu : public wxMenuBar
{
	DECLARE_CLASS(MainMenu)
	DECLARE_EVENT_TABLE()

public:
	/// <summary>Конструктор класса.</summary>
	MainMenu(void);

	/// <summary>Деструктор класса.</summary>
	~MainMenu(void);

protected:
	void OnNewProject(wxCommandEvent& event);

	void OnOpenProject(wxCommandEvent& event);

	void OnSaveProject(wxCommandEvent& event);

	void OnSaveAsProject(wxCommandEvent& event);

	void OnExit(wxCommandEvent& event);

	void OnAbout(wxCommandEvent& event);

private:

};

#endif