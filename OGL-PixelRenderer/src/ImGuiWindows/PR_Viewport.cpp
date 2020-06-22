#include "PR_Viewport.h"

#ifdef _DEBUG
#include <cstdio>
#endif

PR_Viewport::PR_Viewport(const std::string &name): PR_Window(name){
	// fbo stuff here if necessasry
}
PR_Viewport::PR_Viewport(const std::string& name, unsigned int *tex) : PR_Window(name), _texture(tex) {
	// fbo stuff here if necessasry
}

PR_Viewport::~PR_Viewport(){ }

void PR_Viewport::Update() {
	if (!_show)
		return;

	if (!Begin())
		End();
	else {
		ImVec2 size = ImGui::GetContentRegionAvail();
		_viewportSize = { size.x, size.y };
		ImGui::Image((void*)(intptr_t)*_texture, {size.x, size.y});
		
		#ifdef _DEBUG
			printf("Viewport size: (%f, %f)\n", size.x, size.y);
		#endif

		End();
	}
}

glm::vec2 PR_Viewport::ViewportSize() const {
	return _viewportSize;
}
