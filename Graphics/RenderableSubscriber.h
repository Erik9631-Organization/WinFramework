#pragma once
/*
* All renderables should recieve reference to a Movable or resizable as base argument???? This should define the relative position of the renderable????? (Read next line!!!!!)
* Component should also be renderable (It recieved a graphics object from the root). The render function in the component should do a transformation to the viewport coordinate system
*/
class RenderEventInfo;

class RenderableSubscriber
{
public:
	virtual void OnRender(RenderEventInfo e) = 0;
};

