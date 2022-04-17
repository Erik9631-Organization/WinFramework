#pragma once
#include <vector>
#include "api/Resizable.h"
class DefaultResize : public Resizable
{
private:
	Vector2 size;
	std::vector<std::reference_wrapper<ResizeSubscriber>> subscribers;
	Resizable& associatedResizable;
public:
	DefaultResize(Resizable& resizeComponent);
	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual Vector2 GetSize() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;
	virtual void SetSize(Vector2 size) override;
	virtual void SetSize(float width, float height) override;
	virtual void SetWidth(float width) override;
	virtual void SetHeight(float height) override;
};

