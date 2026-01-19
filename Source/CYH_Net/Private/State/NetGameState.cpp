// Fill out your copyright notice in the Description page of Project Settings.


#include "State/NetGameState.h"
#include "Net/UnrealNetwork.h"
#include "Widget/MainHUD.h"

void ANetGameState::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		MainHUD = playerController->GetHUD<AMainHUD>();
	}
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANetGameState, RemainingTime);
	DOREPLIFETIME(ANetGameState, bGameEnded);
	DOREPLIFETIME(ANetGameState, WinnerName);
}

void ANetGameState::OnRep_RemainingTime()
{
	if (MainHUD.IsValid())
	{
		MainHUD->UpdateTime(RemainingTime);
	}
}

void ANetGameState::OnRep_GameEnded()
{
	if (MainHUD.IsValid())
	{
		MainHUD->ShowResult(bGameEnded);
	}
}

void ANetGameState::OnRep_WinnerName()
{
	if (MainHUD.IsValid())
	{
		MainHUD->UpdateWinnerName(WinnerName);
	}
}
