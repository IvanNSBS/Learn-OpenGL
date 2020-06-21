#ifndef IMGUIVIEWPORTH
#define IMGUIVIEWPORTH

#include <string>
#include <glm/vec2.hpp>
#include "PRWindow.h"

class PRViewport : PRWindow
{
public:
	PRViewport(const std::string &name);
	~PRViewport();
	void Update() override;
	glm::vec2 ViewportSize() const;

protected:
	glm::vec2 _viewportSize;
	unsigned int* _FBO = nullptr; // pointer to FBO;
};

#endif