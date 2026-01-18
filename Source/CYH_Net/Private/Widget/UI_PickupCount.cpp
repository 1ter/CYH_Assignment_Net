// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_PickupCount.h"
#include "State/NetPlayerState.h"
#include "Components/TextBlock.h"

void UUI_PickupCount::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("[UI][Construct] PS=%s"),
		*GetNameSafe(GetOwningPlayer() ? GetOwningPlayer()->PlayerState : nullptr));

}

void UUI_PickupCount::NativeDestruct()
{
	Super::NativeDestruct();

	if (NetPlayerState.IsValid())
	{
		NetPlayerState->OnCountChanged.RemoveDynamic(this, &UUI_PickupCount::UpdatePickupCount);
	}
}

void UUI_PickupCount::BindPlayerState(ANetPlayerState* InPlayerState)
{
	if (InPlayerState)
	{
		NetPlayerState = InPlayerState;
		InPlayerState->OnCountChanged.AddDynamic(this, &UUI_PickupCount::UpdatePickupCount);

		UpdatePickupCount(NetPlayerState->GetPickupCount());
	}
}

void UUI_PickupCount::UpdatePickupCount(int32 InCount)
{
	if (PickupCount)
	{
		PickupCount->SetText(FText::AsNumber(InCount));
	}
}