#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
class MouseInteractable;
/**
 * A filebrwoser class. If FileBrowser::Open is called, a file browser window is openned, allowing the user to select the file to save / load.
*/
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
	/**
	 * The title that will appear at the top of the filebrowser window
	 * \param title the string that will be displayed as a title
	 */
	FileBrowser(std::string title);

	/**
	 * Opens a file browser window designed for saving files.
	 * This is a blocking function and the exection is halted here until the dialog window is closed.
	 * \return returns true on success and false on failure.
	 */
	bool Save();

	/**
	 * Opens a file browser window designed for loading files.
	 * This is a blocking function and the exection is halted here until the dialog window is closed.
	 * \return returns true on success and false on failure.
	 */
	bool Open();

	/**
	 * Adds a new filter option to the file browser.
	 * \param filterName the filter name under which the filter will be displayed.
	 * \param pattern the pattern the filter should follow. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea">MSDN</a> for more information.
	 */
	void AddFilter(std::string filterName, std::string pattern);

	/**
	 * Sets the directory that the filebrowser should point to after it is opened.
	 * \param initialDir the directory path parameter.
	 */
	void SetDefaultDirectory(std::string initialDir);

	/**
	 * \param index the index of the filter that should be used by default (When the browser is openned.).
	 */
	void SetSelectedFilter(int index);

	/**
	 * \param extention the default extention that is appended to the filename in the "File Name" text field.
	 */
	void SetDefaultExtention(std::string extention);

	/**
	 * \param title the title the file browser should display when openned.
	 */
	void SetTitle(std::string title);

	/**
	 * Allows multi selecting files in the window.
	 */
	FileBrowser& AllowMultiSelect();

	/**
	 * Sets the create prompt flag.
	 */
	FileBrowser& CreatePrompt();
	
	/**
	 * Enables or disables resizing of the file browswer.
	 */
	FileBrowser& EnableResizing();
	FileBrowser& FileMustExist();

	/**
	 * Shows hidden files.
	 */
	FileBrowser& ShowHiddenFiles();

	/**
	 * \param Flags sets the flags of the file browser. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea">MSDN</a> for more information..
	 */
	FileBrowser& SetFlags(DWORD Flags);

	/**
	 * \return returns the selected path.
	 */
	std::string GetPath();

	/**
	 * \return returns the selected file name.
	 */
	std::string GetFileName();

	/**
	 * \return returns a unicode stream to the selected file.
	 */
	std::wfstream* GetFileStream(std::ios_base::openmode mode);
};

