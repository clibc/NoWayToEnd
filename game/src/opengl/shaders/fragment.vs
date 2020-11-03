#version 330 core
out vec4 color;

in vec2 textureCoord;

uniform sampler2D myTexture;

void main(void)
{
    color = texture(myTexture, textureCoord);
}