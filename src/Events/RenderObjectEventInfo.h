//
// Created by Erik on 20/03/22.
//

#ifndef LII_RENDEROBJECTEVENTINFO_H
#define LII_RENDEROBJECTEVENTINFO_H
#include <memory>
#include <any>
class RenderObjectSubscriber;

class RenderObjectEventInfo
{
private:
    std::any src;
    std::any eventData;
public:
    RenderObjectEventInfo(std::any src, std::any eventData = nullptr);
    template<typename T>
    T* GetSrc() const
    {
        return std::any_cast<T*>(src);
    }
};


#endif //LII_RENDEROBJECTEVENTINFO_H
