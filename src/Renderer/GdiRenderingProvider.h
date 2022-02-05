//
// Created by Erik on 22/01/24.
//

#ifndef LII_GDIRENDERINGPROVIDER_H
#define LII_GDIRENDERINGPROVIDER_H
#include "RenderingProvider.h"
#include "ResizeSubscriber.h"
class CoreWindow;
class UiElement;
namespace Gdiplus
{
    class Region;
}

template<typename T> class MultiTree;


class GdiRenderingProvider : public RenderingProvider, public ResizeSubscriber
{
public:
    void AssignRenderer() override;
    void OnResize(EventResizeInfo e) override;
    void OnInit(CoreWindow &coreWindowFrame) override;
    void OnDestroy(CoreWindow &coreWindow) override;
    void OnRemove(CoreWindow &coreWindow) override;
private:
    CoreWindow* coreWindowframe;
    void AssignGraphicsToNodes(MultiTree<UiElement&>& node, Gdiplus::Region& clippingRegion);
    void CleanBackBuffer();
    void AssignGraphicsToNodes();
    HDC GetSecondaryDC();
    HWND windowHandle;
    HDC windowHdc;
    HDC secondaryDc;
    HBITMAP secondaryBitmap;

};


#endif //LII_GDIRENDERINGPROVIDER_H
