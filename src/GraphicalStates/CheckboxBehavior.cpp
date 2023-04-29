#include "CheckboxBehavior.h"
#include "EventMouseStateInfo.h"
#include "Checkbox.h"
#include "EventCheckboxStateInfo.h"
#include "CheckboxStateSubscriber.h"

CheckBoxBehavior::CheckBoxBehavior(Checkbox& checkbox) : associatedCheckbox(checkbox)
{
	checkbox.AddMouseStateSubscriber(*this);
}

void CheckBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
	associatedCheckbox.Check();
}

void CheckBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{

}

void CheckBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{

}

void CheckBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{

}

void CheckBoxBehavior::AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber)
{
	subscribers.emplace_back(subscriber);
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

void CheckBoxBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}
