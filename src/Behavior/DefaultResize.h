#pragma once
#include <vector>
#include "api/Resizable.h"
#include "vec2.hpp"

class DefaultResize : public Resizable
{
private:
    glm::vec3 size{0};
	std::vector<std::reference_wrapper<ResizeSubscriber>> subscribers;
	Resizable& associatedResizable;
public:
	DefaultResize(Resizable& resizeComponent);
	// Inherited via Resizable
    void NotifyOnResizeSubscribers(EventResizeInfo event) override;
    void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
    void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
    [[nodiscard]] const glm::vec3 & GetSize() const override;
    void SetSize(const glm::vec3 &size, bool emit = true) override;
};