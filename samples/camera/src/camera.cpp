//
// Created by czh on 18-10-31.
//

#include <calib/checkerborad.h>
#include "camera.h"

Camera::Camera(GLuint width, GLuint height) : Game(width, height) {

}

void Camera::init() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    this->state = GAME_ACTIVE;

    ResourceManager::loadShader("sprite", defaultVshaderStr, defaultFshaderStr);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f,
                            1.0f);
    ResourceManager::getShader("sprite").setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);
    ResourceManager::getShader("sprite").setVector4f("location", glm::vec4(1.0f, 1.0f, 0.0f, 0.0f));

    spriteRender = new SpriteRenderer(ResourceManager::getShader("sprite"));

    capture.open(0);
    if (!capture.isOpened()) {
        printf("#camera open failure\n");
    }
//    printf("#makeCheckerboard\n");
//    Checkerborad::makeCheckerboard(SCREEN_WIDTH, SCREEN_HEIGHT, 10, 10);
//
//    cv::Mat cb_source = Vision::read("../samples/camera/res/j59r002.jpg");
//    ResourceManager::loadTexture2D("cb_source", cb_source);
//    Zhang::init(cb_source, 9, 4);


}

void Camera::destory() {
    Game::destory();
}

void Camera::processInput() {
    capture >> frame;
    ResourceManager::loadTexture2D("cb_final", frame);
}

void Camera::update() {

}

void Camera::render(GLFWwindow *window) {
    if (this->state == GAME_ACTIVE) {
        spriteRender->drawSprite(ResourceManager::getTexture2D("cb_final"), glm::vec2(0, 0),
                                 glm::vec2(1280, 480), 0.0f);
        usleep(1000 * 30);
    }
}


