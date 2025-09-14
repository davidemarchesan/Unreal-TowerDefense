#pragma once

#include "CoreMinimal.h"
#include "CellState.generated.h"

UENUM(BlueprintType)
enum class ECellState : uint8
{
    Empty UMETA(DisplayName = "Empty"),                 // 0
    TurretWall UMETA(DisplayName = "TurretWall"),             // 1
    DefaultWall UMETA(DisplayName = "Default Wall")     // 2
};