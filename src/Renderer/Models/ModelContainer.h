//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_MODELCONTAINER_H
#define LII_MODELCONTAINER_H


#include <memory>
#include <vector>
#include <map>
#include "Commands.h"
#include "RenderingModel.h"
#include "MoveSubscriber.h"

class ModelContainer : public MoveSubscriber
{
private:
    RenderingModel * AddModel(std::unique_ptr<RenderingModel> renderingModel);
    Renderer& renderer;
    template<typename T>
    T* CreateModel()
    {
        auto model = std::make_unique<T>();
        model->SetRenderer(&renderer);
        return static_cast<T*>(AddModel(std::move(model)));
    }
    std::vector<std::unique_ptr<RenderingModel>> renderingModels;
    std::multimap<float, RenderingModel*> modelZIndexMap;
public:
    [[nodiscard]] const std::multimap<float, RenderingModel *> & GetZIndexMap() const;
    explicit ModelContainer(Renderer& renderer);
    RenderingModel *CreateModel(SubCommands createCommand);
    void RemoveModel(RenderingModel* model);
    void RemoveModel(size_t index);
    RenderingModel *GetModel(size_t index);
    const std::vector<std::unique_ptr<RenderingModel>>& GetModels();

    void OnMove(EventMoveInfo e) override;
};


#endif //LII_MODELCONTAINER_H
