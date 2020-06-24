#include "PR_Viewport.h"

#ifdef _DEBUG
#include <cstdio>
#endif

PR_Viewport::PR_Viewport(const std::string& name, FrameBuffer* buff) : PR_Window(name), _buffer(buff) {
	// fbo stuff here if necessasry
}

PR_Viewport::~PR_Viewport(){ }

void PR_Viewport::Update() {
	if (!_show)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
	if (!Begin())
		End();
	else {
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (_viewportSize != glm::vec2{ size.x, size.y }) {
			_viewportSize = { size.x, size.y };
			//_buffer->Resize(_viewportSize.x, _viewportSize.y);
			printf("Resizing!\n");
		}
		ImGui::Image((void*)(intptr_t)*_buffer->GetColorAttachment(), {_viewportSize.x, _viewportSize.y});
		End();
	}
	ImGui::PopStyleVar();
}

glm::vec2 PR_Viewport::ViewportSize() const {
	return _viewportSize;
}

float PR_Viewport::AspectRatio() {
	return _viewportSize.x / _viewportSize.y;
}
