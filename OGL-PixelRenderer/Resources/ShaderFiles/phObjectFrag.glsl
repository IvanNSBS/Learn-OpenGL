#version 430 core

struct ToonMaterial {
	float shininess;
	vec3 diffuseColor;
	float celThreshold;
	float celAttenuation;
};

out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

// specular
uniform vec3 viewPos;
uniform ToonMaterial material;

void main(){
	vec3 lightDir = normalize(vec3(0, 0, 0.5));
	vec3 lightColor = vec3(1,1,1);


	//ambient
	vec3 ambient = 0.1 * lightColor;

	//diffuse
	vec3 norm = normalize(normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseColor = diff * lightColor;

	vec3 result = vec3(1);

	//specular
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow( max( dot(viewDir, reflectDir), 0.0), material.shininess);


	if(material.celAttenuation*diff >= material.celThreshold){
		diff = 1;
	}
	else{
		diff = 0.25f;
	}
	vec3 diffuse = vec3(diff);
	vec3 specular = vec3(0);
	if(dot(normal, lightDir) > 0 && material.celAttenuation*spec > 0.5){
		specular = vec3(1);
	}

	result = material.diffuseColor;

	FragColor = vec4(result, 1);
}