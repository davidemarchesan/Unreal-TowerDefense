// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefense.h"
#include "Modules/ModuleManager.h"
#include "UI/GameStyle.h"

class FTowerDefenseModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		FGameStyle::Initialize();
	}

	virtual void ShutdownModule() override
	{
		FGameStyle::Shutdown();
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FTowerDefenseModule, TowerDefense, "TowerDefense" );
