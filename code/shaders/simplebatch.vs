#version 460 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tPos;
layout(location = 2) in float colIndex;

uniform mat4 model;
uniform mat4 projection;

out vec2 textCord;
out float colorIndex;

void main(){
		textCord = tPos;
		colorIndex = colIndex;
		gl_Position = projection * model * vec4(pos, 1.0);
}