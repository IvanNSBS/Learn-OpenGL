#ifndef IMGUIVIEWPORTH
#define IMGUIVIEWPORTH

#include <string>
#include <glm/vec2.hpp>
#include "PR_Window.h"

#include "../OpenGL/Buffers/FrameBuffer.h"

class PR_Viewport : public PR_Window
{
public:
	PR_Viewport(const std::string& name, FrameBuffer *buffer);
	~PR_Viewport();
	void Update() override;
	glm::vec2 ViewportSize() const;
	float AspectRatio();

protected:
	FrameBuffer* _buffer = nullptr; // pointer to FBO texture;
	glm::vec2 _viewportSize;
};

#endif