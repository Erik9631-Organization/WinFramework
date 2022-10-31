//
// Created by Erik on 08/03/22.
//

#include "StaticTexture.h"
#include "EventResizeInfo.h"
#include <stb_image.h>
#include <stb_image_resize.h>
#include "glew.h"
using namespace OpenGL;

Vector2 StaticTexture::GetSize()
{
    return Vector2();
}

float StaticTexture::GetWidth()
{
    return size.GetX();
}

float StaticTexture::GetHeight()
{
    return size.GetY();
}

void StaticTexture::SetSize(Vector2 size, bool emit)
{
    if(imageData == nullptr)
        return;
    unsigned char *output;
    stbir_resize_uint8(imageData, this->size.GetX(), this->size.GetY(),
                       0, output, size.GetX(), size.GetY(), 0, 0);
    this->size = size;
    imageData = output;
}

void StaticTexture::SetSize(float width, float height, bool emit)
{
    SetSize({width, height}, emit);
}

void StaticTexture::SetWidth(float width, bool emit)
{
    SetSize(width, size.GetY(), emit);
}

void StaticTexture::SetHeight(float height, bool emit)
{
    SetSize(size.GetX(), height, emit);
}

void StaticTexture::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    resizeBehavior.NotifyOnResizeSubscribers(event);
}

void OpenGL::StaticTexture::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void OpenGL::StaticTexture::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

OpenGL::StaticTexture::StaticTexture(const std::string &path, const int &format) :
    resizeBehavior(*this)
{
    this->path = path;
    this->format = format;
}

OpenGL::StaticTexture::StaticTexture() : StaticTexture("", 0)
{

}

const std::string & OpenGL::StaticTexture::GetPath() const
{
    return path;
}

void OpenGL::StaticTexture::SetPath(const std::string &wstring, const int &format)
{
    this->path = wstring;
    this->format = format;
}

const unsigned char * OpenGL::StaticTexture::GetData() const
{
    return imageData;
}

const bool &OpenGL::StaticTexture::LoadFromFile()
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

void OpenGL::StaticTexture::Load()
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

const int &OpenGL::StaticTexture::GetFormat() const
{
    return format;
}

const bool &OpenGL::StaticTexture::IsLoaded()
{
    return loaded;
}

void OpenGL::StaticTexture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGL::StaticTexture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void StaticTexture::Unload()
{

}

const std::string &StaticTexture::GetTag()
{
    return tag;
}

void StaticTexture::SetTag(const std::string &tag)
{
    this->tag = tag;
}

const unsigned long long int &StaticTexture::GetId() const
{
    return textureId;
}
