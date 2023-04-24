#pragma once
#include "Components/UiElement.h"
#include "Graphics/SimpleBorder.h"
#include "Border.h"
#include <string>


class Panel :public UiElement
{
protected:
	Border border;
public:
	Panel();

	/**
	 * \param name the identification name of the grid. This is not a display value.
	 */
	Panel(std::string name);

	/**
	 * \param x the X viewPortSize of the grid.
	 * \param y the Y viewPortSize of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	Panel(int x, int y, int width, int height, std::string name);
};

