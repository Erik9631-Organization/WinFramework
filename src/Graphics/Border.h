//
// Created by erik9 on 2/19/2023.
//

#ifndef LII_BORDER_H
#define LII_BORDER_H
#include "Appearance.h"
#include "RectangleProxy.h"
#include "DefaultRelativeZIndex.h"
#include <memory>

class Border : public Appearance
{
private:
    UiElement& associatedElement;
    Presenter* presenter = nullptr;
    RectangleProxy rectangleProxy;
    glm::vec4 relativeZIndex = {0, 0, DefaultRelativeZIndex::GetInstance()->GetIndex("BorderIndex"), 0};
public:
    explicit Border(UiElement& element);
    void OnMounted(Presenter &presenter, UiElement &element) override;
    void OnMove(EventMoveInfo e) override;
    void OnResize(EventResizeInfo e) override;
    void SetColor(glm::ivec4 color);

    void SetVisible(bool state) override;

private:
    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
};


#endif //LII_BORDER_H
