#ifndef IMGUIVIEWPORTH
#define IMGUIVIEWPORTH

#include <string>
#include <glm/vec2.hpp>
#include "PR_Window.h"

class PR_Viewport : public PR_Window
{
public:
	PR_Viewport(const std::string &name);
	~PR_Viewport();
	void Update() override;
	glm::vec2 ViewportSize() const;

protected:
	glm::vec2 _viewportSize;
	unsigned int* _FBO = nullptr; // pointer to FBO;
};

#endif