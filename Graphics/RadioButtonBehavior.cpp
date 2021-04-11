#include "RadioButtonBehavior.h"
#include "EventMouseStateInfo.h"
#include "RadioButton.h"
#include "RadioButtonStateSubscriber.h"
#include "EventRadioButtonStateInfo.h"


RadioButtonBehavior::RadioButtonBehavior(RadioButton& button) : associatedRadioButton(button)
{
	group = nullptr;
	button.AddMouseStateSubscriber(*this);
}

void RadioButtonBehavior::Group(RadioButton& button)
{
	if (group == nullptr)
	{
		group = std::make_shared<std::vector<std::reference_wrapper<RadioButton>>>();
		group->push_back(associatedRadioButton);
	}

	group->push_back(button);
	button.SetGroup(group);
}

void RadioButtonBehavior::RemoveFromGroup(RadioButton& button)
{
	if (group == nullptr)
		return;
	for (std::vector<std::reference_wrapper<RadioButton>>::iterator it = group->begin(); it <= group->end(); it++)
		if (&it->get() == &button)
		{
			group->erase(it);
			return;
		}
}

void RadioButtonBehavior::UnGroup()
{
	if (group == nullptr)
		return;

	RemoveFromGroup(associatedRadioButton);
	this->group = nullptr;

}

void RadioButtonBehavior::SetGroup(std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group)
{
	if (group == nullptr)
		return;
	this->group = group;
}

void RadioButtonBehavior::OnMouseDown(EventMouseStateInfo e)
{

}

void RadioButtonBehavior::OnMouseUp(EventMouseStateInfo e)
{
	associatedRadioButton.Check();
	if (group == nullptr)
		return;

	if (!associatedRadioButton.IsChecked())
		return;

	for (RadioButton& button : *group)
	{
		if(&button != &associatedRadioButton)
			button.SetChecked(false);
	}

}

void RadioButtonBehavior::OnMousePressed(EventMouseStateInfo e)
{

}

void RadioButtonBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void RadioButtonBehavior::OnMouseEntered(EventMouseStateInfo e)
{
}

void RadioButtonBehavior::OnMouseLeft(EventMouseStateInfo e)
{
}

void RadioButtonBehavior::NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e)
{
	for (RadioButtonStateSubscriber& subscriber : subscribers)
		subscriber.OnRadioButtonSelected(e);
}

void RadioButtonBehavior::AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

void RadioButtonBehavior::RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<RadioButtonStateSubscriber>>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
		if (&it->get() == &subscriber)
		{
			subscribers.erase(it);
			return;
		}
}
