//
// Created by czh on 18-10-15.
//

#include "egl.h"

/*
EGLDisplay EGL::eglDisplay;
EGLContext EGL::context;
EGLContext EGL::context1;
EGLSurface EGL::eglSurface;
NativeDisplayType EGL::display;

bool EGL::init_EGL(int fb_num) {
    EGLint w, h, dummy;
    EGLint numConfigs;
    EGLConfig config;
    // EGLContext context;

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(eglDisplay, 0, 0);

    const EGLint attribs[] =
            {
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_NONE
            };

    eglChooseConfig(eglDisplay, attribs, &config, 1, &numConfigs);

//    eglSurface = eglCreateWindowSurface(eglDisplay, config, window, NULL);

    if (eglSurface == EGL_NO_SURFACE) {
        printf("eglCreateWindowSurface failed\n");
        return false;
    }

    EGLint ctxAttribs[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
            };
    context = eglCreateContext(eglDisplay, config, NULL, ctxAttribs);
    context1 = eglCreateContext(eglDisplay, config, context, ctxAttribs);
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &w);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &h);

    if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, context) == EGL_FALSE) {
        return false;
    }
    return true;
}

void EGL::swapBuffer() {
    eglSwapBuffers(eglDisplay, eglSurface);
    glClear(GL_COLOR_BUFFER_BIT);
}
*/
