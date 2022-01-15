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

int main()
{
	int value1;
	CoInitialize(NULL);
	Poc::LoadFile();
	if (Poc::test_ansi_code(value1)) return value1;

	return 0;
}

