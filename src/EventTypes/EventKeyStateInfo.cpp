#include "EventKeyStateInfo.h"

EventKeyStateInfo::EventKeyStateInfo(KeyStateSubject* source, int virtualKey, wchar_t unicodeKey) : EventKeyStateInfo(source, virtualKey, unicodeKey, nullptr)
{

}

EventKeyStateInfo::EventKeyStateInfo(KeyStateSubject* source, int virtualKey, wchar_t unicodeKey, unsigned char *keyboardState)
{
	this->source = source;
	this->virtualKey = virtualKey;
	this->unicodeKey = unicodeKey;
	if (keyboardState != nullptr)
		manager.SetKeyboardState(keyboardState);
}

EventKeyStateInfo::EventKeyStateInfo(KeyStateSubject* source, EventKeyStateInfo info)
{
	manager = info.GetInputManager();
	unicodeKey = info.GetUnicodeKey();
	virtualKey = info.GetVirtualKey();
	this->source = source;
}

InputManager& EventKeyStateInfo::GetInputManager()
{
	return manager;
}

KeyStateSubject* EventKeyStateInfo::GetSource()
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
