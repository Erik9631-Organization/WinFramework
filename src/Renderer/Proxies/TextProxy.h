//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_TEXTPROXY_H
#define LII_TEXTPROXY_H


#include "Movable.h"
#include "RenderProxy.h"
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "RenderingProxyMessageSender.h"
#include "api/TextApi.h"

class TextModel;

class TextProxy : public TextApi, public RenderProxy, public MoveSubscriber, public Movable
{
private:
    TextModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    size_t id = 0;
    RenderingProxyMessageSender messageSender;
public:
    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 & GetAbsolutePosition() override;

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

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    const size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void OnMove(EventMoveInfo e) override;

    void SetText(const std::wstring& text) override;

    void SetFontSize(float fontSize) override;

    void SetFontAlignment(FontAlignment alignment) override;

    void SetFontLineAlignment(FontAlignment alignment) override;

    void SetColor(const glm::ivec4 &color) override;

    void SetFontFamily(const std::wstring &fontFamily) override;

    const glm::ivec4 &GetColor() override;

    const std::wstring &GetText() override;

    const std::wstring &GetFontFamily() override;

    FontAlignment GetFontLineAlignment() override;

    FontAlignment GetFontAlignment() override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    SubCommands GetModelRequestCommand() override;

    void SetViewPortSize(const glm::vec4 &vec4) override;

    void SetViewPortPosition(const glm::vec4 &vec4) override;

    glm::vec4 &GetViewPortSize() override;

    glm::vec4 &GetViewPortPosition() override;

    void ResetViewPort() override;

};


#endif //LII_TEXTPROXY_H
