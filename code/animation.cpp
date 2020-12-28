#include "animation.h"

void create_animation(animation *anim, const texture *tex, int clip_size)
{
    anim->tex = tex;
    anim->clip_size = clip_size;
    int clip_count = anim->tex->idata.width / anim->clip_size;
    anim->clip_count = clip_count;
    anim->clips = (glm::vec2 *)malloc(sizeof(glm::vec2) * 4 * clip_count);

    float normal_size = (float)anim->clip_size / (float)anim->tex->idata.width;
    int count = 0;
    for (int i = 0; i < clip_count; ++i)
    {
        anim->clips[count + 0] = glm::vec2(normal_size + (normal_size * float(i)), 1.0f);
        anim->clips[count + 1] = glm::vec2(normal_size + (normal_size * float(i)), 0.0f);
        anim->clips[count + 2] = glm::vec2(normal_size * i, 0.0f);
        anim->clips[count + 3] = glm::vec2(normal_size * i, 1.0f);

        count += 4;
    }
}
