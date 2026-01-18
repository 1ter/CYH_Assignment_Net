// Fill out your copyright notice in the Description page of Project Settings.


#include "State/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PickupCount = 0;
		OnCountChanged.Broadcast(PickupCount);
	}
}

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, PickupCount);
	DOREPLIFETIME(ANetPlayerState, MyName);
}

void ANetPlayerState::AddCount(int32 InCount)
{
	if (HasAuthority())
	{
		PickupCount += InCount;

		UE_LOG(LogTemp, Warning, TEXT("[SERVER] AddCount -> %d"), PickupCount);

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

void ANetPlayerState::OnRep_PickupCount()
{
	UE_LOG(LogTemp, Warning, TEXT("[CLIENT] OnRep -> %d"), PickupCount);


	OnCountChanged.Broadcast(PickupCount);
}

void ANetPlayerState::OnRep_MyName()
{
	OnNameChanged.Broadcast(MyName);
}