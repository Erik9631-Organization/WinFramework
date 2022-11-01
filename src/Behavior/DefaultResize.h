#pragma once
#include <vector>
#include "api/Resizable.h"
#include "vec2.hpp"

class DefaultResize : public Resizable
{
private:
    glm::vec2 size;
	std::vector<std::reference_wrapper<ResizeSubscriber>> subscribers;
	Resizable& associatedResizable;
public:
	DefaultResize(Resizable& resizeComponent);
	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual glm::vec2 GetSize() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;
	virtual void SetSize(const glm::vec2 &size, bool emit) override;
	virtual void SetSize(float width, float height, bool emit) override;
	virtual void SetWidth(float width, bool emit) override;
	virtual void SetHeight(float height, bool emit) override;

    void SetSize(const glm::vec2 &size) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width) override;

    void SetHeight(float height) override;
};

