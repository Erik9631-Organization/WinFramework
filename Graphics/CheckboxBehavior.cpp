#include "CheckboxBehavior.h"
#include "EventMouseStateInfo.h"
#include "Checkbox.h"
#include "EventCheckboxStateInfo.h"
#include "CheckboxStateSubscriber.h"

CheckBoxBehavior::CheckBoxBehavior(Checkbox& checkbox) : associatedCheckbox(checkbox)
{
	checkbox.AddMouseStateSubscriber(*this);
	onClickColor = Color::MakeARGB(255, 100, 100, 100);
}

void CheckBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty("background-color", onClickColor);
	associatedCheckbox.Check();
}

void CheckBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty("background-color", Color::DarkGray);
}

void CheckBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty("background-color", Color::DarkGray);
}

void CheckBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty("background-color", Color::Transparent);
}

void CheckBoxBehavior::AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

void CheckBoxBehavior::RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<CheckboxStateSubscriber>>::iterator it; it != subscribers.end(); it++)
	{
		if (&it->get() == &subscriber)
			subscribers.erase(it);
	}
}

void CheckBoxBehavior::NotifyOnChecked(EventCheckboxStateInfo info)
{
	for (CheckboxStateSubscriber& subscriber : subscribers)
		subscriber.OnChecked(info);
}
