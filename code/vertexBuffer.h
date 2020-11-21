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

void GenerateVertexBuffer(vertex_buffer &vb);
void SetAttributeF(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer);
