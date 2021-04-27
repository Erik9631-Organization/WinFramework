#pragma once
class ComboElement;
class ComboBoxStateSubject;


class EventComboBoxStateInfo
{
private:
	ComboElement& element;
	ComboBoxStateSubject& src;
public:
	EventComboBoxStateInfo(ComboElement& element, ComboBoxStateSubject& src);
	ComboElement& GetElement();
	ComboBoxStateSubject& GetSrc();
};

