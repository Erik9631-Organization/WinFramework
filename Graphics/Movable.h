#pragma once
#include "MoveSubject.h"
#include <Windows.h>
#include <gdiplus.h>

class Movable
{
	virtual Gdiplus::Point GetPosition() = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual void SetPosition(Gdiplus::Point position) = 0;
	virtual void SetX(int x) = 0;
	virtual void SetY(int y) = 0;
};

