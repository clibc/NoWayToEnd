#include "GL/glew.h"
#include "opengl/loadShaders.hpp"

class gl_shader
{
public:
    gl_shader(const char *vsPath, const char *fsPath);
    void Bind();
    void ChangeUniform();

private:
    GLuint m_shaderProgram;
};