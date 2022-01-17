#include "DefaultRender.h"
#include "EventTypes/RenderEventInfo.h"

DefaultRender::DefaultRender(Renderable& renderable) : assosiactedRenderable(renderable)
{

}

void DefaultRender::OnRender(RenderEventInfo e)
{
	if (e.GetGraphics() == nullptr)
		return;

	for (Renderable& renderable : renderables)
		renderable.OnRender(e);
}

void DefaultRender::Repaint()
{
	assosiactedRenderable.Repaint();
}

void DefaultRender::AddRenderable(Renderable& renderable)
{
	renderables.push_back(renderable);
	Repaint();
}

void DefaultRender::RemoveRenderable(Renderable& renderable)
{
	for (std::vector<std::reference_wrapper<Renderable>>::iterator i = renderables.begin(); i != renderables.end(); i++)
	{
		if (&i->get() == &renderable)
		{
			renderables.erase(i);
			return;
		}
	}
}

std::vector<std::reference_wrapper<Renderable>> DefaultRender::GetRenderables()
{
	return renderables;
}

