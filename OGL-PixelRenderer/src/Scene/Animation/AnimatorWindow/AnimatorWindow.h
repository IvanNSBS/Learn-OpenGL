#pragma once

#include "AnimTimeline.h"

#include "../../../ImGuiWindows/PR_Window.h"

class AnimatorWindow : public PR_Window
{
public:
	AnimatorWindow();
	~AnimatorWindow();

private:
	AnimTimeline* _timeLine;
};

