//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RECTANGLEPROXY_H
#define LII_RECTANGLEPROXY_H
#include "Movable.h"
#include "Resizable.h"
#include <vector>
#include "RenderProxy.h"
#include <unordered_map>
#include "Commands.h"
#include "ModelViewport.h"
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "RenderingProxyMessageSender.h"
#include <concurrentqueue.h>

class RenderingConsumer;
class RectangleModel;
class RenderMessage;

class RectangleProxy : public Movable, public Resizable, public RenderProxy, public MoveSubscriber, public ResizeSubscriber
{
private:
    RectangleModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    std::vector<ResizeSubscriber*>resizeSubscribers;
    RenderingProxyMessageSender messageSender;

    void SendRenderingMessage(std::unique_ptr<RenderMessage> message);
public:

    void SetThickness(float thickness);

    void SetViewPortPosition(const glm::vec2& position);

    void SetViewPortSize(const glm::vec2 &size);

    void ResetViewPort();

    void SetFill(bool fill);

    void SetColor(const glm::vec4 &color);

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

    glm::vec4 GetSize() override;

    float GetWidth() override;

    float GetHeight() override;

    void SetSize(glm::vec4 size, bool emit) override;

    void SetSize(glm::vec4 size) override;

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

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    [[nodiscard]] const ModelViewport& GetViewport() const;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;
};


#endif //LII_RECTANGLEPROXY_H
