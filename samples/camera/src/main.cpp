//
// Created by czh on 18-10-31.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "dconfig.h"

Camera blizzard(SCREEN_WIDTH, SCREEN_HEIGHT);

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            blizzard.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            blizzard.keys[key] = GL_FALSE;
    }
}

void mainLoop() {

}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blizzard", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    blizzard.init();

    while (!glfwWindowShouldClose(window)) {
        clock_t start = clock();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blizzard.processInput();
        blizzard.render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        clock_t end = clock();
        int time_ms = (double) (end - start) / CLOCKS_PER_SEC * 1000;
        if ((33 - time_ms) > 0) {
            usleep((33 - time_ms));
        }
    }

    glfwTerminate();

    return 0;
}