#pragma once

#include "../PR_Window.h"
#include "PR_PropertyDef.h"

/// Property Window will display properties for 
/// something that defined PR_PropertyWindowDef
class PR_PropertyWindow : public PR_Window
{
public:
	PR_PropertyWindow(const std::string &name, PR_PropertyDef* def);
	void Update() override;
	void SetDefinition(PR_PropertyDef* newDef);

protected:
	PR_PropertyDef* _def; // implementation/definition of Property Window
};

