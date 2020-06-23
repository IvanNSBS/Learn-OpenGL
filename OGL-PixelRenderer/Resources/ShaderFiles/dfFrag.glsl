#version 430 core

in vec2 UVs;

out vec4 FragColor;
 
vec3 checker(in float u, in float v)
{
  float checkSize = 32;
  float fmodResult = mod(floor(checkSize * u) + floor(checkSize * v), 2.0);
  float fin = max(sign(fmodResult), 0.86);
  return vec3(fin, fin, fin);
}

void main(){
	vec3 check = checker(UVs.x, UVs.y);
	FragColor = vec4(check, 1.0);
	// FragColor = vec4(1, 0, 0, 1);
}