// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStyle.h"

#include "Engine/Font.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FGameStyle::StyleInstance = nullptr;

/*
 * Palette: https://coolors.co/333745-e63462-fe5f55-c7efcf-eef5db
 * https://coolors.co/visualizer/333745-e63462-fe5f55-c7efcf-eef5db
 * Gunmetal:	333745
 * Cerise:		E63462
 * Bittersweet: FE5F55
 * TeaGreen:	C7EFCF
 * Beige:		EEF5DB
 *
*/

void FGameStyle::Initialize()
{
	if (StyleInstance.IsValid())
	{
		return;
	}

	StyleInstance = MakeShareable(new FSlateStyleSet("GameStyle"));

	// Fonts
	StyleInstance->Set("TowerDefense.Font.Regular", FSlateFontInfo(
		                   LoadObject<UFont>(nullptr, TEXT("/Game/UI/Fonts/Quicksand/Quicksand-Regular_Font.Quicksand-Regular_Font")), 20
	                   )
	);

	StyleInstance->Set("TowerDefense.Font.SemiBold", FSlateFontInfo(
						   LoadObject<UFont>(nullptr, TEXT("/Game/UI/Fonts/Quicksand/Quicksand-Medium_Font.Quicksand-Medium_Font")), 20
					   )
	);

	StyleInstance->Set("TowerDefense.Font.SemiBold", FSlateFontInfo(
		                   LoadObject<UFont>(nullptr, TEXT("/Game/UI/Fonts/Quicksand/Quicksand-SemiBold_Font.Quicksand-SemiBold_Font")), 20
	                   )
	);

	StyleInstance->Set("TowerDefense.Font.Bold", FSlateFontInfo(
						   LoadObject<UFont>(nullptr, TEXT("/Game/UI/Fonts/Quicksand/Quicksand-Bold_Font.Quicksand-Bold_Font")), 20
					   )
	);

	// Colors
	const FColor ColorGunmetal = FColor::FromHex("333745");
	const FColor ColorCerise = FColor::FromHex("E63462");
	const FColor ColorBittersweet = FColor::FromHex("FE5F55");
	const FColor ColorTeaGreen = FColor::FromHex("C7EFCF");
	const FColor ColorBeige = FColor::FromHex("EEF5DB");

	StyleInstance->Set("TowerDefense.Color.Primary", FLinearColor::White);
	StyleInstance->Set("TowerDefense.Color.Accent", FLinearColor(1.0f, 0.8f, 0.2f));
	StyleInstance->Set("TowerDefense.Color.Background", FLinearColor(0.05f, 0.05f, 0.08f));

	StyleInstance->Set("TowerDefense.Color.Gunmetal", FLinearColor(ColorGunmetal));
	StyleInstance->Set("TowerDefense.Color.Cerise", FLinearColor(ColorCerise));
	StyleInstance->Set("TowerDefense.Color.Bittersweet", FLinearColor(ColorBittersweet));
	StyleInstance->Set("TowerDefense.Color.TeaGreen", FLinearColor(ColorTeaGreen));
	StyleInstance->Set("TowerDefense.Color.Beige", FLinearColor(ColorBeige));

	const FButtonStyle ButtonStyle = FButtonStyle()
	                           .SetNormalPadding(FMargin(10))
	                           .SetPressedPadding(FMargin(8))
	                           .SetNormal(FSlateColorBrush(ColorBeige))
	                           .SetHovered(FSlateColorBrush(FLinearColor(0.3f, 0.7f, 1.0f)))
	                           .SetPressed(FSlateColorBrush(FLinearColor(0.1f, 0.4f, 0.8f)));

	StyleInstance->Set("TowerDefense.Button", ButtonStyle);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FGameStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}
}

const ISlateStyle& FGameStyle::Get()
{
	return *StyleInstance;
}

FName FGameStyle::GetStyleSetName()
{
	return "TowerDefense.Style";
}
