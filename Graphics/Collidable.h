#pragma once
#include <any>
namespace Gdiplus
{
	class Point;
}

class Collidable
{
public:
	virtual bool ColidesWithPoint(Gdiplus::Point) = 0;
	virtual std::any ColidesWithUpmost(Gdiplus::Point) = 0;
};

