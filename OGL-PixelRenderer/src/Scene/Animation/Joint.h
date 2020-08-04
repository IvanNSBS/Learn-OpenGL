#pragma once

#include <vector>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

class Joint {

public:
	Joint(const int& id, const std::string& name, const glm::mat4 localBindTransf);
	~Joint();

	const int Id() const;
	std::vector<Joint*> childs;
	std::string name;
	int id;

	const glm::mat4* AnimatedBindTransform();
	const glm::mat4* InverseBindTransform();
	const glm::mat4* LocalBindTransform();

protected:
	glm::mat4 CalcInverseBindTransform(glm::mat4 parentBindTransform);

private:

	/// <summary>
	/// Bind means original model pose with no animation applied
	/// Local means that the transform is in relation to the parent
	/// </summary>

	glm::mat4 animatedTransform = glm::mat4(1); // Transform to move model position to joint animation position. Is in model space 
	glm::mat4 localBindTransform = glm::mat4(1); // Joint transform in relation to parent joint transform
	glm::mat4 inverseBindTransform = glm::mat4(1); // inverse of localBindTransform
};