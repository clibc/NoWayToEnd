#include "gl/glew.h"
#include <vector>

class gl_vertexBuffer
{
public:
    gl_vertexBuffer(std::vector<uint32_t> &indices);
    void SetVertexAttribArray(GLuint index, GLuint size, size_t stride, const GLvoid *pointer);
    void inline Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); }
    void inline Unbind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); };

private:
    GLuint m_bufferID;
    std::vector<uint32_t> *m_indices;
};
