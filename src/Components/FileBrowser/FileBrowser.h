#pragma once

#include <string>
#include <fstream>

class FileBrowser {
public:
    /**
     * Opens a file browser window designed for saving files.
     * This is a blocking function and the exection is halted here until the dialog window is closed.
     * \return returns true on success and false on failure.
     */
    virtual bool Save() = 0;

    /**
     * Opens a file browser window designed for loading files.
     * This is a blocking function and the exection is halted here until the dialog window is closed.
     * \return returns true on success and false on failure.
     */
    virtual bool Open() = 0;

    /**
     * Adds a new filter option to the file browser.
     * \param filterName the filter name under which the filter will be displayed.
     * \param pattern the pattern the filter should follow. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea">MSDN</a> for more information.
     */
    virtual void AddFilter(std::string filterName, std::string pattern) = 0;

    /**
     * Sets the directory that the filebrowser should point to after it is opened.
     * \param initialDir the directory path parameter.
     */
    virtual void SetDefaultDirectory(std::string initialDir) = 0;

    /**
     * \param index the index of the filter that should be used by default (When the browser is openned.).
     */
    virtual void SetSelectedFilter(int index) = 0;

    /**
     * \param extention the default extention that is appended to the filename in the "File Name" text field.
     */
    virtual void SetDefaultExtention(std::string extention) = 0;

    /**
     * \param title the title the file browser should display when openned.
     */
    virtual void SetTitle(std::string title) = 0;

    /**
     * Allows multi selecting files in the window.
     */
    virtual FileBrowser& AllowMultiSelect() = 0;

    /**
     * Sets the create prompt flag.
     */
    virtual FileBrowser& CreatePrompt() = 0;

    /**
     * Enables or disables resizing of the file browswer.
     */
    virtual FileBrowser& EnableResizing() = 0;
    virtual FileBrowser& FileMustExist() = 0;

    /**
     * Shows hidden files.
     */
    virtual FileBrowser& ShowHiddenFiles() = 0;

    /**
     * \param Flags sets the flags of the file browser. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea">MSDN</a> for more information..
     */
    virtual FileBrowser& SetFlags(unsigned int Flags) = 0;

    /**
     * \return returns the selected path.
     */
    virtual std::string GetPath() = 0;

    /**
     * \return returns the selected file name.
     */
    virtual std::string GetFileName() = 0;

    /**
     * \return returns a unicode stream to the selected file.
     */
    virtual std::wfstream* GetFileStream(std::ios_base::openmode mode) = 0;
};

