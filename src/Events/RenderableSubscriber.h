#pragma once
/*
* All renderables should recieve reference to a Movable or resizable as base argument???? This should define the relative position of the renderable????? (Read next line!!!!!)
* UiElement should also be renderable (It recieved a renderer object from the root). The render function in the component should do a translation to the viewport coordinate system
*/



class RenderEventInfo;
class DrawData;
#include "DrawData.h"

/**
 *	This interface defines all the classes which are capable of drawing on the canvas.
 */
class RenderableSubscriber
{
public:
	/**
	 * Method which recieves the render events
	 * \param e the render event object which contains the renderer on which the rendering is to be done. Check RenderEventInfo class.
	 */
	virtual void OnRender(RenderEventInfo e) = 0;
	virtual void OnSync(const DrawData& data) = 0;
};

