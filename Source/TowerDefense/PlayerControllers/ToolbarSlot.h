#pragma once

#include "CoreMinimal.h"
#include "ToolbarSlot.generated.h"

USTRUCT(BlueprintType)
struct FToolbarSlot
{

	GENERATED_BODY()

	FToolbarSlot(const int32 InButton, const float InPrice, const FText& InName, const FName& InID, TFunction<void()> InAction): Key(InButton), Price(InPrice), Name(InName), ID(InID), Action(MoveTemp(InAction)) {}

	FToolbarSlot(): Key(0), Price(0.f), Name(FText::GetEmpty()), ID(NAME_None) {}

	UPROPERTY()
	int32 Key = 0;

	UPROPERTY()
	float Price = 0;

	UPROPERTY()
	FText Name;

	UPROPERTY()
	FName ID;
	
	TFunction<void()> Action;
	
};
