#include "PR_Window.h"

PR_Window::PR_Window(const std::string &name):_name(name), _show(true) { }

PR_Window::~PR_Window() { }

bool PR_Window::Begin() {
	return ImGui::Begin(this->_name.c_str(), &this->_show);
}

std::string PR_Window::Name() const {
	return _name;
}

void PR_Window::End() {
	ImGui::End();
}

bool* PR_Window::Show() {
	return &_show;
}