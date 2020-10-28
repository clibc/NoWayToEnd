#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "opengl/loadShaders.hpp"

namespace ogl
{
    class shader
    {
    public:
        shader() = default;
        shader(const char *vsPath, const char *fsPath);
        inline void Bind() { glUseProgram(m_shaderProgram); }
        void ChangeUniformMatrix(GLint location, glm::mat4 matrix);
        inline GLint GetUniformLocation(const char *name) { return glGetUniformLocation(m_shaderProgram, name); }

    private:
        GLuint m_shaderProgram;
    };
}; 