// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolbarWidget.h"

#include "ToolbarSlotWidget.h"

void SToolbarWidget::Construct(const FArguments& InArgs)
{
	// Const
	const float SpaceBetweenSlots = 10.f;

	// Input
	Slots = InArgs._Slots;

	// Slate

	TSharedPtr<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);

	for (FToolbarSlot& Slot : Slots)
	{
		HorizontalBox->AddSlot()
		[
			SNew(SToolbarSlotWidget)
			.Name(Slot.Name)
			.Key(FText::AsNumber(Slot.Key))
			.Price(FText::AsNumber(Slot.Price))
		];
	}

	ChildSlot[

		HorizontalBox.ToSharedRef()

		// SNew(SHorizontalBox)
		//
		// + SHorizontalBox::Slot()
		// .Padding(SpaceBetweenSlots, 0)
		// [
		// 	SNew(SToolbarSlotWidget)
		// 	.Name(FText::FromString("Wall"))
		// 	.Key(FText::AsNumber(1))
		// 	.Price(FText::AsNumber(200))
		// ]
		//
		// + SHorizontalBox::Slot()
		// .Padding(SpaceBetweenSlots, 0)
		// [
		// 	SNew(SToolbarSlotWidget)
		// 	.Name(FText::FromString("Cannon"))
		// 	.Key(FText::AsNumber(2))
		// 	.Price(FText::AsNumber(500))
		// ]

	];
}
