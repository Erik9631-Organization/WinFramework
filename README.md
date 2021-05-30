# Lii Framework
Lii framework is an open source framework which allows you to create interactive desktop applications on windows platform with ease.


## Installation
1. Download the file from the release tab.
2. Extract it somewhere to your disk.
3. In visual studio, point the compiler to the include/header directory where you extracted your lib.
	- This is found under C/C++ > General > Additional Include Directories.
4. Point the compiler to the .lib file located in the include directory.
	- This is found under Linker > General > Additional Library Directories
5. Include the lib in the additional dependencies.
	- This is located under Linker > Input > Additional Dependencies.
	- Type in the name of the lib (Lii.lib for release and LiiDebug.lib for debug configuration)
	
## Entry point
Once everything is linked, you can create your first source file.
include the WinWrapper.h header and define the entry point.
An example of a bare-bone entry point:
```C++
#include <WinWrapper.h> // Needed
#include <ApplicationController.h>
int WinEntry()
{
	ApplicationController::JoinThreads();
	return 0;
}
```