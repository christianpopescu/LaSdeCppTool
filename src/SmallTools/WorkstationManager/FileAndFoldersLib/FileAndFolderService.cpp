#include "pch.h"
#include "FileAndFolderService.h"

std::vector<fs::path> FileAndFolderService::GetRecursiveFiles(const fs::path&  inputPath, const std::regex&  reg)
{
    std::vector<fs::path> result;
    for (const fs::directory_entry& de :
        fs::recursive_directory_iterator(inputPath)) {
        if (de.is_regular_file() && std::regex_match(de.path().stem().string(), reg)) {
            result.push_back(de.path());
        }
        return result;
    }
}
