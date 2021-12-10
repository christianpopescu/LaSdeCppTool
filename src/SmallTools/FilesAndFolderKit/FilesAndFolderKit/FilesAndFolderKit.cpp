// FilesAndFolderKit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

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
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

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
	
	std::string s;
	std::cin >> s;
	wprintf(L"\x1b[31mThis text has a red foreground using SGR.31.\r\n");
	wprintf(L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n");
	wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
	wprintf(L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n");
	wprintf(L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n");
	wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
	wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
	wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");
	// To also clear the scroll back, emit L"\x1b[3J" as well.
	// 2J only clears the visible window and 3J only clears the scroll back.

	// Restore the mode on the way out to be nice to other command-line applications.
	SetConsoleMode(hStdOut, originalMode);
	return false;
}

int main()
{
	int value1;
	if (test_ansi_code(value1)) return value1;

	return 0;
}


