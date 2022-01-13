// FilesAndFolderKit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
* This solution contains 3 pocs:
*  - using ansi code
*  - intercepting keybord
*  - Reading file / folder
*/

// TODO: Refactor  code moving POC to separate class
// TODO: Add class to rename files or folders

#include <iostream>
#include <string>
#include <Windows.h>
#include <Shobjidl_core.h>

#include "Poc/Poc.h"

HANDLE hStdin;
VOID ErrorExit(LPSTR, DWORD);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);


bool test_ansi_code(int& value1)
{
	HANDLE hStdOut;
	

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Fetch existing console mode so we correctly add a flag and not turn off others
	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode))
	{
		value1 = ::GetLastError();
		return true;
	}

	// Hold original mode to restore on exit to be cooperative with other command-line apps.
	const DWORD originalMode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_WINDOW_INPUT;

	// Try to set the mode.
	if (!SetConsoleMode(hStdOut, mode))
	{
		value1 = ::GetLastError();
		return true;
	}
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
	GetConsoleScreenBufferInfo(hStdOut, &ScreenBufferInfo);
	COORD Size;
	Size.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
	Size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
	
	
	
	// Write the sequence for clearing the display.
	DWORD written = 0;
	PCWSTR sequence = L"\x1b[2J";
	if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
	{
		// If we fail, try to restore the mode on the way out.
		SetConsoleMode(hStdOut, originalMode);
		value1 = ::GetLastError();
		return true;
	}

	// To also clear the scroll back, emit L"\x1b[3J" as well.
	// 2J only clears the visible window and 3J only clears the scroll back.

	written = 0;
	sequence = L"\033[34;1;4mHello\033[0m";
	if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
	{
		// If we fail, try to restore the mode on the way out.
		SetConsoleMode(hStdOut, originalMode);
		value1 = ::GetLastError();
		return true;
	}

	std::cout << Size.X << std::endl;
	std::cout << Size.Y << std::endl;
	
	std::cout << "Input string followed by <Enter> ";
	std::string s;
	std::cin >> s;
	wprintf(L"\x1b[31mText 1.\r\n");
	wprintf(L"\x1b[1mText 2.\r\n");
	wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
	wprintf(L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n");
	wprintf(L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n");
	wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
	wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
	wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");
	// To also clear the scroll back, emit L"\x1b[3J" as well.
	// 2J only clears the visible window and 3J only clears the scroll back.

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	std::string msg1{ "GetStdHandle"};
	//LPSTR pS1 =  TCHAR[31];
	LPSTR pS1 = const_cast<char*>(msg1.c_str());
	std::string msg2{ "ReadConsoleInput" };
	//LPSTR pS1 =  TCHAR[31];
	LPSTR pS2 = const_cast<char*>(msg2.c_str());
	std::string msg3{ "ReadConsoleInput" };
	//LPSTR pS1 =  TCHAR[31];
	LPSTR pS3 = const_cast<char*>(msg3.c_str());
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit(pS1, originalMode);
	while (counter++ <= 50)
	{
		// Wait for the events.

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit(pS2, originalMode);

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events

			case MENU_EVENT:   // disregard menu events
				break;

			default:
				ErrorExit(pS3, originalMode);
				break;
			}
		}
	}

	// Restore the mode on the way out to be nice to other command-line applications.
	SetConsoleMode(hStdOut, originalMode);
	return false;
}

int main()
{
	int value1;
	CoInitialize(NULL);
	Poc::LoadFile();
	if (test_ansi_code(value1)) return value1;

	return 0;
}

VOID ErrorExit(LPSTR lpszMessage, DWORD savedMode)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.
	
	SetConsoleMode(hStdin, savedMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	printf("Key event: ");

	if (ker.bKeyDown)
		printf("key pressed\n");
	else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
