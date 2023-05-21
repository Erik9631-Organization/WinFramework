//
// Created by erik9 on 5/14/2023.
//

#include "ModelContainer.h"
#include "RectangleModel.h"
#include "TextModel.h"
#include "EllipseModel.h"
#include "LineModel.h"
#include "EventMoveInfo.h"

RenderingModel *ModelContainer::CreateModel(SubCommands createCommand)
{
    switch (createCommand)
    {
        case SubCommands::RequestRectangle:
        {
            auto* model = CreateModel<RectangleModel>();
            modelZIndexMap.emplace(model->GetZIndex(), model);
            auto concreteModel = dynamic_cast<RectangleModel*>(model);
            if(concreteModel != nullptr)
                concreteModel->AddOnMoveSubscriber(*this);
            return model;
        }
        case SubCommands::RequestText:
        {
            auto* model = CreateModel<TextModel>();
            modelZIndexMap.emplace(model->GetZIndex(), model);
            auto concreteModel = dynamic_cast<TextModel*>(model);
            if(concreteModel != nullptr)
                concreteModel->AddOnMoveSubscriber(*this);
            return model;
        }
        case SubCommands::RequestEllipse:
        {
            auto* model = CreateModel<EllipseModel>();
            modelZIndexMap.emplace(model->GetZIndex(), model);
            auto concreteModel = dynamic_cast<EllipseModel*>(model);
            if(concreteModel != nullptr)
                concreteModel->AddOnMoveSubscriber(*this);
            return model;
        }
        case SubCommands::RequestLine:
        {
            auto* model = CreateModel<LineModel>();
            modelZIndexMap.emplace(model->GetZIndex(), model);
            auto concreteModel = dynamic_cast<LineModel*>(model);
            if(concreteModel != nullptr)
                concreteModel->AddOnMoveSubscriber(*this);
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
    modelZIndexMap.erase(model->GetZIndex());
}

void ModelContainer::RemoveModel(size_t index)
{
    if(index >= renderingModels.size())
        return;
    modelZIndexMap.erase(renderingModels[index]->GetZIndex());
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
//TODO Optimization events should send additional info what axis has changed
void ModelContainer::OnMove(EventMoveInfo e)
{
    auto matches = modelZIndexMap.equal_range(e.GetAbsolutePosition().z);
    auto model = dynamic_cast<RenderingModel*>(e.GetSource());
    if (model == nullptr)
        return;

    for(auto it = matches.first; it != matches.second; ++it)
    {
        if(it->second == model)
        {
            modelZIndexMap.erase(it);
            break;
        }
    }
    modelZIndexMap.emplace(e.GetAbsolutePosition().z, model);
}

const std::multimap<float, RenderingModel *> & ModelContainer::GetZIndexMap() const
{
    return modelZIndexMap;
}
