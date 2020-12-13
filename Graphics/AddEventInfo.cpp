#include "AddEventInfo.h"
#include "Component.h"

AddEventInfo::AddEventInfo(Component & addedComponent) : EventInfo(addedComponent)
{

}

Component * AddEventInfo::GetParentComponent()
{
	return component.GetParent();
}


AddEventInfo::~AddEventInfo()
{
}
