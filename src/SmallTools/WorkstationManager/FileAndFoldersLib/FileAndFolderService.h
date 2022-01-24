#pragma once
#include <filesystem>
#include <regex>
namespace fs = std::filesystem;
class FileAndFolderService
{
public:
	static std::vector<fs::path> GetRecursiveFiles(const fs::path&  inputPath, const std::regex&  reg);
};

