#include "WindowsFileBrowser.h"

WindowsFileBrowser::WindowsFileBrowser(std::string title)
{
	filePath = new char[fileNameSize];
	fileName = new char[fileTitleSize];
	this->title = title;
	memset(&browserStructure, 0, sizeof(OPENFILENAMEA));
	browserStructure.lStructSize = sizeof(OPENFILENAMEA);
	browserStructure.nMaxFile = fileNameSize;
	browserStructure.nMaxFileTitle = fileTitleSize;
	browserStructure.lpstrFile = filePath;
	browserStructure.lpstrFileTitle = fileName;
	browserStructure.lpstrFile[0] = 0;
	browserStructure.lpstrTitle = this->title.c_str();
	flags = 0;
}

void WindowsFileBrowser::SetTitle(std::string title)
{
	this->title = title;
	browserStructure.lpstrTitle = this->title.c_str();
}

bool WindowsFileBrowser::Save()
{
	browserStructure.Flags = flags;
	browserStructure.lpstrFilter = filters.c_str();
	return GetSaveFileNameA(&browserStructure);
}

bool WindowsFileBrowser::Open()
{
	browserStructure.Flags = flags;
	browserStructure.lpstrFilter = filters.c_str();
	return GetOpenFileNameA(&browserStructure);
}

void WindowsFileBrowser::SetSelectedFilter(int index)
{
	browserStructure.nFilterIndex = index;
}

void WindowsFileBrowser::SetDefaultExtention(std::string extention)
{
	browserStructure.lpstrDefExt = extention.c_str();
}

void WindowsFileBrowser::AddFilter(std::string filterName , std::string pattern)
{
	filters += filterName;
	filters.push_back('\0');
	filters += pattern;
	filters.push_back('\0');
	//filters = ("All\0*.*\0Text\0*.TXT\0");
}

void WindowsFileBrowser::SetDefaultDirectory(std::string initialDir)
{

}

FileBrowser & WindowsFileBrowser::AllowMultiSelect()
{
	flags |= OFN_ALLOWMULTISELECT;
	return *this;
}

FileBrowser & WindowsFileBrowser::CreatePrompt()
{
	flags |= OFN_CREATEPROMPT;
	return *this;
}

FileBrowser & WindowsFileBrowser::EnableResizing()
{
	flags |= OFN_ENABLESIZING;
	return *this;
}

FileBrowser & WindowsFileBrowser::FileMustExist()
{
	flags |= OFN_FILEMUSTEXIST;
	return *this;
}

FileBrowser & WindowsFileBrowser::ShowHiddenFiles()
{
	flags |= OFN_FORCESHOWHIDDEN;
	return *this;
}

FileBrowser & WindowsFileBrowser::SetFlags(unsigned int Flags)
{
	flags = flags;
	return *this;
}

std::string WindowsFileBrowser::GetPath()
{
	return std::string(filePath);
}

std::string WindowsFileBrowser::GetFileName()
{
	return std::string(fileName);
}

std::wfstream* WindowsFileBrowser::GetFileStream(std::ios_base::openmode mode)
{
	if (strlen(filePath) <= 0)
		return nullptr;
	std::wfstream* stream = new std::wfstream();
	stream->open(filePath, mode);
	return stream;
}
