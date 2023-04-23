#pragma once
#include <any>
class RadioButtonStateSubject;

/**
 * This class is responsible for holding all the information related to radio thumbTrack events.
 */
class EventRadioButtonStateInfo
{
private:
	bool isSelected;
	RadioButtonStateSubject* src;
public:
	/**
	 * \param selected whether the src object is selected. True for selected, false for unselected
	 * \param src the source object that called the event.
	 */
	EventRadioButtonStateInfo(bool selected, RadioButtonStateSubject* src);

	/**
	 * \return returns the source object that called the event.
	 */
	RadioButtonStateSubject* GetSrc();
	
	/**
	 * \returns whether the src object was selected.
	 */
	bool IsSelected();
};

