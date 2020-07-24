#pragma once

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

class Joint {

public:
	Joint(const int& id, const std::string& name, const glm::mat4 localTransf);
	~Joint();

	const int Id() const;
	std::vector<Joint*> childs;
	std::string name;
	int id;

	const glm::mat4* AnimatedBindTransform();
	const glm::mat4* InverseBindTransform();
	const glm::mat4* LocalBindTransform();

protected:
	glm::mat4 CalcInverseBindTransform();

private:

	glm::mat4 animatedTransform; // in model space 
	glm::mat4 localBindTransform; // transform in relation to parent
	glm::mat4 inverseBindTransform;
};