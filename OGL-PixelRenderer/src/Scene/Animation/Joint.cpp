#include "Joint.h"

Joint::Joint(
	const int& _id, 
	const std::string& _nm, 
	const glm::mat4 _localTransf):id(_id), name(_nm), localBindTransform(_localTransf) 
{
}

const glm::mat4* Joint::AnimatedBindTransform()
{
	return &animatedTransform;
}

const glm::mat4* Joint::InverseBindTransform()
{
	return &inverseBindTransform;
}

const glm::mat4* Joint::LocalBindTransform()
{
	return &localBindTransform;
}

glm::mat4 Joint::CalcInverseBindTransform(glm::mat4 parentBindTransform)
{
	glm::mat4 bindTransf = parentBindTransform * localBindTransform;
	inverseBindTransform = glm::inverse(localBindTransform);
	for (auto joint : childs) {
		joint->CalcInverseBindTransform(bindTransf);
	}
	return glm::mat4();
}
