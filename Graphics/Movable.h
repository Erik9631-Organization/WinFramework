#pragma once
#include "MoveSubject.h"
#include <Windows.h>
#include <gdiplus.h>

class Movable : public MoveSubject
{
public:
	virtual Gdiplus::Point GetPosition() = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;

	virtual int GetAbsoluteX() = 0;
	virtual int GetAbsoluteY() = 0;
	virtual Gdiplus::Point GetAbsolutePosition() = 0;

	virtual void SetPosition(Gdiplus::Point position) = 0;
	virtual void SetPosition(int x, int y) = 0;
	virtual void SetX(int x) = 0;
	virtual void SetY(int y) = 0;

	virtual void SetElementOffset(Gdiplus::Point offset) = 0;
	virtual void SetElementXOffset(int x) = 0;
	virtual void SetElementYOffset(int y) = 0;
	virtual Gdiplus::Point GetElementOffset() = 0;
	virtual int GetElementXOffset() = 0;
	virtual int GetElementYOffset() = 0;
};

