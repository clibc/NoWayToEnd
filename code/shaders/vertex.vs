#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tPos;
layout(location = 2) in float texID;

out vec2 TexCoord;
out float textureIndex;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoord = tPos;
	textureIndex = texID;
	gl_Position = projection * model * vec4(position, 1.0);
}