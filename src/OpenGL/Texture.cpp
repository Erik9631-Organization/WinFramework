//
// Created by Erik on 08/03/22.
//

#include "DefaultTexture.h"
#include "EventResizeInfo.h"
#include <stb_image.h>
#include <stb_image_resize.h>
#include "glew.h"
using namespace OpenGL;

Vector2 DefaultTexture::GetSize()
{
    return Vector2();
}

float DefaultTexture::GetWidth()
{
    return size.GetX();
}

float DefaultTexture::GetHeight()
{
    return size.GetY();
}

void DefaultTexture::SetSize(Vector2 size)
{
    if(imageData == nullptr)
        return;
    unsigned char *output;
    stbir_resize_uint8(imageData, this->size.GetX(), this->size.GetY(),
                       0, output, size.GetX(), size.GetY(), 0, 0);
    this->size = size;
    imageData = output;
}

void DefaultTexture::SetSize(float width, float height)
{
    SetSize({width, height});
}

void DefaultTexture::SetWidth(float width)
{
    SetSize(width, size.GetY());
}

void DefaultTexture::SetHeight(float height)
{
    SetSize(size.GetX(), height);
}

void DefaultTexture::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    resizeBehavior.NotifyOnResizeSubscribers(event);
}

void OpenGL::DefaultTexture::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void OpenGL::DefaultTexture::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

OpenGL::DefaultTexture::DefaultTexture(const std::string &path, const int &format) :
    resizeBehavior(*this)
{
    this->path = path;
    this->format = format;
}

OpenGL::DefaultTexture::DefaultTexture() : DefaultTexture("", 0)
{

}

const std::string & OpenGL::DefaultTexture::GetPath() const
{
    return path;
}

void OpenGL::DefaultTexture::SetPath(const std::string &wstring, const int &format)
{
    this->path = wstring;
    this->format = format;
}

const unsigned char * OpenGL::DefaultTexture::GetData() const
{
    return imageData;
}

const bool &OpenGL::DefaultTexture::LoadFromFile()
{
    int width = 0;
    int height = 0;
    int n = 0;
    imageData = stbi_load(path.c_str(), &width, &height, &n, 0);
    if(imageData == nullptr)
        return false;
    this->size.SetValue(width, height);

    return true;
}

void OpenGL::DefaultTexture::LoadResource()
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, format, size.GetX(), size.GetY(), 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    loaded = true;
    stbi_image_free(imageData);
}

const int &OpenGL::DefaultTexture::GetFormat() const
{
    return format;
}

const bool &OpenGL::DefaultTexture::IsLoaded()
{
    return loaded;
}

void OpenGL::DefaultTexture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGL::DefaultTexture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DefaultTexture::UnloadResource()
{

}

const std::string &DefaultTexture::GetTag()
{
    return tag;
}

void DefaultTexture::SetTag(const std::string &tag)
{
    this->tag = tag;
}

const unsigned long long int &DefaultTexture::GetId() const
{
    return textureId;
}
