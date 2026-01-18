// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_PickupCount.h"
#include "State/NetPlayerState.h"
#include "Components/TextBlock.h"

void UUI_PickupCount::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APawn* pawn = GetOwningPlayerPawn())
	{
		if (ANetPlayerState* playerState = pawn->GetPlayerState<ANetPlayerState>())
		{
			UpdateInfo(playerState->GetMyName(), playerState->GetPickupCount());
		}
	}
}

void UUI_PickupCount::UpdateInfo(const FString& InName, int32 InCount)
{
	if (Name)
	{
		Name->SetText(FText::FromString(InName));
	}

	if (PickupCount)
	{
		PickupCount->SetText(FText::AsNumber(InCount));
	}
}