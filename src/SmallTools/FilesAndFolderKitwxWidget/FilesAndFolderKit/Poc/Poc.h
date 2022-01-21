#pragma once
#include <Windows.h>
#include <Shobjidl_core.h>
#include <iostream>
#include <string>

class Poc {
public:
	static HANDLE hStdin;

	static VOID ErrorExit(LPSTR, DWORD);
	static VOID KeyEventProc(KEY_EVENT_RECORD);
	static VOID MouseEventProc(MOUSE_EVENT_RECORD);
	static VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	static bool test_ansi_code(int& value1);
	static PWSTR LoadFile();
};