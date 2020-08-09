#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

//#include "../Animation/Joint.h"

#include "Material.h"
#include "../../Data Types/Transform.h"
#include "../../Data Types/Vertex.h"
#include "../../Data Types/Texture.h"
#include "../../Data Types/VertexBone.h"

class MeshData
{
private:
	GLuint _vertexArray, _vertexBuffer, _indexBuffer, _boneBuffer;
	//Joint _rootJoint;
	//unsigned int _jointCount;
public:
	std::vector<Vertex> vertices;
	std::vector<VertexBone> bones;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::string name;

	//Transform transform;
	glm::mat4 transform;

	Material* material = nullptr;
	void Draw();
	void SetMaterial(Material* mat);

	MeshData(std::string name, glm::mat4 transform, const std::vector<Vertex>& verts, const std::vector<GLuint>& idxs, Material* mat);
	MeshData(std::string name, glm::mat4 transform, const std::vector<Vertex>& verts, const std::vector<VertexBone>& bone, const std::vector<GLuint>& idxs, Material* mat);
	~MeshData();
};

