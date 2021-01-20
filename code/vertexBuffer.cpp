#include "vertexBuffer.h"

void generate_vertex_buffer(vertex_buffer &vb)
{
    glGenBuffers(1, &vb.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb.size, (float *)vb.vertices, GL_STATIC_DRAW);
}

void generate_dynamic_vertex_buffer(vertex_buffer &vb)
{
    glGenBuffers(1, &vb.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb.size, (float *)vb.vertices, GL_DYNAMIC_DRAW);
}

void set_vertex_attributef(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}

void create_batch(batch &b, int quadCountX, int quadCountY)
{
    b.vertex_count = quadCountX * quadCountY * 5 * 4;
    b.vertex_data = (float *)malloc(sizeof(float) * b.vertex_count);
    float quadWidth = 1.0f / (float)quadCountX;
    float quadHeight = 1.0f / (float)quadCountY;
    for (int i = 0; i < quadCountX * quadCountY; ++i)
    {
        b.vertex_data[(i * 20) + 0] = quadWidth + (quadWidth * (float)i);
        b.vertex_data[(i * 20) + 1] = quadHeight + (quadHeight * (float)i);
        b.vertex_data[(i * 20) + 2] = 0.0f;
        b.vertex_data[(i * 20) + 3] = 1.0f;
        b.vertex_data[(i * 20) + 4] = 1.0f;

        b.vertex_data[(i * 20) + 5] = quadWidth + (quadWidth * (float)i);
        b.vertex_data[(i * 20) + 6] = -(quadHeight + (quadHeight * (float)i));
        b.vertex_data[(i * 20) + 7] = 0.0f;
        b.vertex_data[(i * 20) + 8] = 1.0f;
        b.vertex_data[(i * 20) + 9] = 0.0f;

        b.vertex_data[(i * 20) + 10] = -(quadWidth + (quadWidth * (float)i));
        b.vertex_data[(i * 20) + 11] = -(quadHeight + (quadHeight * (float)i));
        b.vertex_data[(i * 20) + 12] = 0.0f;
        b.vertex_data[(i * 20) + 13] = 0.0f;
        b.vertex_data[(i * 20) + 14] = 0.0f;

        b.vertex_data[(i * 20) + 15] = -(quadWidth + (quadWidth * (float)i));
        b.vertex_data[(i * 20) + 16] = quadHeight + (quadHeight * (float)i);
        b.vertex_data[(i * 20) + 17] = 0.0f;
        b.vertex_data[(i * 20) + 18] = 0.0f;
        b.vertex_data[(i * 20) + 19] = 1.0f;
    }
}
