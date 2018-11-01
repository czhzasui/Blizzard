//
// Created by czh on 18-9-10.
//

#include "game.h"

Game::Game(GLuint width, GLuint height) : state(GAME_ACTIVE), width(width), height(height) {
}

Game::~Game() {

}

void Game::init() {

}

void Game::destory() {
    ResourceManager::clear();
}

void Game::processInput(float dt) {

}

void Game::update() {

}

void Game::render(GLFWwindow *window) {

}






