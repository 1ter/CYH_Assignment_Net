// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_Timer.h"
#include "State/NetGameState.h"
#include "Components/TextBlock.h"

void UUI_Timer::NativeConstruct()
{
	Super::NativeConstruct();

	if (UWorld* world = GetWorld())
	{
		if (ANetGameState* gameState = Cast<ANetGameState>(world->GetGameState()))
		{
			UpdateTime(gameState->GetRemainingTime());
		}
	}
}

void UUI_Timer::UpdateTime(int32 InTime)
{
	if (Timer)
	{
		Timer->SetText(FText::AsNumber(InTime));
	}
}