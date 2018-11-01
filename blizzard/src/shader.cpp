//
// Created by czh on 18-9-10.
//

#include "shader.h"

void Shader::compile(const GLchar *vShaderSource, const GLchar *fShaderSource, const GLchar *gShaderSource) {
    GLuint sVertex, sFragment, gShader;

    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vShaderSource, nullptr);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fShaderSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    if (gShaderSource != nullptr) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &gShaderSource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }

    this->ID = glCreateProgram();
#ifdef SML
    std::cout << "#glCreateProgram ID:" << this->ID;
    if (gShaderSource == nullptr) {
        std::cout << " w/o_gShader" << std::endl;
    } else {
        std::cout << " w/_gShader" << std::endl;
    }
#endif
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (gShaderSource != nullptr)
        glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (gShaderSource != nullptr)
        glDeleteShader(gShader);

}

Shader &Shader::use() {
    glUseProgram(this->ID);
    //std::cout << "#Use glUseProgram: " << this->ID << std::endl;
    return *this;
}

void Shader::setInteger(const GLchar *name, GLint value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) {
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << "\n -- ----------------------------------------------------- "
                      << std::endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                      << infoLog << "\n -- ----------------------------------------------------- "
                      << std::endl;
        }
    }
}



