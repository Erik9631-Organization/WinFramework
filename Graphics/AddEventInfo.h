#pragma once
class Component;
class AddEventInfo
{
private:
	Component & addedComponent;
	Component & parentComponent;
public:
	AddEventInfo(Component & addedComponent, Component& parentComponent);
	Component & GetAddedComponent();
	Component & GetParentComponent();
	~AddEventInfo();
};

