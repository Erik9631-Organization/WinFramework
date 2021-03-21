#include "EventKeyStateInfo.h"
#include <Windows.h>

EventKeyStateInfo::EventKeyStateInfo(std::any source, int virtualKey, wchar_t unicodeKey) : EventKeyStateInfo(source, virtualKey, unicodeKey, nullptr)
{

}

EventKeyStateInfo::EventKeyStateInfo(std::any source, int virtualKey, wchar_t unicodeKey, BYTE* keyboardState)
{
	this->source = source;
	this->virtualKey = virtualKey;
	this->unicodeKey = unicodeKey;
	if (keyboardState != nullptr)
		manager.SetKeyboardState(keyboardState);
}

InputManager& EventKeyStateInfo::GetInputManager()
{
	return manager;
}

std::any EventKeyStateInfo::GetSource()
{
	return source;
}

int EventKeyStateInfo::GetVirtualKey()
{
	return virtualKey;
}

wchar_t EventKeyStateInfo::GetUnicodeKey()
{
	return unicodeKey;
}
