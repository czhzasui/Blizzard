//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_CAMERA_H
#define OPENGL_PRO_CAMERA_H

#include <game.h>
#include "calib/zhu.h"
#include <calib/zhang.h>
#include "trackline/trackline.h"

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
};


#endif //OPENGL_PRO_CAMERA_H
