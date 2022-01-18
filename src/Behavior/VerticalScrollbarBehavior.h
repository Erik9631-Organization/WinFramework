//
// Created by Erik on 1/18/2022.
//

#ifndef LII_VERTICALSCROLLBARBEHAVIOR_H
#define LII_VERTICALSCROLLBARBEHAVIOR_H


#include "MouseStateSubscriber.h"
#include "ScalingUtil.h"
#include "OnAddSubscriber.h"
#include "ResizeSubscriber.h"
#include "EventResizeInfo.h"

class ScrollBar;
class Button;
class Adjustable;

/**
    the trackbar moves from position 0 to 100.
    the trackbar has a height or width.

    the size of the scrollbar is defined as following:
    scrollbarSizeInPercent = windowHeight / pageHeight //If >= 1, hide, if smaller than minSize, then ensure it is always minSize

    the empty space in which the scrollbar moves is defined as:
    emptyArea = height - scrollbarHeight

    the scrollbar position in % is defined as
    percentualPosition = (scrollbarHeight + scrollbar.Y) / emptyArea

    the height of the page is defined as following:
    pageHeight = lastElement.Y + lastElement.Width

    the transform of the elements is defined as following:
    transform.Y = pageHeight * percentualPosition

    1. Set default value. Should start at top left with full width. Height should be calculated based on current number of elements.
    2. Calculate the initial position of the elements based on the position of the trackbar.
    3. Subscribe to trackbar mouse events
    4. calculate the position of the elements based on the position of the trackbar again when capture is received.
 */



class VerticalScrollbarBehavior : public MouseStateSubscriber, public OnAddSubscriber<Component&>, public ResizeSubscriber
{
public:
    VerticalScrollbarBehavior(ScrollBar& scrollbar, Button& trackBar);
    void OnMouseDown(EventMouseStateInfo e) override;
    void OnMouseUp(EventMouseStateInfo e) override;
    void OnMousePressed(EventMouseStateInfo e) override;
    void OnMouseMove(EventMouseStateInfo e) override;
    void OnMouseEntered(EventMouseStateInfo e) override;
    void OnMouseLeft(EventMouseStateInfo e) override;
    void OnMouseCaptured(EventMouseStateInfo e) override;


    void SetPadding(int padding);
    void OnAdd(EventOnAddInfo<Component&> e) override;

    void OnResize(EventResizeInfo e) override;

private:
    int padding = 0;
    ScrollBar& associatedScrollbar;
    Button& associatedTrackBar;
    Adjustable* GetLastComponent();
    int GetPageHeight();
    float GetScrollbarPercentualPos();
    float GetScrollbarPercentualHeight();
    int minSize = 10;
    void UpdateThumbTrackSize();


};


#endif //LII_VERTICALSCROLLBARBEHAVIOR_H
