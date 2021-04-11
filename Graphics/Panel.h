#pragma once
#include "Component.h"
#include "SimpleBorder.h"
#include <string>


class Panel :public Component
{
private:
	SimpleBorder border;
public:
	Panel();
	Panel(std::string name);
	Panel(int x, int y, int width, int height, std::string name);
};

