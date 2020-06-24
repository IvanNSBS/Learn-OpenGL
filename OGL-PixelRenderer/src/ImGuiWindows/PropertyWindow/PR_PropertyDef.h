#pragma once

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

class PR_PropertyDef
{
public:
	PR_PropertyDef() {}
	virtual void BeginProperty() = 0;
};

