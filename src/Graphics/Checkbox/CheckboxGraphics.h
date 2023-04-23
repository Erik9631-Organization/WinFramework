//
// Created by erik9 on 4/22/2023.
//

#ifndef LII_CHECKBOXGRAPHICS_H
#define LII_CHECKBOXGRAPHICS_H
#include "Appearance.h"
#include "DefaultRelativeZIndex.h"
#include "Border.h"
#include "Text2.h"

class CheckboxGraphics : public Appearance
{
private:
    RectangleProxy checkboxBorder;
    TextProxy checkBoxChar;
    glm::vec4 checkboxPosition = {0.02, 0.3f, DefaultRelativeZIndex::GetInstance()->GetIndex("None"), 0};
    ScalingUtil2D checkboxScaler;
    UiElement& associatedElement;
    bool checked = false;
    void UpdateGraphics();

public:
    void SetCheck(bool state);

    bool IsChecked();

    explicit CheckboxGraphics(UiElement &element);

    float GetRelativeZIndex() override;

    void SetRelativeZIndex(float relativeZIndex) override;

    void SetVisible(bool state) override;

    void OnMounted(Presenter &presenter, UiElement &element) override;

    void OnMove(EventMoveInfo e) override;

    void OnResize(EventResizeInfo e) override;

    void ResetViewport() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    glm::vec4 &GetViewportSize() override;

    glm::vec4 &GetViewportPosition() override;

};


#endif //LII_CHECKBOXGRAPHICS_H
