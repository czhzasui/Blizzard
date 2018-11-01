//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_BLIZZARD_H
#define OPENGL_PRO_BLIZZARD_H

#include <game.h>

class Animation : public Game {
public:
    SpriteRenderer *spriteRender;

    Animation(GLuint width, GLuint height);

    void init();

    void destory();

    void processInput(float dt);

    void update();

    void render(GLFWwindow *window);

    void displayVideo(GLFWwindow *window);
};


#endif //OPENGL_PRO_BLIZZARD_H
