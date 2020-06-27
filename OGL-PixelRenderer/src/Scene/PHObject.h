#pragma once

#include "../OpenGL/Shaders/ShaderProgram.h"
#include "./Cameras/Camera.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"


struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 loc, glm::vec3 rot, glm::vec3 sc) {
		location = loc;
		rotation = rot;
		scale = sc;
	}

	Transform(){}
};

/// <summary>
/// Placeholder class to test viewport stuff while actual model class
/// is not finished
/// </summary>
class PHObject {
private:

	GLuint objVAO;
	GLuint objVBO[3]; //0 = vertices, 1 = normals, 2 = uvs;
	GLuint texture;
	float celThreshold = 0.425f;
	float attenuation = 0.750f;

	std::string name = "Obj";



	bool load_from_file(const char* filePath) {
		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		std::ifstream f(filePath);
		if (!f.is_open())
		{
			std::cout << "File cannot be oppened or does not exist\n";
			return false;
		}

		std::cout << "file was oppened!\n";


		while (!f.eof())
		{
			char line[512];
			f.getline(line, 512);

			std::stringstream s;
			s << line;

			char junk;

			if (line[0] == 'v')
			{
				if (line[1] == 't')
				{
					float uvs, uvt;
					s >> junk >> junk >> uvs >> uvt;
					glm::vec2 uv(uvs, uvt);
					temp_uvs.push_back(uv);
				}
				if (line[1] == 'n')
				{
					float nx, ny, nz;
					s >> junk >> junk >> nx >> ny >> nz;
					glm::vec3 normal(nx, ny, nz);
					temp_normals.push_back(normal);
				}
				else {
					float vx, vy, vz;
					s >> junk >> vx >> vy >> vz;
					glm::vec3 vertex(vx, vy, vz);
					temp_vertices.push_back(vertex);
				}
			}

			else if (line[0] == 'f')
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				s >> junk >> vertex1 >> vertex2 >> vertex3;
				int fstslash = vertex1.find("/");
				int sndslash = vertex1.find("/", fstslash + 1);
				int trdslash = vertex1.find("/", sndslash + 1);
				std::string fst = vertex1.substr(0, fstslash);
				std::string snd = vertex1.substr(fstslash + 1, sndslash - fstslash - 1);
				std::string trd = vertex1.substr(sndslash + 1);
				vertexIndex[0] = atoi(fst.c_str());
				uvIndex[0] = atoi(snd.c_str());
				normalIndex[0] = atoi(trd.c_str());

				fstslash = vertex2.find("/");
				sndslash = vertex2.find("/", fstslash + 1);
				trdslash = vertex2.find("/", sndslash + 1);
				fst = vertex2.substr(0, fstslash);
				snd = vertex2.substr(fstslash + 1, sndslash - fstslash - 1);
				trd = vertex2.substr(sndslash + 1);
				vertexIndex[1] = atoi(fst.c_str());
				uvIndex[1] = atoi(snd.c_str());
				normalIndex[1] = atoi(trd.c_str());

				fstslash = vertex3.find("/");
				sndslash = vertex3.find("/", fstslash + 1);
				trdslash = vertex3.find("/", sndslash + 1);
				fst = vertex3.substr(0, fstslash);
				snd = vertex3.substr(fstslash + 1, sndslash - fstslash - 1);
				trd = vertex3.substr(sndslash + 1);
				vertexIndex[2] = atoi(fst.c_str());
				uvIndex[2] = atoi(snd.c_str());
				normalIndex[2] = atoi(trd.c_str());

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int v1 = vertexIndices[i];
			unsigned int n1 = normalIndices[i];
			unsigned int uv1 = uvIndices[i];

			vertices.push_back(temp_vertices[v1 - 1].x);
			vertices.push_back(temp_vertices[v1 - 1].y);
			vertices.push_back(temp_vertices[v1 - 1].z);

			normals.push_back(temp_normals[n1 - 1].x);
			normals.push_back(temp_normals[n1 - 1].y);
			normals.push_back(temp_normals[n1 - 1].z);

			uvs.push_back(temp_uvs[uv1 - 1].s);
			uvs.push_back(temp_uvs[uv1 - 1].t);

			//printf("vert = (%f, %f, %f)\n", temp_vertices[v1 - 1].x, temp_vertices[v1 - 1].y, temp_vertices[v1 - 1].z);
			//printf("normal = (%f, %f, %f)\n", temp_normals[n1 - 1].x, temp_normals[n1 - 1].y, temp_normals[n1 - 1].z);
			//printf("uv = (%f, %f)\n", temp_uvs[uv1 - 1].s, temp_uvs[uv1 - 1].t);
		}

		std::cout << "vertSize = " << vertexIndices.size() << "\n";
		std::cout << "normalSize = " << normalIndices.size() << "\n";
		std::cout << "uvSize = " << uvIndices.size() << "\n";

		return true;
	}

public:
	Transform transform;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> uvs;
	glm::mat4 model;
	ShaderProgram* shader;
	glm::vec3 color = glm::vec3(0.35, 0.175, 0.155);
	float shininess = 3.6;
	float specStr = 1.f;

