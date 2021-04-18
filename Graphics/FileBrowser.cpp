#include "FileBrowser.h"

FileBrowser::FileBrowser() : FileBrowser("")
{

}

FileBrowser::FileBrowser(std::string title)
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


void FileBrowser::SetTitle(std::string title)
{
	this->title = title;
	browserStructure.lpstrTitle = this->title.c_str();
}

bool FileBrowser::Save()
{
	browserStructure.Flags = flags;
	browserStructure.lpstrFilter = filters.c_str();
	return GetSaveFileNameA(&browserStructure);
}

bool FileBrowser::Open()
{
	browserStructure.Flags = flags;
	browserStructure.lpstrFilter = filters.c_str();
	return GetOpenFileNameA(&browserStructure);
}

void FileBrowser::SetSelectedFilter(int index)
{
	browserStructure.nFilterIndex = index;
}

void FileBrowser::SetDefaultExtention(std::string extention)
{
	browserStructure.lpstrDefExt = extention.c_str();
}

void FileBrowser::AddFilter(std::string filterName ,std::string pattern)
{
	filters += filterName;
	filters.push_back('\0');
	filters += pattern;
	filters.push_back('\0');
	//filters = ("All\0*.*\0Text\0*.TXT\0");
}



FileBrowser& FileBrowser::AllowMultiSelect()
{
	flags |= OFN_ALLOWMULTISELECT;
	return *this;
}

FileBrowser& FileBrowser::CreatePrompt()
{
	flags |= OFN_CREATEPROMPT;
	return *this;
}

FileBrowser& FileBrowser::EnableResizing()
{
	flags |= OFN_ENABLESIZING;
	return *this;
}

FileBrowser& FileBrowser::FileMustExist()
{
	flags |= OFN_FILEMUSTEXIST;
	return *this;
}

FileBrowser& FileBrowser::ShowHiddenFiles()
{
	flags |= OFN_FORCESHOWHIDDEN;
	return *this;
}

FileBrowser& FileBrowser::SetFlags(DWORD Flags)
{
	flags = flags;
	return *this;
}



std::string FileBrowser::GetPath()
{
	return std::string(filePath);
}

std::string FileBrowser::GetFileName()
{
	return std::string(fileName);
}

std::wfstream* FileBrowser::GetFileStream(std::ios_base::openmode mode)
{
	if (strlen(filePath) <= 0)
		return nullptr;
	std::wfstream* stream = new std::wfstream();
	stream->open(filePath, mode);
	return stream;
}
