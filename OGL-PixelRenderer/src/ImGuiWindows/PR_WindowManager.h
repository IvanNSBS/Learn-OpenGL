#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include "PR_Window.h"


class PR_WindowManager
{

public:
	PR_WindowManager(GLFWwindow* window, const char* glslVersion);
	~PR_WindowManager();

	void Update();
	void Render();
	void AddWindow(PR_Window *newWindow);

private:
	void ShowDockSpace(bool* open);
	void SetStyle();
	void UpdateWindows();
	void DeleteWindows(){}

	GLFWwindow* _windowRef;
	std::vector<PR_Window*> _windows;
};

