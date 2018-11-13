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

private:

    GLfloat animationVertices[16] = {
            // Pos      // Tex
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    GLuint animationIndices[6] = {
            0, 1, 2,
            0, 2, 3
    };
};


#endif //OPENGL_PRO_BLIZZARD_H
