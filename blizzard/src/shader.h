//
// Created by czh on 18-9-10.
//

#ifndef OPENGL_PRO_SHADER_H
#define OPENGL_PRO_SHADER_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "dconfig.h"

class Shader {
public:

    Shader() {};

    int ID;

    Shader &use();

    void compile(const GLchar *vShaderSource, const GLchar *fShaderSource, const GLchar *gShaderSource);

    void setInteger(const GLchar *name, GLint value, GLboolean useShader = true);

    void setFloat(const GLchar *name, const float &value, GLboolean useShader = true);

    void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = true);

    void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = true);

    void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = true);

    void setMatrix3(const GLchar *name, const glm::mat3 &matrix, GLboolean useShader = true);

    void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = true);

private:
    void checkCompileErrors(GLuint object, std::string type);
};


#endif //OPENGL_PRO_SHADER_H
