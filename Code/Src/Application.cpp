#include "../Inc/Application.h"
#include "../Inc/MainFrame.h"

IMPLEMENT_APP(Application);

bool Application::OnInit(void)
{
	wxImage::AddHandler(new wxXPMHandler);
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);

	//wxInitAllImageHandlers();

	MainFrame* frame = new MainFrame(NULL);
	frame->Maximize();
	frame->Show();

	SetTopWindow(frame);

	return true;
}