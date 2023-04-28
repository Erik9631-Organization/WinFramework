//
// Created by erik9 on 4/4/2023.
//

#ifndef LII_TEXT2_H
#define LII_TEXT2_H
#include "Appearance.h"
#include "TextProxy.h"
#include "DefaultRelativeZIndex.h"
#include "ScalingUtil2D.h"

class Text2 : public Appearance, public TextApi, public Movable
{
private:
    TextProxy textProxy;
    Presenter* presenter = nullptr;
    UiElement& associatedElement;
    glm::vec4 textPosition = {0.0f, 0.0f, DefaultRelativeZIndex::GetInstance()->GetIndex("TextIndex"), 1.0};
    ScalingUtil2D textScaler;
    std::vector<MoveSubscriber*> moveSubscribers;
public:

    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
    explicit Text2(UiElement &associatedElement);
    ~Text2() override;

    void OnMounted(Presenter &presenter, UiElement &element) override;
    void OnMove(EventMoveInfo e) override;
    void OnResize(EventResizeInfo e) override;

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

    void SetText(const std::wstring &text) override;

    const glm::vec4 & GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 &GetAbsolutePosition() override;

    void SetPosition(const glm::vec4 &position, bool emit) override;

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

    void SetTranslate(const glm::vec4 &offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    const glm::vec4 & GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    ScalingUtil2D& GetScales();

    void SetVisible(bool state) override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    const glm::vec4 & GetViewportSize() override;

    const glm::vec4 & GetViewportPosition() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

    void OnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void OnViewportPositionChanged(const Viewport2EventInfo &event) override;

    void OnViewportReset(const Viewport2EventInfo &event) override;
};


#endif //LII_TEXT2_H
