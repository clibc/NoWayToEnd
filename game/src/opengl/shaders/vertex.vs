#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 atextureCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out textureCoord;

void main(void)
{
    gl_Position = vec4(position, 1.0);
}