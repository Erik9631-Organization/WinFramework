#pragma once
#include "Utils/InputManager.h"
#include "Event.h"
/**
 * This class is responsible for holding event information related to keyboard inputs.
 */
class EventKeyStateInfo : public Event
{
private:
	EventSource* source;
	int virtualKey;
	wchar_t unicodeKey;
	InputManager manager;
public:
	/**
	 * \param source the source object that calls the event
	 * \param virtualKey the virtual key that was interacted with when the event was sent.
	 * \param unicodeKey the unicode key of the thumbTrack that was interacted with when the event was sent.
	 */
	EventKeyStateInfo(EventSource *source, int virtualKey, wchar_t unicodeKey);

	/**
	 * \param source the source object that calls the event
	 * \param virtualKey the virtual key that was interacted with when the event was sent.
	 * \param unicodeKey the unicode key of the thumbTrack that was interacted with when the event was sent.
	 * \param keyboardState a pointer to an array containing a snapshot of the current state of the keyboard. Check <a href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeyboardstate">MSDN</a> for more info 
	 */
	EventKeyStateInfo(EventSource *source, int virtualKey, wchar_t unicodeKey, unsigned char *keyboardState);

	EventKeyStateInfo(EventSource *source, EventKeyStateInfo info);

	/**
	 * \return returns a reference to the input manager which contains a snapshot of the keyboard state when the event was sent.
	 */
	InputManager& GetInputManager();

	/**
	 * \return returns the virtual key that was interacted with at the point the event was called.
	 */
	int GetVirtualKey();

	/**
	 * \return returns the unicode character of the key that was interacted with at the point the event was called.
	 */
	wchar_t GetUnicodeKey();

    EventSource * GetSource() const override;
};

