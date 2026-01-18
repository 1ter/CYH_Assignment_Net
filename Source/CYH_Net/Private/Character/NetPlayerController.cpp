// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NetPlayerController.h"
#include "Widget/MainHUD.h"
#include "Widget/UI_PickupCount.h"
#include "Widget/UI_Timer.h"
#include "State/NetPlayerState.h"
#include "State/NetGameState.h"

void ANetPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		MainHUD = Cast<AMainHUD>(GetHUD());

	}
}

void ANetPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UE_LOG(LogTemp, Warning, TEXT("[PC] OnRep_PlayerState -> %s"),
		*GetNameSafe(GetPlayerState<APlayerState>()));


	if (IsLocalController())
	{
		BindPlayerState();
	}
}

void ANetPlayerController::BindPlayerState()
{
	if (!MainHUD.IsValid())
	{
		MainHUD = Cast<AMainHUD>(GetHUD());
	}

	if (MainHUD.IsValid())
	{
		if (ANetPlayerState* playerState = GetPlayerState<ANetPlayerState>())
		{
			if (UUI_PickupCount* pickupCount = MainHUD->GetPickupCountWidget())
			{
				pickupCount->BindPlayerState(playerState);
			}
		}
	}
}
