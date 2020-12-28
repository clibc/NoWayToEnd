#pragma once
#include "texture.h"

struct animation
{
    const texture *tex;
    int clip_size;
    unsigned int clip_count;
    glm::vec2 *clips;
};

void create_animation(animation *anim, const texture *tex, int clip_size);
