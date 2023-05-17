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
    glm::vec3 textPosition = {0.0f, 0.0f, DefaultRelativeZIndex::GetInstance()->GetIndex("TextIndex")};
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

    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    ScalingUtil2D& GetScales();

    void SetVisible(bool state) override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec3 &input) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec3 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void AddViewportSubscriber(ViewportSubscriber &subscriber) override;

    void RemoveViewportSubscriber(ViewportSubscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const ViewportEventInfo &event) override;

    void NotifyOnViewportPositionChanged(const ViewportEventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const ViewportEventInfo &event) override;

    void OnViewportSizeChanged(const ViewportEventInfo &event) override;

    void OnViewportPositionChanged(const ViewportEventInfo &event) override;

    void OnViewportReset(const ViewportEventInfo &event) override;
};


#endif //LII_TEXT2_H
