#include "FileBrowserFactory.h"
#include "LinuxFileBrowser.h"
#include "WindowsFileBrowser.h"

std::unique_ptr<FileBrowser> FileBrowserFactory::Create(std::string title) {
    FileBrowser * fileBrowser = nullptr;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    fileBrowser = new WindowsFileBrowser(title);
#elif __linux__
    fileBrowser = new LinuxFileBrowser(title);
#else
    error "Unknown compiler"
#endif
    return std::unique_ptr<FileBrowser>(fileBrowser);
}
