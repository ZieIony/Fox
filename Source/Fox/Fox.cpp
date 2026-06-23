// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fox.h"
#include "Modules/ModuleManager.h"
#include "FoxGameplayTagManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FFoxGameModule, Fox, "Fox" );

void FFoxGameModule::StartupModule() {
	FFoxGameplayTagManager::Init();
}