#version 460 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D texture;

void main()
{
    color = texture2D(texture, TexCoord);
}
