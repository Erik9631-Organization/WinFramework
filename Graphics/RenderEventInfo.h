#pragma once
#include <Windows.h>
#include <gdiplus.h>

class RenderEventInfo
{
private:
	Gdiplus::Graphics* graphics;
	Gdiplus::Size parentSize;
public:
	RenderEventInfo(Gdiplus::Graphics* g, Gdiplus::Size parentSize);
	RenderEventInfo(Gdiplus::Graphics* g);
	Gdiplus::Graphics* GetGraphics();
	Gdiplus::Size GetParentSize();
	void SetParentSize(Gdiplus::Size parentSize);
};