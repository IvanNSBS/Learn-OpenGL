#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UVs;

void main() {
	
	gl_Position = vec4(aPos, 1);
	UVs = aUV;
}