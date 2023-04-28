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
    static constexpr glm::vec4 defaultVec = glm::vec4{0, 0, 0, 1};
    static constexpr glm::ivec4 defaultColorVec = glm::vec4{0, 0, 0, 1};
    static std::wstring defaultText;
    TextModel* model = nullptr;
    std::vector<MoveSubscriber*>moveSubscribers;
    size_t id = 0;
    RenderingProxyMessageSender messageSender;
    std::vector<Viewport2Subscriber*> viewPortSubscribers;
public:
    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;

    const size_t & GetAssociatedModelId() override;

    void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

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

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec4 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

};


#endif //LII_TEXTPROXY_H
