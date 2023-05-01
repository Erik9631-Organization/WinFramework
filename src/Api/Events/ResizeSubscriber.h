#pragma once
#include "EventResizeInfo.h"
class ResizeSubscriber
{
public:
	virtual void OnResize(EventResizeInfo e) = 0;
    virtual ~ResizeSubscriber() = default;
};

