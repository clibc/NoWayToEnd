#include "gl_vertexBuffer.h"

gl_vertexBuffer::gl_vertexBuffer(std::vector<uint32_t> &indices)
    : m_indices(&indices)
{
    glCreateBuffers(1, &m_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glBufferData(GL_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);
}

void gl_vertexBuffer::SetVertexAttribArray(GLuint index, GLuint size, size_t stride, const GLvoid *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}
