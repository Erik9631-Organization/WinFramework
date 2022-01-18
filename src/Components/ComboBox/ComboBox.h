#pragma once
#include "Components/Panel.h"
#include "Graphics/SimpleBorder.h"
#include "ComboSelection.h"
#include "Events/ComboBoxStateSubscriber.h"
#include "Events/ComboBoxStateSubject.h"
#include "Behavior/DefaultComboBoxBehavior.h"
#include <any>

class Button;
class DefaultComboBoxBehavior;

/**
 * A combobox component. When clicked will show a list of options from which a selection can be made.
 * Once selected, the displayed string within the checkbox will change to the selection string. In the combo menu, the selected item will also highlight.
 */

class ComboBox : public Panel, public ComboBoxStateSubject
{
private:
	ComboSelection selections;
	Button* button;
	DefaultComboBoxBehavior behavior;
	bool isPacked = true;
public:
	/**
	 * \return returns whether the combobox is packed or unpacked. True if packed, false if unpacked
	 */
	bool IsPacked();
	ComboBox();
	
	/**
	 * \param componentName name of the component. Used for identification and the value is not displayed anywhere.
	 */
	ComboBox(std::string componentName);

	/**
	 * \param x position where the component should appear
	 * \param y position where the component should appear
	 * \param width of the component
	 * \param height height of the component
	 * \param componentName the name of the component.
	 */
	ComboBox(int x, int y, int width, int height, std::string componentName);

	/**
	 * Changes the source thumbTrack under which the elements should unpack.
	 * \param button the source of the thumbTrack.
	 */
	void SetComboButton(Button* button);

	/**
	 * \return returns the text which is displayed on the associated thumbTrack
	 */
	std::wstring GetText();

	/**
	 * \param text sets the text which is displayed on the associated thumbTrack
	 */
	void SetText(std::wstring text);

	/**
	 * Creates a new combo element which appears within the unpacked window
	 * \param comboElementText the text that the element should display
	 * \param value any object which the element should contain.
	 */
	MouseStateSubject& CreateComboElement(std::wstring comboElementText, std::any value);

	/**
	 * Unpacks the combobox
	 */
	void Upack();

	/**
	 * Packs the combobox
	 */
	void Pack();

	/**
	 * \return returns reference to the currently selected combo element
	 */
	ComboElement& GetSelectedElement();

	// Inherited via ComboBoxStateSubject
	virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e) override;
	virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e) override;
	virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e) override;
	virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;
	virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;
};

