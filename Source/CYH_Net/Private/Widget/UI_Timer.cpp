// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_Timer.h"
#include "State/NetGameState.h"
#include "Components/TextBlock.h"

void UUI_Timer::NativeConstruct()
{
	Super::NativeConstruct();

	if (UWorld* world = GetWorld())
	{
		NetGameState = Cast<ANetGameState>(world->GetGameState());
		if (NetGameState.IsValid())
		{
			NetGameState->OnTimerChanged.AddDynamic(this, &UUI_Timer::UpdateTime);

			UpdateTime(NetGameState->GetRemainingTime());
		}
	}
}

void UUI_Timer::NativeDestruct()
{
	Super::NativeDestruct();

	if (NetGameState.IsValid())
	{
		NetGameState->OnTimerChanged.RemoveDynamic(this, &UUI_Timer::UpdateTime);
	}
}

void UUI_Timer::UpdateTime(int32 InTime)
{
	if (Timer)
	{
		Timer->SetText(FText::AsNumber(InTime));
	}
}