//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_SPORT_H
#define OPENGL_PRO_SPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <unistd.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


class Game {
public:

    GameState state;
    GLuint width, height;
    GLboolean keys[1024];

    Game(GLuint width, GLuint height);

    ~Game();

    virtual void init();

    virtual void destory();

    virtual void processInput(float dt);

    virtual void update();

    virtual void render(GLFWwindow *window);

    const char *defaultVshaderStr =
            "#version 330 core                                  \n"
            "layout (location = 0) in vec4 vertex;              \n"
            "out vec2 TexCoords;                                \n"
            "uniform mat4 model;                                \n"
            "uniform mat4 projection;                           \n"
            "uniform vec4 location;                             \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   TexCoords.x = vertex.z * location.x + location.z;\n"
            "   TexCoords.y = vertex.w * location.y + location.w;\n"
            "   gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);\n"
            "}                                                  \n";

    const char *defaultFshaderStr =
            "#version 330 core                                  \n"
            "precision mediump float;                           \n"
            "in vec2 TexCoords;                                 \n"
            "out vec4 color;                                    \n"
            "uniform sampler2D image;                           \n"
            "uniform vec3 spriteColor;                          \n"
            "void main()                                        \n"
            "{                                                  \n"
            "   color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n"
            "}                                                  \n";



private:
};


#endif //OPENGL_PRO_SPORT_H
