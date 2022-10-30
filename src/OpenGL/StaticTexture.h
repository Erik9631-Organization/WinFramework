//
// Created by Erik on 08/03/22.
//

#ifndef STB_TEXTURE_H
#define STB_TEXTURE_H


#include "LiiImage.h"
#include "DefaultResize.h"
#include <string>
#include "Vector2Int.h"
#include "Texture.h"

namespace OpenGL
{
    class StaticTexture : public Texture
    {
    private:
        DefaultResize resizeBehavior;
        std::string path;
        unsigned char* imageData;
        Vector2Int size;
        unsigned int textureId = 0;
        int format = 0;
        bool loaded = false;
        std::string tag;
    public:
        StaticTexture();
        StaticTexture(const std::string &path, const int &format);
        void SetSize(Vector2 size, bool emit) override;
        void SetSize(float width, float height, bool emit) override;
        void SetWidth(float width) override;
        void SetHeight(float height) override;
        void NotifyOnResizeSubscribers(EventResizeInfo event) override;
        void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;
        void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;
        const std::string & GetPath() const override;
        void SetPath(const std::string &wstring, const int &format) override;
        const unsigned char * GetData() const override;
        const bool &LoadFromFile() override;
        void Load() override;
        const int &GetFormat() const override;
        const bool &IsLoaded() override;
        void Bind() const override;
        void Unbind() const override;
        float GetHeight() override;
        Vector2 GetSize() override;
        float GetWidth() override;
        void Unload() override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
        const unsigned long long int &GetId() const override;
    };
}


#endif //STB_TEXTURE_H
