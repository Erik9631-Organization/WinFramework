//
// Created by Erik on 20/03/22.
//

#ifndef LII_RENDEROBJECTEVENTINFO_H
#define LII_RENDEROBJECTEVENTINFO_H
#include <memory>
#include <any>
#include "Event.h"

class RenderObjectSubscriber;

class RenderObjectEventInfo : public Event
{
private:
    EventSource* src;
    std::any eventData;
public:
    explicit RenderObjectEventInfo(EventSource *src, std::any eventData = nullptr);
    template<typename T>
    T* GetSrc() const
    {
        return std::any_cast<T*>(src);
    }

    [[nodiscard]] EventSource * GetSource() const override;
};


#endif //LII_RENDEROBJECTEVENTINFO_H
