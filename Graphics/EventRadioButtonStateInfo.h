#pragma once
#include <any>

/**
 * This class is responsible for holding all the information related to radio button events.
 */
class EventRadioButtonStateInfo
{
private:
	bool isSelected;
	std::any src;
public:
	/**
	 * \param selected whether the src object is selected. True for selected, false for unselected
	 * \param src the source object that called the event.
	 */
	EventRadioButtonStateInfo(bool selected, std::any src);

	/**
	 * \return returns the source object that called the event.
	 */
	std::any GetSrc();
	
	/**
	 * \returns whether the src object was selected.
	 */
	bool IsSelected();
};

