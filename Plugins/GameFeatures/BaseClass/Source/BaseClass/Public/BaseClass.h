#pragma once

#include "Modules/ModuleManager.h"

class FBaseClassModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
