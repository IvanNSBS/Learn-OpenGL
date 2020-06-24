#pragma once

#include <glad/glad.h>
#include <iostream>

#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"


class FrameBuffer : public PR_PropertyDef
{
public:
	FrameBuffer(const unsigned int &width, const unsigned int &height);
	~FrameBuffer();
	void Bind();
	void Unbind();
	void Resize(unsigned int nwidth, unsigned int nheight);
	GLuint* GetColorAttachment();

	void BeginProperty() override;

private:
	void Initialize();
	unsigned int _width = 0, _height = 0;
	GLuint _ID = 0, _colorAttachment = 0, _depthAttachment = 0;
};

