#include "pch.h"
#include "FileAndFolderService.h"
#include <fstream>

std::vector<fs::path> FileAndFolderService::GetRecursiveFiles(const fs::path& inputPath, const std::regex& reg)
{

    std::vector<fs::path> result;
    if (fs::exists(inputPath)) {
        for (const fs::directory_entry& de :
            fs::recursive_directory_iterator(inputPath)) {
            if (de.is_regular_file() && std::regex_match(de.path().stem().string(), reg)) {
                result.push_back(de.path());
            }

        }
    }
    return result;
}

std::vector<std::vector<std::string>> FileAndFolderService::GetInfoFromFile(const fs::path& filePath, const std::regex& reg, int number_of_groups)
{
    std::vector<std::vector<std::string>> result;
    if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
        std::ifstream file;
        file.open(filePath.string());
        std::string line;
        std::vector<std::string > line_by_group;
        if (file.is_open()) {
            std::smatch match;
            if (std::regex_search(line, match, reg) == true) {
                std::vector<std::string > line_by_group;
                for (int i{ 0 }; i < number_of_groups; ++i) {
                    line_by_group.push_back(match.str(i + 1));
                }
                result.push_back(line_by_group);
            }
        }
    }
    return result;
}
