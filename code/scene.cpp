#include "scene.h"

void scene_init(scene &scn)
{
    create_shader(scn.anim_shader, "../code/shaders/vertex.vs", "../code/shaders/fragment.vs");
    create_shader(scn.reg_shader, "../code/shaders/regular.vs", "../code/shaders/fragment.vs");

    static float vertices[] = {
        -1.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -1.5f, 0.5f, 0.0f,

        0.5f, -0.5f, 0.0f,
        1.5f, -0.5f, 0.0f,
        1.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f};

    batch bat;
    create_batch(bat, 10, 10);

    scn.anim_vertex.vertices = bat.vertex_data;
    scn.anim_vertex.size = (size_t)bat.vertex_count * sizeof(float);
    generate_dynamic_vertex_buffer(scn.anim_vertex);
    set_vertex_attributef(scn.anim_vertex, 0, 3, 5 * sizeof(float), (void *)0);
    set_vertex_attributef(scn.anim_vertex, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    scn.projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    set_uniform_mat4(scn.anim_shader, "projection", scn.projection);
}
