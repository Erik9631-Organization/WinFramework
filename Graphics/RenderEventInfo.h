#pragma once
#include <Windows.h>
#include <gdiplus.h>

class RenderEventInfo
{
private:
	Gdiplus::Graphics* graphics;
public:
	RenderEventInfo(Gdiplus::Graphics* g);
	Gdiplus::Graphics* GetGraphics();
};