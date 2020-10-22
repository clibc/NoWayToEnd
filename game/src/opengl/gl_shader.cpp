#include "opengl/gl_shader.h"

gl_shader::gl_shader(const char *vsPath, const char *fsPath)
{
    m_shaderProgram = LoadShaders(vsPath, fsPath);
    glUseProgram(m_shaderProgram);
}

void gl_shader::Bind()
{
    glUseProgram(m_shaderProgram);
}
