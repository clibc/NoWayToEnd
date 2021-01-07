#include "scene.h"

void scene_init(scene &scn)
{
    create_shader(scn.sh, "../code/shaders/vertex.vs", "../code/shaders/fragment.vs");
    static float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    scn.vb.vertices = &vertices[0];
    scn.vb.size = sizeof(vertices);
    generate_dynamic_vertex_buffer(scn.vb);
    set_vertex_attributef(scn.vb, 0, 3, 3 * sizeof(float), (void *)0);

    scn.projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    set_uniform_mat4(scn.sh, "projection", scn.projection);

    glm::vec3 vertxPos1(0.5f, 0.5f, 0.0f);
    glm::vec3 vertxPos2(0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos3(-0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos4(-0.5f, 0.5f, 0.0f);

    set_uniform_vec3(scn.sh, "c_positions[0]", vertxPos1);
    set_uniform_vec3(scn.sh, "c_positions[1]", vertxPos2);
    set_uniform_vec3(scn.sh, "c_positions[2]", vertxPos3);
    set_uniform_vec3(scn.sh, "c_positions[3]", vertxPos4);
}
