//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_SPRITE_H
#define OPENGL_PRO_SPRITE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "texture.h"
#include "dconfig.h"
#include "resource_manager.h"
#include "vision/vision.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader shader);

    ~SpriteRenderer();

    void drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    GLuint VAO;

    void init();

    GLfloat vertices[16] = {
            // Pos      // Tex
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    const GLuint indices[6] = {
            0, 1, 2,
            0, 2, 3
    };
};


#endif //OPENGL_PRO_SPRITE_H