	PHObject(const char* filePath, const char* vertexPath, const char* fragPath) {
		if (!load_from_file(filePath))
			return;

		shader = new ShaderProgram(vertexPath, fragPath);
	}

	PHObject(const char* filePath, Transform t, const char* vertexPath, const char* fragPath) :transform(t) {
		if (!load_from_file(filePath))
			return;
		shader = new ShaderProgram(vertexPath, fragPath);
	}

	void set_name(std::string newName) {
		name = newName;
	}

	glm::mat4* get_obj_model_matrix() {
		model = glm::mat4(1.f);
		glm::vec3 nScale = glm::vec3(transform.scale.x, -transform.scale.y, transform.scale.z);
		model = glm::scale(model, nScale);
		model = glm::translate(model, transform.location);
		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, -1));
		return &model;
	}


	void start_imgui() {
		if (ImGui::Begin("PH Object")) {
			ImGui::DragFloat3((name + " Position").c_str(), glm::value_ptr(transform.location), 0.1f);
			ImGui::DragFloat3((name + " Rotation").c_str(), glm::value_ptr(transform.rotation), 1.f);
			ImGui::DragFloat3((name + " Scale").c_str(), glm::value_ptr(transform.scale), 0.05f);
			ImGui::ColorEdit3((name + " Color").c_str(), glm::value_ptr(color));
			ImGui::DragFloat((name + " Shininess").c_str(), &shininess, 0.1, 0, 64);
			ImGui::DragFloat((name + " Spec Strength").c_str(), &specStr, 0.01, 0, 1);
			ImGui::DragFloat((name + " Cel Threshold").c_str(), &celThreshold, 0.01, 0, 1);
			ImGui::DragFloat((name + " Cel Attenuation").c_str(), &attenuation, 0.01, 0, 1);
		}
	}

	void Start() {
		glGenVertexArrays(1, &objVAO);
		glGenBuffers(3, objVBO);

		glBindVertexArray(objVAO);


		glBindBuffer(GL_ARRAY_BUFFER, objVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, objVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, objVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		printf("Started Object!\n");
	}

	void Draw(Camera& cam) {
		shader->Bind();

		shader->SetMat4("model", GL_FALSE, glm::value_ptr(*get_obj_model_matrix()));
		shader->SetMat4("view", GL_FALSE, glm::value_ptr(*cam.get_view_matrix()));
		shader->SetMat4("projection", GL_FALSE, glm::value_ptr(*cam.get_projection_matrix()));
		shader->SetFloat3("viewPos", cam.GetPos());

		shader->SetFloat3("material.diffuseColor", color);
		shader->SetFloat("material.celThreshold", celThreshold);
		shader->SetFloat("material.celAttenuation", attenuation);
		shader->SetFloat("material.shininess", shininess);

		glBindVertexArray(objVAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	}
};