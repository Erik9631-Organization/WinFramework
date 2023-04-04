//
// Created by erik9 on 2/19/2023.
//

#ifndef LII_BORDER_H
#define LII_BORDER_H
#include "Appearance.h"
#include "RectangleProxy.h"
#include "RelativeZIndex.h"
#include <memory>

class Border : public Appearance
{
private:
    UiElement& associatedElement;
    Presenter* presenter = nullptr;
    std::unique_ptr<RectangleProxy> rectangleProxy;
    glm::vec4 relativeZIndex = {0, 0, 0, RelativeZIndex::GetInstance()->GetIndex("BorderIndex")};
public:
    Border(UiElement& element);
    void OnMounted(Presenter &presenter, UiElement &element) override;
    void OnMove(EventMoveInfo e) override;
    void OnResize(EventResizeInfo e) override;
    void SetColor(glm::ivec4 color);

private:
    float GetRelativeZIndex() override;
    void SetRelativeZIndex(float relativeZIndex) override;
};


#endif //LII_BORDER_H
