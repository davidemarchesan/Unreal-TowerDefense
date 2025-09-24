#pragma once

#include "CoreMinimal.h"
#include "RunPhase.generated.h"

UENUM(BlueprintType)
enum class ERunPhase : uint8
{
	Build UMETA(DisplayName = "Build"),
	Wave UMETA(DisplayName = "Wave"),
};
