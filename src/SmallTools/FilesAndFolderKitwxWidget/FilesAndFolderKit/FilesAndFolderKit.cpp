// FilesAndFolderKit.cpp : This file contains the macro that starts the wxWidgets application. Program execution begins and ends there.
//


/*
* This solution contains 3 pocs:
*  - using ansi code
*  - intercepting keybord
*  - Reading file / folder
*/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "UI/AppFrame.h"
#include "UI/FilesAndFolderKitApp.h"

wxIMPLEMENT_APP(MyApp);

/*
#include <iostream>
#include <string>
#include <Windows.h>
#include <Shobjidl_core.h>

#include "Poc/Poc.h"

int main()
{
	int value1;
	CoInitialize(NULL);
	Poc::LoadFile();
	if (Poc::test_ansi_code(value1)) return value1;

	return 0;
}

*/
