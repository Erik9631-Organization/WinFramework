//
// Created by Erik on 09/04/22.
//

#ifndef LII_DEFAULTRENDERINGMANAGER_H
#define LII_DEFAULTRENDERINGMANAGER_H
#include "RenderingManager.h"
#include <map>
#include "ShaderProgram.h"
#include "CoreWindow.h"

namespace OpenGL
{
    class DefaultRenderingManager : public RenderingManager
    {
    public:
        void Render() override;
        void Render(const Model &model) override;
        void AddModel(const Model &model) override;
        void RemoveModel(Model &model) override;
        void Move(const Model &model) override;
    private:
        void DrawInternalModel(Model &model);
        long long lastShaderId = -1;
        long long lastMeshManagerId = -1;
        long long lastTextureId = -1;
        const Texture* lastTexture = nullptr;
        struct Compare
        {
            bool operator()(const Model* a, const Model* b) const
            {
                //If the texture is not set, set the ID to very low
                long long aTextureId = -1;
                long long bTextureId = -1;
                if(a->GetTexture() != nullptr)
                    aTextureId = a->GetTexture()->GetId();
                if(b->GetTexture() != nullptr)
                    bTextureId = b->GetTexture()->GetId();

                //First compare by ShaderId as swapping shader is the most expensive
                if(a->GetShader().GetId() < b->GetShader().GetId())
                    return true;
                if(a->GetShader().GetId() > b->GetShader().GetId())
                    return false;

                //Compare by texture as texture swapping is the second most expensive.
                if(aTextureId < bTextureId)
                    return true;
                if(aTextureId > bTextureId)
                    return false;

                //Lastly compare by the buffer.
                if(a->GetMesh()->GetMeshManager().GetId() < b->GetMesh()->GetMeshManager().GetId())
                    return true;
                if(a->GetMesh()->GetMeshManager().GetId() > b->GetMesh()->GetMeshManager().GetId())
                    return false;

                //If everything is equal then just decide using generic ID
                if(a->GetId() < b->GetId())
                    return true;
                if(a->GetId() > b->GetId())
                    return false;

                //Equal objects
                return false;
            }
        };

        std::map<const Model*, Model*, Compare> renderingScene;
    };
}



#endif //LII_DEFAULTRENDERINGMANAGER_H
