// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStyle.h"

#include "Engine/Font.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FGameStyle::StyleInstance = nullptr;

struct FStyleFontData
{
	FString Name;
	FString Source;
};

struct FStyleIconData
{
	FName Name;
	FString Source;
	FVector2D Size;
};

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

	// Colors
	const FColor ColorGunmetal = FColor::FromHex("333745");
	const FColor ColorCerise = FColor::FromHex("E63462");
	const FColor ColorBittersweet = FColor::FromHex("FE5F55");
	const FColor ColorTeaGreen = FColor::FromHex("C7EFCF");
	const FColor ColorBeige = FColor::FromHex("EEF5DB");

	const FColor ColorYellow = FColor::FromHex("F4E409");

	StyleInstance->Set("TowerDefense.Color.Gunmetal", FLinearColor(ColorGunmetal));
	StyleInstance->Set("TowerDefense.Color.Cerise", FLinearColor(ColorCerise));
	StyleInstance->Set("TowerDefense.Color.Bittersweet", FLinearColor(ColorBittersweet));
	StyleInstance->Set("TowerDefense.Color.TeaGreen", FLinearColor(ColorTeaGreen));
	StyleInstance->Set("TowerDefense.Color.Beige", FLinearColor(ColorBeige));

	StyleInstance->Set("TowerDefense.Color.Yellow", FLinearColor(ColorYellow));

	// Fonts
	InitializeFonts();

	// Icons
	InitializeIcons();

	// Buttons
	InitializeButtons();
	const FButtonStyle ButtonStyle = FButtonStyle()
	                                 .SetNormalPadding(FMargin(40))
	                                 .SetPressedPadding(FMargin(8))
	                                 .SetNormal(FSlateColorBrush(FLinearColor(FColor::FromHex("F4E409"))))
	                                 .SetNormalForeground(FLinearColor(0.05f, 0.05f, 0.08f))
	                                 .SetHovered(FSlateColorBrush(ColorBittersweet))
	                                 .SetPressed(FSlateColorBrush(ColorBittersweet));

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

void FGameStyle::InitializeFonts()
{
	const TArray<FStyleFontData> StyleFonts = {
		FStyleFontData(
			"TowerDefense.Font.Regular",
			"/Game/UI/Fonts/Quicksand/Quicksand-Regular_Font.Quicksand-Regular_Font"
		),
		FStyleFontData(
			"TowerDefense.Font.Medium",
			"/Game/UI/Fonts/Quicksand/Quicksand-Medium_Font.Quicksand-Medium_Font"
		),
		FStyleFontData(
			"TowerDefense.Font.SemiBold",
			"/Game/UI/Fonts/Quicksand/Quicksand-SemiBold_Font.Quicksand-SemiBold_Font"
		),
		FStyleFontData(
			"TowerDefense.Font.Bold",
			"/Game/UI/Fonts/Quicksand/Quicksand-Bold_Font.Quicksand-Bold_Font"
		),
	};

	const TMap<FString, float> FontSizes = {
		{"xs", 14.f},
		{"sm", 16.f},
		{"md", 22.f},
		{"lg", 26.f},
		{"xl", 32.f},
		{"xxl", 40.f},
	};

	for (const FStyleFontData& StyleFont : StyleFonts)
	{
		for (const TPair<FString, float>& FontSize : FontSizes)
		{
			FString StyleFontName = StyleFont.Name + "." + FontSize.Key;
			// Example: TowerDefense.Font.Regular.sm | TowerDefense.Font.Regular.md

			StyleInstance->Set(*StyleFontName, FSlateFontInfo(
				                   LoadObject<UFont>(
					                   nullptr, *StyleFont.Source),
				                   FontSize.Value
			                   )
			);
		}
	}
}

void FGameStyle::InitializeIcons()
{
	const TArray<FStyleIconData> StyleIcons = {
		FStyleIconData(
			"TowerDefense.Icons.Heart",
			"/Game/UI/Icons/FontAwesome/heart-solid-full.heart-solid-full",
			FVector2D(64.0f, 56.0f)
		),
		FStyleIconData(
			"TowerDefense.Icons.Coins",
			"/Game/UI/Icons/FontAwesome/coins-solid-full.coins-solid-full",
			FVector2D(64.0f, 64.0f)
		),
		FStyleIconData(
			"TowerDefense.Icons.Skull",
			"/Game/UI/Icons/FontAwesome/skull-solid-full.skull-solid-full",
			FVector2D(64.0f, 64.0f)
		),
		FStyleIconData(
			"TowerDefense.Icons.Star",
			"/Game/UI/Icons/FontAwesome/star-solid-full.star-solid-full",
			FVector2D(64.0f, 61.0f)
		),
		FStyleIconData(
			"TowerDefense.Icons.Meteor",
			"/Game/UI/Icons/FontAwesome/meteor-solid-full.meteor-solid-full",
			FVector2D(64.0f, 64.0f)
		),
	};

	for (const FStyleIconData& StyleIcon : StyleIcons)
	{
		StyleInstance->Set(StyleIcon.Name,
		                   new FSlateImageBrush(LoadObject<UTexture2D>(
			                                        nullptr,
			                                        *StyleIcon.Source),
		                                        FVector2D(64.0f, 56.0f)));
	}
}

void FGameStyle::InitializeButtons()
{
	const FButtonStyle ButtonStyle = FButtonStyle()
	                                 .SetNormalPadding(FMargin(14, 7))
	                                 .SetPressedPadding(FMargin(14, 7))
	                                 .SetNormal(FSlateRoundedBoxBrush(
		                                 StyleInstance->GetColor("TowerDefense.Color.Yellow"), 12))
	                                 .SetHovered(
		                                 FSlateRoundedBoxBrush(StyleInstance->GetColor("TowerDefense.Color.Yellow"),
		                                                       12))
	                                 .SetPressed(
		                                 FSlateRoundedBoxBrush(StyleInstance->GetColor("TowerDefense.Color.Yellow"),
		                                                       12))
	                                 .SetNormalForeground(FLinearColor::Black)
	                                 .SetHoveredForeground(FLinearColor::Black)
	                                 .SetPressedForeground(FLinearColor::Black);

	StyleInstance->Set("TowerDefense.Button.Yellow", ButtonStyle);
}
