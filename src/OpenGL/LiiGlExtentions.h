//
// Created by Erik on 11/02/22.
//

#ifndef LII_LIIGLEXTENTIONS_H
#define LII_LIIGLEXTENTIONS_H

#endif //LII_LIIGLEXTENTIONS_H
#include "wglext.h"
#include "glext.h"

static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLBINDBUFFERPROC glBindBuffer;


void LoadExtentions()
{
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
    if(!wglCreateContextAttribsARB)
    {
        CoreWindow::ConsoleWrite("Error getting wglCreateContextAttribsARB" );
        system("PAUSE");
        exit(0);
    }
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");

    if(!wglChoosePixelFormatARB)
    {
        CoreWindow::ConsoleWrite("Error getting wglChoosePixelFormatARB" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");

    if(!glGenBuffers)
    {
        CoreWindow::ConsoleWrite("Error getting glGenBuffers" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }


}
