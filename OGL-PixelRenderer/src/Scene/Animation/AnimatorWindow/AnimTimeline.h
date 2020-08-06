#pragma once

#include "../../../ImGuiWindows/PR_Window.h"

class AnimTimeline : public PR_Window
{
public:
	void Update() override;
	AnimTimeline(const int& maxFrames, const std::string& name) : _maxFrames(maxFrames), PR_Window(name) { _finalFrame = maxFrames; }

	// Remember: Examples i'll need to create this GUI
	// Custom Rendering Example from Dear ImGui demo
	// Layouts example from Dear ImGui Demo
	//		Layouts will be used to organize Timeline Header and Timeline
	/*
		## Timeline Header
		- FPS sampling
		- Starting Frame
		- Last Frame
		- Current Frame
		- Current Time(in seconds)

		## Timeline
		- Lista com quantidade total de frames
		- Sinalizador de qual frame é um keyframe
		- Linha vertical que mostra onde o tempo atual está na timeline
	*/

	// TODO:
	// Use ImGui custom renderer to draw the timeline vertical progress line

private:

	int _maxFrames = 30;

	int _initialFrame = 0, _finalFrame = 0;
	int _currentFrame = 0;
	int _frameSampling = 30; // number of frames per second

	float _animationDuration = 7.5f;
	float _currentTime = 0.f;
	int loopCount = 0;
};

