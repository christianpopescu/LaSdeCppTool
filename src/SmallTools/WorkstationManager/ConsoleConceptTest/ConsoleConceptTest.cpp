// The purpose of this project is to test different scenarios
//

#include <iostream>
#include <filesystem>
#include <regex>
#include "../FileAndFoldersLib/FileAndFolderService.h"


namespace fs = std::filesystem;

int main()
{
    std::cout << "Hello World!\n";
    fs::path pt("D:\\Temp\\FirstQtWidgets");
    for (auto p : FileAndFolderService::GetRecursiveFiles(pt, std::regex(".*"))) {
        std::cout << p.stem().string() << std::endl;
    }


}

