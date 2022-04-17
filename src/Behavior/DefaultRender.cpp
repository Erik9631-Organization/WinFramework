#include "DefaultRender.h"
#include "RenderEventInfo.h"
#include "Vector2.h"
#include "DrawData2D.h"
#include <execution>
#include <algorithm>

DefaultRender::DefaultRender(RenderCommander& renderable) : assosiactedRenderable(renderable)
{

}

void DefaultRender::OnRender(RenderEventInfo e)
{

	if (e.GetRenderer() == nullptr)
		return;

	for (RenderCommander& renderable : renderables)
		renderable.OnRender(e);
}

void DefaultRender::Repaint()
{
	assosiactedRenderable.Repaint();
}

void DefaultRender::AddRenderable(RenderCommander &renderable)
{
    addRenderableMutex.lock();
	renderables.push_back(renderable);
	Repaint();
    addRenderableMutex.unlock();
}

void DefaultRender::RemoveRenderable(RenderCommander& renderable)
{
    addRenderableMutex.lock();
	for (std::vector<std::reference_wrapper<RenderCommander>>::iterator i = renderables.begin(); i != renderables.end(); i++)
	{
		if (&i->get() == &renderable)
		{
			renderables.erase(i);
			return;
		}
	}
    addRenderableMutex.unlock();
}

std::vector<std::reference_wrapper<RenderCommander>> DefaultRender::GetRenderables()
{
	return renderables;
}

void DefaultRender::OnSync(const DrawData& data)
{
    //Perform parallel for loop here
    addRenderableMutex.lock();
    std::for_each(std::execution::par, renderables.begin(), renderables.end(), [&](RenderCommander& renderable)
    {
        renderable.OnSync(data);
    });
    addRenderableMutex.unlock();

}

