#pragma once
#include <filesystem>
#include <regex>
namespace fs = std::filesystem;
class FileAndFolderService
{
public:
	static std::vector<fs::path> GetRecursiveFiles(const fs::path&  inputPath, const std::regex&  reg);
	
	// Return list of groups get from regular expression
	// Assumption: the file contains lines that corresponds to regular expression. The regular expression could contains a couple of groups
	static std::vector<std::vector<std::string>> GetInfoFromFile(const fs::path& filePath, const std::regex& reg, int number_of_groups);
};

