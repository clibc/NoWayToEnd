#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 atextureCoord;

out vec2 textureCoord;

uniform mat4 mvp;
uniform mat4 model;

void main(void)
{
    gl_Position = mvp * model * vec4(position, 1.0);
    textureCoord = atextureCoord;
}