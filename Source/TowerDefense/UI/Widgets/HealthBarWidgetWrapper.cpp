// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidgetWrapper.h"

#include "TowerDefense/UI/Components/HealthBarWidget.h"

TSharedRef<SWidget> UHealthBarWidgetWrapper::RebuildWidget()
{
	HealthBarWidget = SNew(SHealthBarWidget)
		.HealthPercent(1.f);

	return HealthBarWidget.ToSharedRef();
}

void UHealthBarWidgetWrapper::SetHealthPercent(float InPercent)
{
	if (HealthBarWidget.IsValid())
	{
		HealthBarWidget->SetHealthPercent(InPercent);
	}
}
