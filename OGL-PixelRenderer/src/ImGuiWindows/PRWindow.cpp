#include "PRWindow.h"

PRWindow::PRWindow(const std::string &name):_name(name), _show(true) { }

PRWindow::~PRWindow() { }

bool PRWindow::Begin() {
	return ImGui::Begin(this->_name.c_str(), &this->_show);
}

void PRWindow::End() {
	ImGui::End();
}