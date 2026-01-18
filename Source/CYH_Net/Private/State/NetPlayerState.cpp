// Fill out your copyright notice in the Description page of Project Settings.


#include "State/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::AddCount(int32 InCount)
{
	if (HasAuthority())
	{
		PickupCount += InCount;

		OnCountChanged.Broadcast(PickupCount);
	}
}

void ANetPlayerState::SetMyName(const FString& InName)
{
	if (HasAuthority())
	{
		if (InName.IsEmpty())
		{
			MyName = TEXT("Player");
		}
		else
		{
			MyName = InName;
		}

		OnNameChanged.Broadcast(MyName);
	}
}

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANetPlayerState, PickupCount);
	DOREPLIFETIME(ANetPlayerState, MyName);
}

void ANetPlayerState::OnRep_PickupCount()
{
	OnCountChanged.Broadcast(PickupCount);
}

void ANetPlayerState::OnRep_MyName()
{
	OnNameChanged.Broadcast(MyName);
}