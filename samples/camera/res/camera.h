//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_CAMERA_H
#define OPENGL_PRO_CAMERA_H

#include <game.h>

class Camera : public Game {
public:
    SpriteRenderer *spriteRender;

    cv::VideoCapture capture;

    Camera(GLuint width, GLuint height);

    void init();

    void destory();

    void processInput();

    void update();

    void render(GLFWwindow *window);
};


#endif //OPENGL_PRO_CAMERA_H
