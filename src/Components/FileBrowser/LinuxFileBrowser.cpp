#include "LinuxFileBrowser.h"

bool LinuxFileBrowser::Save()
{
    return false;
}

bool LinuxFileBrowser::Open() {
    return false;
}

void LinuxFileBrowser::AddFilter(std::string filterName, std::string pattern) {

}

void LinuxFileBrowser::SetDefaultDirectory(std::string initialDir) {

}

void LinuxFileBrowser::SetSelectedFilter(int index) {

}

void LinuxFileBrowser::SetDefaultExtention(std::string extention) {

}

void LinuxFileBrowser::SetTitle(std::string title) {

}

FileBrowser &LinuxFileBrowser::AllowMultiSelect() {
    return *this;
}

FileBrowser &LinuxFileBrowser::CreatePrompt() {
    return *this;
}

FileBrowser &LinuxFileBrowser::EnableResizing() {
    return *this;
}

FileBrowser &LinuxFileBrowser::FileMustExist() {
    return *this;
}

FileBrowser &LinuxFileBrowser::ShowHiddenFiles() {
    return *this;
}

FileBrowser &LinuxFileBrowser::SetFlags(unsigned int Flags) {
    return *this;
}

std::string LinuxFileBrowser::GetPath() {
    return std::string();
}

std::string LinuxFileBrowser::GetFileName() {
    return std::string();
}

std::wfstream *LinuxFileBrowser::GetFileStream(std::ios_base::openmode mode) {
    return nullptr;
}
