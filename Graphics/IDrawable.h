#pragma once
#include <Windows.h>
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
class IDrawable
{
public:
	virtual void Paint(Graphics& g) = 0;
	IDrawable() {};
	virtual ~IDrawable() {};
};

