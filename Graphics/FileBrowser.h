#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
class MouseInteractable;

class FileBrowser
{
private:
	int fileNameSize = 16384;
	int fileTitleSize = 8192;
	char* filePath;
	char* fileName;
	OPENFILENAMEA browserStructure;
	std::string filters;
	std::string title;
	DWORD flags;

public:
	FileBrowser();
	FileBrowser(std::string title);
	bool Save();
	bool Open();
	void AddFilter(std::string filterName, std::string pattern);
	void SetDefaultDirectory(std::string initialDir);
	void SetSelectedFilter(int index);
	void SetDefaultExtention(std::string extention);
	void SetTitle(std::string title);
	FileBrowser& AllowMultiSelect();
	FileBrowser& CreatePrompt();
	FileBrowser& EnableResizing();
	FileBrowser& FileMustExist();
	FileBrowser& ShowHiddenFiles();
	FileBrowser& SetFlags(DWORD Flags);
	std::string GetPath();
	std::string GetFileName();
	std::wfstream* GetFileStream(std::ios_base::openmode mode);
};

