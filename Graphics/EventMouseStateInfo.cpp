#include "EventMouseStateInfo.h"

Gdiplus::Point EventMouseStateInfo::GetMousePosition()
{
	return position;
}

int EventMouseStateInfo::GetMouseX()
{
	return position.X;
}

int EventMouseStateInfo::GetMouseY()
{
	return position.Y;
}

int EventMouseStateInfo::GetKey()
{
	return key;
}
