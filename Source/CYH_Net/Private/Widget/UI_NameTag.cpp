// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_NameTag.h"
#include "Components/TextBlock.h"
#include "State/NetPlayerState.h"

void UUI_NameTag::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* pawn = GetOwningPlayerPawn())
	{
		if (ANetPlayerState* playerState = pawn->GetPlayerState<ANetPlayerState>())
		{
			UpdateName(playerState->GetMyName());
		}
	}
}

void UUI_NameTag::UpdateName(const FString& InName)
{
	if (NameTag)
	{
		NameTag->SetText(FText::FromString(InName));
	}
}

