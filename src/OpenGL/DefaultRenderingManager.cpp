//
// Created by Erik on 09/04/22.
//

#include "CoreWindow.h"
#include "DefaultRenderingManager.h"
using namespace OpenGL;

void DefaultRenderingManager::Render()
{
    for(auto element : renderingScene)
    {
        Model& currentModel = *element.second;
        DrawInternalModel(currentModel);
    }
}

void DefaultRenderingManager::Render(const OpenGL::Model &model)
{
    auto result = renderingScene.find(&model);
    if(result == renderingScene.end())
        return;
    DrawInternalModel(*result->second);
}

void DefaultRenderingManager::AddModel(const Model &model)
{
    Model* internalModel = model.Clone();
    auto inserted = renderingScene.try_emplace(internalModel, internalModel);
    if(inserted.second == false)
        CoreWindow::ConsoleWrite("Insertion failed!!");
}

void DefaultRenderingManager::RemoveModel(OpenGL::Model &model)
{

}
//Used for updating the values during a sync event
void DefaultRenderingManager::Move(const Model &model)
{
    auto result = renderingScene.find(&model);
    if(result == renderingScene.end())
        return;
    result->second->Move(model);
}

void DefaultRenderingManager::DrawInternalModel(OpenGL::Model &model)
{
    if(model.GetShaderProgram().GetId() != lastShaderId)
    {
        lastShaderId = model.GetShaderProgram().GetId();
        model.GetShaderProgram().Load();
    }

    if(model.GetMesh() != nullptr && model.GetMesh()->GetMeshManager().GetId() != lastMeshManagerId)
    {
        lastMeshManagerId = model.GetMesh()->GetMeshManager().GetId();
        model.GetMesh()->GetMeshManager().Bind();
    }

    if(model.GetTexture() != nullptr)
    {
        if(model.GetTexture()->GetId() != lastTextureId)
        {
            model.GetTexture()->Bind();
            lastTexture = model.GetTexture();
            lastTextureId = model.GetTexture()->GetId();
        }
    }
    else if(lastTexture != nullptr)
    {
        lastTexture->Unbind();
        lastTextureId = -1;
        lastTexture = nullptr;
    }

    RenderObjectEventInfo eventInfo{this, nullptr};
    model.OnRender(&eventInfo);
}

bool DefaultRenderingManager::HasModel(const Model &model) const
{
    auto result = renderingScene.find(&model);
    if(result == renderingScene.end())
        return false;
    return true;
}
