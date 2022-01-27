#pragma once
/*
* All renderables should recieve reference to a Movable or resizable as base argument???? This should define the relative position of the renderable????? (Read next line!!!!!)
* UiElement should also be renderable (It recieved a graphics object from the root). The render function in the component should do a transformation to the viewport coordinate system
*/



class RenderEventInfo;
/**
 *	This interface defines all the classes which are capable of drawing on the canvas.
 */
class RenderableSubscriber
{
public:
	/**
	 * Method which recieves the render events
	 * \param e the render event object which contains the graphics on which the rendering is to be done. Check RenderEventInfo class.
	 */
	virtual void OnRender(RenderEventInfo e) = 0;
};

