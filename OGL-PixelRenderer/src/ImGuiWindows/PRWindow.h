#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <string>

class PRWindow
{
public:
	PRWindow(const std::string &name);
	~PRWindow();

	virtual void Update() = 0;

protected:
	virtual bool Begin();
	void End();

	bool _show;
	std::string _name;

};