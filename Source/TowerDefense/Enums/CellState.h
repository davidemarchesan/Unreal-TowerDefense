#pragma once

#include "CoreMinimal.h"
#include "CellState.generated.h"

UENUM(BlueprintType)
enum class ECellState : uint8
{
    Empty UMETA(DisplayName = "Empty"),                 // 0
    Wall UMETA(DisplayName = "Wall"),                   // 1
    DefaultWall UMETA(DisplayName = "Default Wall")     // 2
};