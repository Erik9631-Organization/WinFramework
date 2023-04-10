//
// Created by erik9 on 4/4/2023.
//

#ifndef LII_TEXT2_H
#define LII_TEXT2_H
#include "Appearance.h"
#include "TextProxy.h"
#include "DefaultRelativeZIndex.h"
#include "ScalingUtil2D.h"

class Text2 : public Appearance, public TextApi
{
private:
    TextProxy textProxy;
    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
    Presenter* presenter = nullptr;
    UiElement* parentElement = nullptr;
    glm::vec4 textPosition = {0.0f, 0.0f, DefaultRelativeZIndex::GetInstance()->GetIndex("TextIndex"), 1.0};
    ScalingUtil2D textScaler;
public:
    explicit Text2(UiElement* associatedElement);
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
};


#endif //LII_TEXT2_H
