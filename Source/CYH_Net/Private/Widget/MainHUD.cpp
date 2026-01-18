// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainHUD.h"
#include "Widget/UI_Main.h"
#include "Widget/UI_PickupCount.h"
#include "Widget/UI_Timer.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* pc = GetOwningPlayerController())
	{
		if (pc && pc->IsLocalController())
		{
			if (MainHUDclass)
			{
				MainWidget = CreateWidget<UUI_Main>(GetOwningPlayerController(), MainHUDclass);
				if (MainWidget.IsValid())
				{
					MainWidget->AddToViewport();
				}
			}
		}
	}
}

UUI_PickupCount* AMainHUD::GetPickupCountWidget()
{
	if (MainWidget.IsValid())
	{
		return MainWidget->GetPickupCountWidget();
	}

	return nullptr;
}

UUI_Timer* AMainHUD::GetTimerWidget()
{
	if (MainWidget.IsValid())
	{
		return MainWidget->GetTimerWidget();
	}

	return nullptr;
}

