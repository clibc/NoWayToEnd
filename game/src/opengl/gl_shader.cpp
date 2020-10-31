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

    void shader::SetUniform1f(GLuint loc, float value)
    {
        glUniform1f(loc, value);
    }

    void shader::SetUniform3fv(GLuint loc, glm::vec3 vector)
    {
        glUniform3fv(loc, 3, glm::value_ptr(vector));
    }

}; // namespace ogl
