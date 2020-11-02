#version 330 core

in vec3 textureCoord;
out vec3 color;

uniform sempler2D myTexture;

void main(void)
{
    FragColor = texture(myTexture, textureCoord);
}