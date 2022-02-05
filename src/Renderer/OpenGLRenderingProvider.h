//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERINGPROVIDER_H
#define LII_OPENGLRENDERINGPROVIDER_H
#include "RenderingProvider.h"
#include <Windows.h>
typedef HGLRC WINAPI wglCreateContextAttribsARB (HDC hdc, HGLRC hShareContext, const int *attribList);
typedef bool wglChoosePixelFormatARB (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);


class OpenGLRenderingProvider : public RenderingProvider
{
public:
    void AssignRenderer() override;
    void OnInit(CoreWindow &coreWindowFrame) override;
    void OnDestroy(CoreWindow &coreWindow) override;
    void OnRemove(CoreWindow &coreWindow) override;
private:
    void GetGlExtensions();
    void PrepareWindowRenderer(CoreWindow& window);
    static wglCreateContextAttribsARB* pWglCreateContextAttribsARB;
    static wglChoosePixelFormatARB* pWglChoosePixelFormatARB;
    HGLRC openGlContext;
    HDC windowDc;
};


#endif //LII_OPENGLRENDERINGPROVIDER_H
