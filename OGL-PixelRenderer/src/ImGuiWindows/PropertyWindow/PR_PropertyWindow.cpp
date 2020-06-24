#include "PR_PropertyWindow.h"

PR_PropertyWindow::PR_PropertyWindow(
	const std::string& name, 
	PR_PropertyDef* def) : PR_Window(name), _def(def) { }

void PR_PropertyWindow::Update() 
{
	if (!_show)
		return;

	if (!Begin()) {
		End();
		return;
	}

	_def->BeginProperty();
	End();
	
}

void PR_PropertyWindow::SetDefinition(PR_PropertyDef* def) {
	_def = def;
}
