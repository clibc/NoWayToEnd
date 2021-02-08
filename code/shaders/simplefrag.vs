#version 460 core

out vec4 color;
in float colorIndex;
in vec2 textCord;

uniform sampler2D textures[2];

void main()
{
	int index = int(colorIndex);
    //color = vec4(colorIndex, 0.0, 0.0, 1.0);
	color = texture2D(textures[index], textCord);
}
