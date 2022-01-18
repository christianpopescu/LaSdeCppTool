#include "AppFrame.h"
#include <wx/Panel.h>

AppFrame::AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->Append(ID_Paint, "&Paint something...\tCtrl-P",
        "Paint");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Files and Folders Kit!");
    clientWindow =  new wxWindow(this, wxID_ANY);


    
}

void AppFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world Files And Folder Kit Application!");
}

void AppFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a Files and Folders Kit Application",
        "About Files and Folders Kit Application", wxOK | wxICON_INFORMATION);
}

void AppFrame::OnPaint(wxCommandEvent& event)
{
    wxPaintDC dc(this->clientWindow);
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxRED_BRUSH);
    // Get window dimensions
    wxSize sz = GetClientSize();
    // Our rectangle dimensions
    int w = 100, h = 50;

    // Center the rectangle on the window, but never
    // draw at a negative position.
    int x = wxMax(0,200);
    int y = wxMax(0, 100);
    wxRect rectToDraw(x, y, w, h);
    // For efficiency, do not draw if not exposed
 //   if (IsExposed(rectToDraw))
        dc.DrawRectangle(rectToDraw);
        dc.DrawLine(0, 0, 200, 200);
}

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
EVT_MENU(ID_Hello, AppFrame::OnHello)
EVT_MENU(ID_Paint, AppFrame::OnPaint)
EVT_MENU(wxID_EXIT, AppFrame::OnExit)
EVT_MENU(wxID_ABOUT, AppFrame::OnAbout)
wxEND_EVENT_TABLE()

