#pragma once

#include "Keyframe.h"
#include <vector>

class Animation
{
public:
	std::vector<Keyframe> keyFrames;
	float duration;

	Animation(const float& dur, const std::vector<Keyframe>& frames);
	~Animation();

private:
};

