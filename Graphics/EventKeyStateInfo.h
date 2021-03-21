#pragma once
#include <any>
#include "InputManager.h"

class EventKeyStateInfo
{
private:
	std::any source;
	int virtualKey;
	wchar_t unicodeKey;
	InputManager manager;
public:
	EventKeyStateInfo(std::any source, int virtualKey, wchar_t unicodeKey);
	EventKeyStateInfo(std::any source, int virtualKey, wchar_t unicodeKey, BYTE* keyboardState);
	InputManager& GetInputManager();
	std::any GetSource();
	int GetVirtualKey();
	wchar_t GetUnicodeKey();
};

