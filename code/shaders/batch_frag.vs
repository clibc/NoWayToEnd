#version 330 core

in vec2 TexCoord;
in float textureIndex;

out vec4 color;

uniform sampler2D textures[2];

void main()
{
	//int index = int(textureIndex);
	//color = texture2D(textures[index], TexCoord);
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
 
