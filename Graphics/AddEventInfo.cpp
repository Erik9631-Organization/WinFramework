#include "AddEventInfo.h"
#include "Component.h"

AddEventInfo::AddEventInfo(Component & addedComponent, Component& parentComponent) : addedComponent(addedComponent), parentComponent(parentComponent)
{

}

Component & AddEventInfo::GetAddedComponent()
{
	return addedComponent;
}

Component & AddEventInfo::GetParentComponent()
{
	return parentComponent;
}


AddEventInfo::~AddEventInfo()
{
}
