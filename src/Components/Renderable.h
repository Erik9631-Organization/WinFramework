#pragma once
#include "Events/RenderableSubscriber.h"
#include <vector>
#include <Renderer.h>

/**
 * This interface is implemented by all the classes that are capable of rendering
 */
class  Renderable : public RenderableSubscriber
{
public:
	/**
	 * Requests a repaint of the current component
	 */
	virtual void Repaint() = 0;
	
	/**
	 * Adds a new renderable to the rendering context. Renderables are graphical objects that are drawn within the component.
	 * \param renderable the renderable to be added.
	 */
	virtual void AddRenderable(Renderable &renderable) = 0;

	/**
	 * Removes a renderable from the rendering context. Renderables are graphical objects that are drawn within the component.
	 * \param renderable the renderable to be removed.
	 */
	virtual void RemoveRenderable(Renderable& renderable) = 0;

	/**
	 * Returns a vector of all the renderables contained within the component.
	 * \return returns a vector containing the renderables.
	 */
	virtual std::vector <std::reference_wrapper<Renderable>> GetRenderables() = 0;
};
