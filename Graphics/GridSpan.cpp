#include "GridSpan.h"


GridSpan::GridSpan()
{
	this->gridRowStart = 0;
	this->gridRowEnd = 0;

	this->gridColumnStart = 0;
	this->gridColumnEnd = 0;
}

GridSpan GridSpan::CreateColumnSpan(int columnStart, int columnEnd)
{
	GridSpan span = GridSpan(columnStart, columnEnd, 0, 0);
	return span;
}

GridSpan GridSpan::CreateRowSpan(int rowStart, int rowEnd)
{
	GridSpan span = GridSpan(0, 0, rowStart, rowEnd);
	return span;
}

GridSpan GridSpan::CreateSpan(int columnStart, int columnEnd, int rowStart, int rowEnd)
{
	GridSpan span = GridSpan(columnStart, columnEnd, rowStart, rowEnd);
	return span;
}

GridSpan::GridSpan(int columnStart, int columnEnd, int rowStart, int rowEnd)
{
	this->gridRowStart= rowStart;
	this->gridRowEnd = rowEnd;

	this->gridColumnStart = columnStart;
	this->gridColumnEnd = columnEnd;
}

bool GridSpan::isSet()
{
	if (!gridColumnStart && !gridColumnEnd && !gridRowStart && !gridRowEnd)
		return false;
	return true;
}

int GridSpan::GetGridColumnStart()
{
	return gridColumnStart;
}

int GridSpan::GetGridColumnEnd()
{
	return gridColumnEnd;
}

int GridSpan::GetGridRowStart()
{
	return gridRowStart;
}

int GridSpan::GetGridRowEnd()
{
	return gridRowEnd;
}
