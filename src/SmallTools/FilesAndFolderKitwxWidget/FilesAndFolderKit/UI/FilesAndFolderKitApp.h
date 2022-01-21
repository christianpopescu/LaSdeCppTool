#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "AppFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};