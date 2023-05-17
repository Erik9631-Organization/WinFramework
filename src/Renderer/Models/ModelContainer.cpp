//
// Created by erik9 on 5/14/2023.
//

#include "ModelContainer.h"
#include "RectangleModel.h"
#include "TextModel.h"
#include "EllipseModel.h"
#include "LineModel.h"

RenderingModel *ModelContainer::CreateModel(SubCommands createCommand)
{
    switch (createCommand)
    {
        case SubCommands::RequestRectangle:
        {
            auto* model = CreateModel<RectangleModel>();
            return model;
        }
        case SubCommands::RequestText:
        {
            auto* model = CreateModel<TextModel>();
            return model;
        }
        case SubCommands::RequestEllipse:
        {
            auto* model = CreateModel<EllipseModel>();
            return model;
        }
        case SubCommands::RequestLine:
        {
            auto* model = CreateModel<LineModel>();
            return model;
        }
        default:
            return nullptr;
    }
}

RenderingModel *ModelContainer::AddModel(std::unique_ptr<RenderingModel> renderingModel)
{
    RenderingModel* modelPtr = renderingModel.get();
    renderingModels.push_back(std::move(renderingModel));
    modelPtr->SetModelId(renderingModels.size() - 1);
    return modelPtr;
}

ModelContainer::ModelContainer(Renderer &renderer) :
    renderer(renderer)
{

}

void ModelContainer::RemoveModel(RenderingModel *model)
{
    renderingModels.erase(renderingModels.begin() + model->GetModelId());
}

void ModelContainer::RemoveModel(size_t index)
{
    if(index >= renderingModels.size())
        return;
    renderingModels.erase(renderingModels.begin() + index);
}

RenderingModel *ModelContainer::GetModel(size_t index)
{
    if(index >= renderingModels.size())
        return nullptr;
    return renderingModels[index].get();
}

const std::vector<std::unique_ptr<RenderingModel>> &ModelContainer::GetModels()
{
    return renderingModels;
}
