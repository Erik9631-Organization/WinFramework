#include "EventKeyStateInfo.h"

EventKeyStateInfo::EventKeyStateInfo(EventSource *source, int virtualKey, wchar_t unicodeKey) : EventKeyStateInfo(source, virtualKey, unicodeKey, nullptr)
{

}

EventKeyStateInfo::EventKeyStateInfo(EventSource *source, int virtualKey, wchar_t unicodeKey, unsigned char *keyboardState)
{
	this->source = source;
	this->virtualKey = virtualKey;
	this->unicodeKey = unicodeKey;
	if (keyboardState != nullptr)
		manager.SetKeyboardState(keyboardState);
}

EventKeyStateInfo::EventKeyStateInfo(EventSource *source, EventKeyStateInfo info)
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

int EventKeyStateInfo::GetVirtualKey()
{
	return virtualKey;
}

wchar_t EventKeyStateInfo::GetUnicodeKey()
{
	return unicodeKey;
}

EventSource * EventKeyStateInfo::GetSource() const
{
    return source;
}
