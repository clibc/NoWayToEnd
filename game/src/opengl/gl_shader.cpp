#include "opengl/gl_shader.h"

namespace ogl
{
    shader::shader(const char *vsPath, const char *fsPath)
    {
        m_shaderProgram = LoadShaders(vsPath, fsPath);
        glUseProgram(m_shaderProgram);
    }

    void shader::ChangeUniformMatrix(GLint location, glm::mat4 matrix)
    {
        // TODO(62bit): change uniforms
        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
};