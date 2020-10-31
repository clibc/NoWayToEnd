#include "opengl/gl_shader.h"

namespace ogl
{
    shader::shader(const char *vsPath, const char *fsPath)
    {
        m_shaderProgram = LoadShaders(vsPath, fsPath);
        glUseProgram, (m_shaderProgram);
    }

    void shader::ChangeUniformMatrix(GLint location, glm::mat4 matrix)
    {
        // TODO(62bit): change uniforms
        glUseProgram(m_shaderProgram);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void shader::SetUniform1f(const char *name, float value)
    {
        glUseProgram(m_shaderProgram);
        GLint loc = glGetUniformLocation(m_shaderProgram, name);
        glUniform1f(loc, value);
    }

    void shader::SetUniform3fv(const char *name, glm::vec3 vector)
    {
        glUseProgram(m_shaderProgram);
        GLint loc = glGetUniformLocation(m_shaderProgram, name);
        glUniform3f(loc, vector.x, vector.y, vector.z);
    }

}; // namespace ogl
