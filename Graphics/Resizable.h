#pragma once
#include "ResizeSubject.h"
#include <Windows.h>
#include <gdiplus.h>
class Resizable : public ResizeSubject
{
public:
	virtual Gdiplus::Size GetSize() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void SetSize(Gdiplus::Size size) = 0;
	virtual void SetSize(int width, int height) = 0;
	virtual void SetWidth(int width) = 0;
	virtual void SetHeight(int height) = 0;
};

