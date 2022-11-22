//
// Created by Erik on 1/18/2022.
//

#ifndef LII_SCROLLBAR_H
#define LII_SCROLLBAR_H
#include "Panel.h"
#include "Button.h"
#include "VerticalScrollbarBehavior.h"
#include <memory>

class MouseStateSubscriber;

class ScrollBar : public Panel
{
public:
    ScrollBar(int x, int y, int width, int height, const std::string &name);
    ScrollBar(const std::string &name);
    ScrollBar();
    /**
     * \remark If control is called, the controlled component will also become owner of the scrollbar.
     * If the scrollbar owner dies, the scrollbar will be deleted
     * \param component The component the scrollbar controls
     */
    static void Control(UiElement *component, std::unique_ptr<ScrollBar> scrollbar);
    UiElement* GetControlledComponent();
    void ClearControl();
private:
    Button* thumbTrack;
    UiElement* controlledComponent = nullptr;
    std::unique_ptr<VerticalScrollbarBehavior> scrollbarBehavior;

};


#endif //LII_SCROLLBAR_H
