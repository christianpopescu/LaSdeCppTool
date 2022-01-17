#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum
{
    ID_Hello = 1
};

class AppFrame : public wxFrame
{
public:
    AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    // This class handles events
    DECLARE_EVENT_TABLE()
   
};

