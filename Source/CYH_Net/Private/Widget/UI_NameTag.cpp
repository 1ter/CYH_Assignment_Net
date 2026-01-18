// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_NameTag.h"
#include "Components/TextBlock.h"
#include "State/NetPlayerState.h"

void UUI_NameTag::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* pawn = GetOwningPlayerPawn())
	{
		NetPlayerState = pawn->GetPlayerState<ANetPlayerState>();
		if (NetPlayerState.IsValid())
		{
			NetPlayerState->OnNameChanged.AddDynamic(this, &UUI_NameTag::UpdateName);

			UpdateName(NetPlayerState->GetMyName());
		}
	}
}

void UUI_NameTag::NativeDestruct()
{
	Super::NativeDestruct();

	if (NetPlayerState.IsValid())
	{
		NetPlayerState->OnNameChanged.RemoveDynamic(this, &UUI_NameTag::UpdateName);
	}
}

void UUI_NameTag::UpdateName(const FString& InName)
{
	if (Name)
	{
		Name->SetText(FText::FromString(InName));
	}
}

