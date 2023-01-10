//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RECTANGLEPROXY_H
#define LII_RECTANGLEPROXY_H
#include "Movable.h"
#include "Resizable.h"
#include <vector>
#include "RenderProxy.h"
#include "Vector4.h"
#include <unordered_map>
#include "Commands.h"

class RenderingConsumer;
class RectangleModel;
class RenderMessage;

class RectangleProxy : public Movable, public Resizable, public RenderProxy
{
private:
    static constexpr unsigned int numberOfCommands = 6;
    RenderingConsumer* renderingConsumer = nullptr;
    RectangleModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    std::vector<ResizeSubscriber*>resizeSubscribers;
    std::unordered_map<SubCommands, RenderMessage*> copyOnWriteMap;
public:
    RectangleProxy();

    void SetViewPort(const glm::vec2 &position, const glm::vec2 &size);

    void SetFill(bool fill);

    void SetRenderingConsumer(RenderingConsumer *consumer) override;

    void SetColor(const Vector4& color);

    glm::vec2 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec2 GetAbsolutePosition() override;

    void SetPosition(glm::vec2 position, bool emit) override;

    void SetPosition(glm::vec2 position) override;

    void SetPosition(float x, float y, bool emit) override;

    void SetPosition(float x, float y) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec2 offset, bool emit) override;

    void SetTranslate(glm::vec2 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec2 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    glm::vec2 GetSize() override;

    float GetWidth() override;

    float GetHeight() override;

    void SetSize(glm::vec2 size, bool emit) override;

    void SetSize(glm::vec2 size) override;

    void SetSize(float width, float height, bool emit) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width, bool emit) override;

    void SetWidth(float width) override;

    void SetHeight(float height, bool emit) override;

    void SetHeight(float height) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void NotifyOnResizeSubscribers(EventResizeInfo event) override;

    void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;

    size_t & GetAssociatedModelId() override;

    void SetAssociatedModel(RenderingModel *model) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

};


#endif //LII_RECTANGLEPROXY_H
