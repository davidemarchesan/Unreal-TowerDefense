#pragma once

#include "CoreMinimal.h"
#include "CellState.generated.h"

UENUM(BlueprintType)
enum class ECellState : uint8
{
    Empty UMETA(DisplayName = "Empty"),
    Wall UMETA(DisplayName = "Wall"),
    DefaultWall UMETA(DisplayName = "Default Wall")
};