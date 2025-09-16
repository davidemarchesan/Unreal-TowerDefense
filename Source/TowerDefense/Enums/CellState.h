#pragma once

#include "CoreMinimal.h"
#include "CellState.generated.h"

UENUM(BlueprintType)
enum class ECellState : uint8
{
    Empty UMETA(DisplayName = "Empty"),                 // 0
    TurretWall UMETA(DisplayName = "Turret Wall"),      // 1
    DefaultWall UMETA(DisplayName = "Default Wall"),    // 2
    Disabled UMETA(DisplayName = "Disabled"),           // 3
};