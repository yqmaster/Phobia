#include "BaseClass.h"

#define LOCTEXT_NAMESPACE "FBaseClassModule"

void FBaseClassModule::StartupModule() {}

void FBaseClassModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBaseClassModule, BaseClass)
