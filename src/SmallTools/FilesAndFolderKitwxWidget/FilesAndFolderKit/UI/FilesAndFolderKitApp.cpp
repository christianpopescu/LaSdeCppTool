#include "FilesAndFolderKitApp.h"

bool MyApp::OnInit()
{
    AppFrame* frame = new AppFrame("Files and Folders kit", wxPoint(50, 50), wxSize(900, 680));
    frame->Show(true);
    return true;
}