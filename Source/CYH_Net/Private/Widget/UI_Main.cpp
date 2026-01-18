// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_Main.h"
#include "State/NetGameState.h"
#include "State/NetPlayerState.h"
#include "Widget/UI_DataLine.h"

void UUI_Main::NativeConstruct()
{
	Super::NativeConstruct();

	if (UWorld* world = GetWorld())
	{
		NetGameState = Cast<ANetGameState>(world->GetGameState());
		if (NetGameState.IsValid())
		{
			NetGameState->OnTimerChanged.AddDynamic(this, &UUI_Main::UpdateTime);

			UpdateTime(NetGameState->GetRemainingTime());
		}
	}

	if (APlayerController* pc = GetOwningPlayer())
	{
		NetPlayerState = pc->GetPlayerState<ANetPlayerState>();
		if (NetPlayerState.IsValid())
		{
			NetPlayerState->OnNameChanged.AddDynamic(this, &UUI_Main::UpdateName);
			NetPlayerState->OnCountChanged.AddDynamic(this, &UUI_Main::UpdatePickupCount);

			UpdateName(NetPlayerState->GetMyName());
			UpdatePickupCount(NetPlayerState->GetPickupCount());
		}
	}
}

void UUI_Main::NativeDestruct()
{
	Super::NativeDestruct();

	if (NetGameState.IsValid())
	{
		NetGameState->OnTimerChanged.RemoveDynamic(this, &UUI_Main::UpdateTime);
	}

	if (NetPlayerState.IsValid())
	{
		NetPlayerState->OnNameChanged.RemoveDynamic(this, &UUI_Main::UpdateName);
		NetPlayerState->OnCountChanged.RemoveDynamic(this, &UUI_Main::UpdatePickupCount);
	}
}

void UUI_Main::UpdateName(const FString& InName)
{
	Name->SetLabel(FText::FromString(InName));
}

void UUI_Main::UpdatePickupCount(int32 InCount)
{
	PickupCount->SetIntValue(InCount);
}

void UUI_Main::UpdateTime(int32 InTime)
{
	Timer->SetIntValue(InTime);
}


