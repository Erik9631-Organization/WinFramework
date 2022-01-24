//
// Created by Erik on 1/18/2022.
//

#ifndef LII_SCROLLBAR_H
#define LII_SCROLLBAR_H
#include "Panel.h"
#include "Button.h"
#include "VerticalScrollbarBehavior.h"

class MouseStateSubscriber;

class ScrollBar : public Panel
{
public:
    ScrollBar(int x, int y, int width, int height, const string &name);
    ScrollBar(const string &name);
    ScrollBar();
    void Control(Component* component);
    Component* GetControlledComponent();
    void ClearControl();
private:
    Button thumbTrack;
    Component* controlledComponent = nullptr;
    VerticalScrollbarBehavior scrollbarBehavior;

};


#endif //LII_SCROLLBAR_H
