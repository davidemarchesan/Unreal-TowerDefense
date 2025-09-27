#pragma once

#include "CoreMinimal.h"
#include "RunPhase.generated.h"

UENUM(BlueprintType)
enum class ERunPhase : uint8
{
	Setup UMETA(DisplayName = "Setup"),
	Defense UMETA(DisplayName = "Defense"),
};
