//
// Created by czh on 18-10-15.
//

#ifndef OPENGL_PRO_DISPLAY_H
#define OPENGL_PRO_DISPLAY_H

#include <glad/glad.h>
#include <EGL/egl.h>
#include <iostream>
class EGL{
public:
    static EGLDisplay eglDisplay;
    static EGLContext context, context1;
    static EGLSurface eglSurface;
    static NativeDisplayType display;
    static NativeWindowType window;

    static bool init_EGL(int fb_num = 0);

    static void swapBuffer();
};


#endif //OPENGL_PRO_DISPLAY_H
