#include "CheckboxBehavior.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "Components/Checkbox.h"
#include "EventTypes/EventCheckboxStateInfo.h"
#include "Events/CheckboxStateSubscriber.h"
#include "Vector3.h"

CheckBoxBehavior::CheckBoxBehavior(Checkbox& checkbox) : associatedCheckbox(checkbox)
{
	checkbox.AddMouseStateSubscriber(*this);
	onClickColor = {150, 150, 150, 255};
}

void CheckBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty("background-color", onClickColor);
	associatedCheckbox.Check();
}

void CheckBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty<Vector3>("background-color", {100, 100, 100});
}

void CheckBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void CheckBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty<Vector3>("background-color", {100, 100, 100});
}

void CheckBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{
	associatedCheckbox.SetProperty<Vector4>("background-colorRGBA", {0, 0, 0, 0});
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

void CheckBoxBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}
