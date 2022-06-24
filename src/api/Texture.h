//
// Created by Erik on 12/04/22.
//

#ifndef LII_TEXTURE_H
#define LII_TEXTURE_H
#include "Resource.h"
#include "Identifiable.h"

class Texture : public Resource, public Resizable, public Identifiable
{
public:
    virtual void NotifyOnResizeSubscribers(EventResizeInfo event) = 0;
    virtual void AddOnResizeSubscriber(ResizeSubscriber &subscriber) = 0;
    virtual void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) = 0;
    virtual const bool& LoadFromFile() = 0;
    virtual const std::string & GetPath() const = 0;
    virtual void SetPath(const std::string &wstring, const int &format) = 0;
    virtual const unsigned char * GetData() const = 0;
    virtual const int &GetFormat() const = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};

#endif //LII_TEXTURE_H
