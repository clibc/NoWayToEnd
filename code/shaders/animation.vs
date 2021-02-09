#version 460 core
layout(location = 0) in vec3 position;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform vec3 c_positions[4];
uniform vec2 t_positions[4];

void main()
{
    if (position == c_positions[0])
    {
        TexCoord = t_positions[0];
    }
    else if (position == c_positions[1])
    {
        TexCoord = t_positions[1];
    }
    else if (position == c_positions[2])
    {
        TexCoord = t_positions[2];
    }
    else if (position == c_positions[3])
    {
        TexCoord = t_positions[3];
    }

    gl_Position = projection * model * vec4(position, 1.0);
}