//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_RESOURCE_MANAGER_H
#define OPENGL_PRO_RESOURCE_MANAGER_H

#include <iostream>
#include <map>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include "shader.h"
#include "texture.h"
#include "vision/vision.h"

class ResourceManager {
public:

    static std::map<std::string, Shader> shaders;

    static std::map<std::string, Texture2D> textures;

    static std::map<std::string, cv::Mat> images;

    static Shader loadShader(std::string name, const GLchar *vShader, const GLchar *fShader, const GLchar *gShader = nullptr);

    static Shader getShader(std::string name);

    static cv::Mat readTexture2D(std::string file);

    static int loadTexture2D(std::string name, std::string file, bool save = true);

    static int loadTexture2D(std::string name, cv::Mat image, bool save = true);

    static int writeTexture2D(std::string name, std::string file);

    static Texture2D getTexture2D(std::string name);

    static void clear();

private:
    ResourceManager() {}

};


#endif //OPENGL_PRO_RESOURCE_MANAGER_H
