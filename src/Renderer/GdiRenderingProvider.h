//
// Created by Erik on 22/01/24.
//

#ifndef LII_GDIRENDERINGPROVIDER_H
#define LII_GDIRENDERINGPROVIDER_H
#include "RenderingProvider.h"
#include "ResizeSubscriber.h"
#include "DrawData2D.h"
#include <functional>
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
    void Render();
    void SyncData(MultiTree<UiElement&>& node);
    HDC GetSecondaryDC();
    void NotifyOnSyncComplete(OnSyncCompleteSubject &src) override;
    void AddOnSyncSubscriber(OnSyncCompleteSubscriber &subscriber) override;
    void RemoveOnSyncSubscriber(OnSyncCompleteSubscriber &subscriber) override;
    HWND windowHandle;
    HDC windowHdc;
    HDC secondaryDc;
    HBITMAP secondaryBitmap;
    DrawData2D defaultDrawData;
    OnSyncCompleteSubscriber* onSyncCompleteSubscriber = nullptr;

};


#endif //LII_GDIRENDERINGPROVIDER_H
