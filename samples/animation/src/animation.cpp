//
// Created by czh on 18-10-31.
//

#include "animation.h"

Animation::Animation(GLuint width, GLuint height) : Game(width, height) {

}

void Animation::init() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    this->state = GAME_ACTIVE;

    ResourceManager::loadShader("sprite", defaultVshaderStr, defaultFshaderStr);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);
    ResourceManager::loadTexture2D("opening1", "../samples/animation/res/textures/opening0,1.png");
    ResourceManager::loadTexture2D("opening2", "../samples/animation/res/textures/opening1,2.png");
    ResourceManager::getShader("sprite").setVector4f("location", glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));

    spriteRender = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Animation::destory() {
    Game::destory();
}

void Animation::processInput(float dt) {

}

void Animation::update() {

}

void Animation::render(GLFWwindow *window) {
    if (this->state == GAME_ACTIVE) {
        this->displayVideo(window);
    }
}

void Animation::displayVideo(GLFWwindow *window){
    int px, py;
    float scaleX, scaleY, moveX, moveY;
    scaleX = 1.0f / 3.0f;
    scaleY = 1.0f / 8.0f;
    static int i = 0;
    for(int i = 0; i < 48; i++){
        px = i % 3;
        py = i / 6;
        moveX = (float)px / 3.0f;
        moveY = (float)py / 8.0f;

        if(i%6 < 3){
            ResourceManager::getShader("sprite").setVector4f("location", glm::vec4(scaleX, scaleY, moveX, moveY));
            spriteRender->drawSprite(ResourceManager::getTexture2D("opening1"), glm::vec2(0.0f, 0.0f), glm::vec2(1280.0f, 480.0f), 0.0f,
                                     glm::vec3(1.0f, 1.0f, 1.0f));
        } else{
            ResourceManager::getShader("sprite").setVector4f("location", glm::vec4(scaleX, scaleY, moveX, moveY));
            spriteRender->drawSprite(ResourceManager::getTexture2D("opening2"), glm::vec2(0.0f, 0.0f), glm::vec2(1280.0f, 480.0f), 0.0f,
                                     glm::vec3(1.0f, 1.0f, 1.0f));
        }
#ifdef  SML
        std::cout << moveX << "," << moveY << std::endl;
#endif
        glfwSwapBuffers(window);
        glfwPollEvents();
        usleep(1000 * 50);
    }
}

