#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <string>

class PR_Window
{
public:
	PR_Window(const std::string &name);
	~PR_Window();

	virtual void Update() = 0;

protected:
	virtual bool Begin();
	void End();

	bool _show;
	std::string _name;

};