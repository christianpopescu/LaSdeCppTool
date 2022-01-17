#include "AppFrame.h"

AppFrame::AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
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

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
EVT_MENU(ID_Hello, AppFrame::OnHello)
EVT_MENU(wxID_EXIT, AppFrame::OnExit)
EVT_MENU(wxID_ABOUT, AppFrame::OnAbout)
wxEND_EVENT_TABLE()