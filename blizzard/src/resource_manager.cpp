//
// Created by czh on 18-9-10.
//

#include "resource_manager.h"
#include "vision/vision.h"


std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, cv::Mat> ResourceManager::images;

void ResourceManager::clear() {

}

Shader
ResourceManager::loadShader(std::string name, const GLchar *vShader, const GLchar *fShader, const GLchar *gShader) {
    Shader shader;
    shader.compile(vShader, fShader, gShader);
    shaders[name] = shader;
}

Shader ResourceManager::getShader(std::string name) {
    return shaders[name];
}

cv::Mat ResourceManager::readTexture2D(std::string file) {
    cv::Mat image = Vision::read(file, cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);
    return image;
}

int ResourceManager::loadTexture2D(std::string name, std::string file, bool save) {
    Texture2D texture2D;
    cv::Mat image = readTexture2D(file);
    if (image.data == nullptr) {
        printf("#loadTexture2D err\n");
        return -1;
    }
    if (image.channels() == 3) {
        texture2D.Image_Format = GL_BGR;
        texture2D.Internal_Format = GL_RGB;
    } else if (image.channels() == 4) {
        texture2D.Image_Format = GL_BGRA;
        texture2D.Internal_Format = GL_RGBA;
    }
    texture2D.update(image.size().width, image.size().height, image.data);
    textures[name] = texture2D;
    if (save) {
        images[name] = image;
    }
    return 0;
}

int ResourceManager::loadTexture2D(std::string name, cv::Mat image, bool save) {
    Texture2D texture2D;
    if (image.data == nullptr) {
        printf("#loadTexture2D err\n");
        return -1;
    }
    if (image.channels() == 3) {
        texture2D.Image_Format = GL_BGR;
        texture2D.Internal_Format = GL_RGB;
    } else if (image.channels() == 4) {
        texture2D.Image_Format = GL_BGRA;
        texture2D.Internal_Format = GL_RGBA;
    }
    texture2D.update(image.size().width, image.size().height, image.data);
    textures[name] = texture2D;
    if (save) {
        images[name] = image;
    }
    return 0;
}

int ResourceManager::writeTexture2D(std::string name, std::string file) {
    Texture2D texture2D;
    cv::Mat image = readTexture2D(file);
    if (images.find(name) == images.end()) {
        printf("#writeTexture2D error, w/o %s\n", name.data());
        return false;
    }
    cv::imwrite(file, images[name]);
    return true;
}

Texture2D ResourceManager::getTexture2D(std::string name) {
    if (images.find(name) == images.end()) {
        printf("#getTexture2D error, w/o %s\n", name.data());
    }
    return textures[name];
}

Texture2D ResourceManager::loadTextureVision(std::string name, cv::Mat *img) {
    //PicData picData = Vision::read(file_path);
    TextureVision textureVision;
    textureVision.update(img);
    textures[name] = textureVision;
}

