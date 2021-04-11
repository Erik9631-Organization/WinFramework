#pragma once
#include <vector>
#include "Resizable.h"
class DefaultResize : public Resizable
{
private:
	Gdiplus::Size size;
	std::vector<std::reference_wrapper<ResizeSubscriber>> subscribers;
	Resizable& associatedResizable;
public:
	DefaultResize(Resizable& resizeComponent);
	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual Gdiplus::Size GetSize() override;
	virtual int GetWidth() override;
	virtual int GetHeight() override;
	virtual void SetSize(Gdiplus::Size size) override;
	virtual void SetSize(int width, int height) override;
	virtual void SetWidth(int width) override;
	virtual void SetHeight(int height) override;
};

