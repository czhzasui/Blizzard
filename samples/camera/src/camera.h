//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_CAMERA_H
#define OPENGL_PRO_CAMERA_H

#include <game.h>
#include "calib/zhu.h"

class Camera : public Game {
public:
    SpriteRenderer *spriteRender;
    cv::Mat frame;

    cv::VideoCapture capture;

    Camera(GLuint width, GLuint height);

    void init();

    void destory();

    void processInput();

    void update();

    void render(GLFWwindow *window);

private:
    char *cameraVshaderStr =
            "#version 330 core                                  \n"
            "layout (location = 0) in vec3 vPos;                \n"
            "layout (location = 1) in vec2 vTex;                \n"
            "uniform mat4 model;                                \n"
            "uniform mat4 view;                                 \n"
            "uniform mat4 proj;                                 \n"
            "out vec2 fTex;                                     \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   gl_Position = proj * view * model * vec4(vPos, 1.0f);\n"
            "   fTex = vec2(vTex.x, vTex.x);                    \n"
            "}                                                  \n";

    char *cameraFshaderStr =
            "#version 330 core                                  \n"
            "precision mediump float;                           \n"
            "in vec2 fTex;                                      \n"
            "out vec4 color;                                    \n"
            "uniform sampler2D image;                           \n"
            "uniform vec3 spriteColor;                          \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   color = vec4(spriteColor, 1.0) * texture(image, fTex);\n"
            "}                                                  \n";

    GLfloat cameraVertices[30] = {
            // Pos      // Tex
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    };

    GLuint cameraIndices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
};


#endif //OPENGL_PRO_CAMERA_H
