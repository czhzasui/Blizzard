//
// Created by czh on 18-9-10.
//

#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader shader) {
    this->shader = shader;

    this->init();

}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color) {
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

    glBindVertexArray(this->VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    glBindVertexArray(0);
}

void SpriteRenderer::init() {
    GLuint VBO;
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid *) (0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
