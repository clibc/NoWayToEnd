#version 330 core
layout(location = 0) in vec3 position;

uniform vec3 color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 theColor;

void main(void)
{
    //gl_Position = u_ViewProjection *  u_Transform  * vec4(position, 1.0);
    gl_Position = vec4(position, 1.0);
    theColor = color;
}