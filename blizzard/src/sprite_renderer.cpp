//
// Created by czh on 18-9-10.
//

#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader shader, GLfloat *vertices, GLuint length) {
    this->shader = shader;

    this->init2(vertices, length);

}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->VAO);
}

void
SpriteRenderer::drawSprite2D(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color,
                             GLuint *indices) {
    static bool hasInit = false;
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));//move
    //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));//rotate
    //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); //scale

    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    if (indices == nullptr) {
        glBindVertexArray(this->VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, defaultIndices);
        glBindVertexArray(0);
        printf("#Using defaultIndices\n");
    } else {
        glBindVertexArray(this->VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        glBindVertexArray(0);
        if (!hasInit) {
            printf("#Using extra Indices\n");
            hasInit = true;
        }
    }

}

void
SpriteRenderer::drawSprite3D(Texture2D texture, glm::vec3 position, glm::vec3 size, GLfloat rotate, glm::vec3 color,
                             GLuint *indices) {
    static bool hasInit = false;
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position));//move
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));//rotate
    model = glm::scale(model, glm::vec3(size)); //scale
    ResourceManager::getShader("camera").setMatrix4("model", model);

    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(45.0f), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);
    ResourceManager::getShader("camera").setMatrix4("proj", proj);

    glm::mat4 view = glm::mat4(1.0f);
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    ResourceManager::getShader("camera").setMatrix4("view", view);


    this->shader.setVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    if (indices == nullptr) {
        glBindVertexArray(this->VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, defaultIndices);
        glBindVertexArray(0);
        printf("#Using defaultIndices\n");
    } else {
        glBindVertexArray(this->VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        glBindVertexArray(0);
        if (!hasInit) {
            printf("#Using extra Indices\n");
            hasInit = true;
        }
    }
}

void SpriteRenderer::init1(GLfloat *vertices, GLuint length) {
    GLuint VBO;
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    if (vertices == nullptr) {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(defaultVertices), defaultVertices, GL_STATIC_DRAW);
    } else {
        if (length == 0) {
            printf("#Error: vertices length of SpriteRenderer\n");
        }
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
        printf("#ok1\n");
    }

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid *) (0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::init2(GLfloat *vertices, GLuint length) {
    GLuint VBO;
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    if (vertices == nullptr) {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(defaultVertices), defaultVertices, GL_STATIC_DRAW);
        printf("#Using defaultVertices\n");
    } else {
        if (length == 0) {
            printf("#Error: vertices length of SpriteRenderer\n");
        }
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
        printf("#Using extra vertices\n");

    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}