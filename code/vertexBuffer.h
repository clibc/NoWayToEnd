#pragma once
#include "common.h"

struct vertex_buffer
{
    // NOTE(62bit): bufferPointer and size must be specified
    // when passing this to GenerateVertexBuffer function.
    // And function will create buffer and initialize bufferID.
    float *vertices;
    size_t size;
    unsigned int bufferID;
};

struct batch
{
    float *vertex_data;
    int vertex_count;
};

void generate_vertex_buffer(vertex_buffer &vb);
void generate_dynamic_vertex_buffer(vertex_buffer &vb);
void set_vertex_attributef(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer);
inline void bind_vertex_buffer(const vertex_buffer &vb) { glBindVertexArray(vb.bufferID); }
void create_batch(batch &b, int quadCountX, int quadCountY);
