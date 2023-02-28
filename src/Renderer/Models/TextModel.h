//
// Created by erik9 on 2/21/2023.
//

#ifndef LII_TEXTMODEL_H
#define LII_TEXTMODEL_H
#include "Movable.h"
#include "Resizable.h"
#include "RenderingModel.h"
#include "MovableModelBehavior.h"

class TextModel : public Movable, public RenderingModel
{
private:
    MovableModelBehavior movableModelBehavior;
    size_t modelId = 0;
    Renderer* renderer;
    glm::ivec4 color{255, 255, 255, 255};
public:
    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec4 GetAbsolutePosition() override;

    void SetPosition(glm::vec4 position, bool emit) override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w, bool emit) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    float GetZIndex() override;

    void Draw() override;

    void SetRenderingProvider(Renderer *renderer) override;

    void SetAssociatedModelId(unsigned long long int id) override;

    size_t &GetModelId() override;

    void SetColor(const glm::vec4 &color);

    const glm::vec4& GetColor();

};


#endif //LII_TEXTMODEL_H
