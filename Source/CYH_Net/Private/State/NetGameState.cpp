// Fill out your copyright notice in the Description page of Project Settings.


#include "State/NetGameState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANetGameState, RemainingTime);
	DOREPLIFETIME(ANetGameState, bGameEnded);
}

void ANetGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
	}
}

void ANetGameState::OnRep_RemainingTime()
{
	OnTimerChanged.Broadcast(RemainingTime);
}

void ANetGameState::OnRep_bGameEnded()
{
	OnGameEnded.Broadcast();
}

void ANetGameState::OnRep_WinnerName()
{
	OnWinnerNameChanged.Broadcast(WinnerName);
}
