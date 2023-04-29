//
// Created by Erik on 08/03/22.
//

#ifndef STB_TEXTURE_H
#define STB_TEXTURE_H


#include "LiiImage.h"
#include "DefaultResize.h"
#include <string>
#include "Texture.h"

namespace OpenGL
{
    class StaticTexture : public Texture
    {
    private:
        DefaultResize resizeBehavior;
        std::string path;
        unsigned char* imageData;
        glm::ivec4 size;
        unsigned int textureId = 0;
        int format = 0;
        bool loaded = false;
        std::string tag;
    public:
        StaticTexture();
        StaticTexture(const std::string &path, const int &format);
        void SetSize(const glm::vec3 &size, bool emit) override;
        void NotifyOnResizeSubscribers(EventResizeInfo event) override;
        void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;
        void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;
        [[nodiscard]] const std::string & GetPath() const override;
        void SetPath(const std::string &wstring, const int &format) override;
        [[nodiscard]] const unsigned char * GetData() const override;
        const bool &LoadFromFile() override;
        void Load() override;
        [[nodiscard]] const int &GetFormat() const override;
        const bool &IsLoaded() override;
        void Bind() const override;
        void Unbind() const override;
        [[nodiscard]] const glm::vec3 & GetSize() const override;
        void Unload() override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
        [[nodiscard]] const unsigned long long int &GetId() const override;
    };
}


#endif //STB_TEXTURE_H
