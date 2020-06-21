#include "PRViewport.h"

PRViewport::PRViewport(const std::string &name): PRWindow(name){
	// fbo stuff here if necessasry
}

PRViewport::~PRViewport(){ }

void PRViewport::Update() {
	if (!_show)
		return;

	if (!Begin())
		End();
	else {
		ImVec2 size = ImGui::GetWindowSize();
		_viewportSize = { size.x, size.y };
		std::string viewSize = "Viewport Size: (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")";
		ImGui::Text(viewSize.c_str());

		End();
	}
}

glm::vec2 PRViewport::ViewportSize() const {
	return _viewportSize;
}
