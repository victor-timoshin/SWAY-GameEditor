#include "../Inc/MainMenu.h"

IMPLEMENT_CLASS(MainMenu, wxMenuBar)

BEGIN_EVENT_TABLE(MainMenu, wxMenuBar)
	EVT_MENU(ID_MENU_NEW_PRJ, MainMenu::OnNewProject)
	EVT_MENU(ID_MENU_OPEN_PRJ, MainMenu::OnOpenProject)
	EVT_MENU(ID_MENU_SAVE_PRJ, MainMenu::OnSaveProject)
	EVT_MENU(ID_MENU_SAVE_AS_PRJ, MainMenu::OnSaveAsProject)
	EVT_MENU(wxID_EXIT, MainMenu::OnExit)
	EVT_MENU(wxID_ABOUT, MainMenu::OnAbout)
END_EVENT_TABLE()

/// <summary>Конструктор класса.</summary>
MainMenu::MainMenu(void)
{
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_MENU_NEW_PRJ, "New\tCtrl+N");
	fileMenu->Append(ID_MENU_OPEN_PRJ, "Open\tCtrl+O");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_MENU_SAVE_PRJ, "Save\tCtrl+S");
	fileMenu->Append(ID_MENU_SAVE_AS_PRJ, "Save As...");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");

	wxMenu* editMenu = new wxMenu();
	editMenu->Append(wxID_UNDO, "Undo\tCtrl+Z");
	editMenu->Append(wxID_REDO, "Redo\tCtrl+Y");

	wxMenu* viewMenu = new wxMenu();
	viewMenu->AppendCheckItem(ID_TOGGLE_LOGWINDOW, "Help Window");

	wxMenu* helpMenu = new wxMenu();
	helpMenu->Append(wxID_ABOUT, "About");

	Append(fileMenu, "File");
	Append(editMenu, "Edit");
	Append(viewMenu, "View");
	Append(helpMenu, "Help");
}

/// <summary>Деструктор класса.</summary>
MainMenu::~MainMenu(void)
{
}


void MainMenu::OnNewProject(wxCommandEvent& event)
{
}

void MainMenu::OnOpenProject(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* openDialog = new wxFileDialog(this, "Choose a file to open",
		wxEmptyString, wxEmptyString, "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG;*.JPEG", wxFD_OPEN, wxDefaultPosition);

	int response = openDialog->ShowModal();
	if (response == wxID_OK)
	{
		// TODO
	}

	openDialog->Destroy();
}

void MainMenu::OnSaveProject(wxCommandEvent& WXUNUSED(event))
{
}

void MainMenu::OnSaveAsProject(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* saveDialog = new wxFileDialog(this, "Save File As _?", wxEmptyString, wxEmptyString,
		"JPEG Files (*.JPG)|*.JPG|PNG Files (*.PNG)|*.PNG|GIF Files (*.GIF)|*.GIF|BMP Files (*.BMP)|*.BMP", wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	int response = saveDialog->ShowModal();
	if (response == wxID_OK)
	{
		// TODO
	}

	saveDialog->Destroy();
}

void MainMenu::OnExit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void MainMenu::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format("%s/n%s", wxVERSION_STRING, wxGetOsDescription().c_str()), "About", wxOK | wxICON_INFORMATION, this);
}