#pragma once

#include "FileBrowser.h"

class LinuxFileBrowser : public FileBrowser
{
/**
     * Opens a file browser window designed for saving files.
     * This is a blocking function and the exection is halted here until the dialog window is closed.
     * \return returns true on success and false on failure.
     */
    bool Save() override;

    /**
     * Opens a file browser window designed for loading files.
     * This is a blocking function and the exection is halted here until the dialog window is closed.
     * \return returns true on success and false on failure.
     */
    bool Open() override;

    /**
     * Adds a new filter option to the file browser.
     * \param filterName the filter name under which the filter will be displayed.
     * \param pattern the pattern the filter should follow.
     */
    void AddFilter(std::string filterName, std::string pattern) override;

    /**
     * Sets the directory that the filebrowser should point to after it is opened.
     * \param initialDir the directory path parameter.
     */
    void SetDefaultDirectory(std::string initialDir) override;

    /**
     * \param index the index of the filter that should be used by default (When the browser is openned.).
     */
    void SetSelectedFilter(int index) override;

    /**
     * \param extention the default extention that is appended to the filename in the "File Name" text field.
     */
    void SetDefaultExtention(std::string extention) override;

    /**
     * \param title the title the file browser should display when openned.
     */
    void SetTitle(std::string title) override;

    /**
     * Allows multi selecting files in the window.
     */
    FileBrowser& AllowMultiSelect() override;

    /**
     * Sets the create prompt flag.
     */
    FileBrowser& CreatePrompt() override;

    /**
     * Enables or disables resizing of the file browswer.
     */
    FileBrowser& EnableResizing() override;
    FileBrowser& FileMustExist() override;

    /**
     * Shows hidden files.
     */
    FileBrowser& ShowHiddenFiles() override;

    /**
     * \param Flags sets the flags of the file browser. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea">MSDN</a> for more information..
     */
    FileBrowser& SetFlags(unsigned int Flags) override;

    /**
     * \return returns the selected path.
     */
    std::string GetPath() override;

    /**
     * \return returns the selected file name.
     */
    std::string GetFileName() override;

    /**
     * \return returns a unicode stream to the selected file.
     */
    std::wfstream* GetFileStream(std::ios_base::openmode mode) override;
};
