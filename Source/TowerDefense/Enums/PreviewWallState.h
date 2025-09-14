#pragma once

#include "CoreMinimal.h"
#include "PreviewWallState.generated.h"

UENUM(BlueprintType)
enum class EPreviewWallState : uint8
{
    None UMETA(DisplayName = "None"),                   // 0
    Valid UMETA(DisplayName = "Valid"),                 // 1
    Invalid UMETA(DisplayName = "Invalid")              // 2
};
