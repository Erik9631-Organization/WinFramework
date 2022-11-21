#pragma once

#include <string>
#include <memory>

class FileBrowser;

class FileBrowserFactory {
public:
    static std::unique_ptr<FileBrowser> Create(std::string title = std::string(""));
};

