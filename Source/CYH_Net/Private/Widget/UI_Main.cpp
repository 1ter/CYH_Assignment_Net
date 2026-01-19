// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_Main.h"
#include "Widget/UI_Timer.h"
#include "Widget/UI_PickupCount.h"
#include "Widget/UI_Result.h"
#include "Components/VerticalBox.h"

void UUI_Main::UpdateMyInfo(const FString& InName, int32 InCount)
{
	if (MyCountWidget)
	{
		MyCountWidget->UpdateInfo(InName, InCount);
	}
}

void UUI_Main::UpdateOtherInfo(ANetPlayerState* InPlayerState, const FString& InName, int32 InCount)
{
	if (InPlayerState && PlayerList && PickupCountWidgetClass)
	{
		if (PlayerWidgetMap.Contains(InPlayerState))
		{
			PlayerWidgetMap[InPlayerState]->UpdateInfo(InName, InCount);
		}
		else
		{
			if (UUI_PickupCount* addWidget = CreateWidget<UUI_PickupCount>(this, PickupCountWidgetClass))
			{
				PlayerList->AddChildToVerticalBox(addWidget);
				PlayerWidgetMap.Add(InPlayerState, addWidget);

				addWidget->UpdateInfo(InName, InCount);
			}
		}
	}
}

void UUI_Main::UpdateTime(int32 InTime)
{
	if (TimeWidget)
	{
		TimeWidget->UpdateTime(InTime);
	}
}

void UUI_Main::UpdateWinnerName(const FString& InName)
{
	if (ResultWidget)
	{
		ResultWidget->UpdateWinnerName(InName);
	}
}

void UUI_Main::ShowResult(bool bShow)
{
	if (ResultWidget)
	{
		ResultWidget->ShowResult(bShow);
	}
}