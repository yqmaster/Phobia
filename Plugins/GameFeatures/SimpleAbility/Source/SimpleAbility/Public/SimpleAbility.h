#pragma once

#include "Modules/ModuleManager.h"

class FSimpleAbilityModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
