#include "Joint.h"

Joint::Joint(const int& _id, const std::string& _nm, const glm::mat4 _localTransf):id(_id), name(_nm), localBindTransform(_localTransf) { }
