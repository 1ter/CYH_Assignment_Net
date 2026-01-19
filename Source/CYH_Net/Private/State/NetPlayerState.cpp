// Fill out your copyright notice in the Description page of Project Settings.


#include "State/NetPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Widget/MainHUD.h"
#include "Character/CYH_NetCharacter.h"

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

		OnRep_PickupCount();
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

		OnRep_MyName();
	}
}

void ANetPlayerState::UpdateHUD()
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController && playerController->GetHUD<AMainHUD>())
	{
		if (AMainHUD* mainHUD = playerController->GetHUD<AMainHUD>())
		{
			if (this == playerController->PlayerState)
			{
				mainHUD->UpdateMyInfo(GetMyName(), PickupCount);
			}
			else
			{
				mainHUD->UpdateOtherInfo(this, GetMyName(), PickupCount);
			}
		}
	}
}

void ANetPlayerState::OnRep_PickupCount()
{
	UpdateHUD();
	UpdateNameTag();
}

void ANetPlayerState::OnRep_MyName()
{
	UpdateHUD();
	UpdateNameTag();
}

void ANetPlayerState::UpdateNameTag()
{
	if (ACYH_NetCharacter* character = Cast<ACYH_NetCharacter>(GetPawn()))
	{
		character->UpdateNameTag(MyName);
	}
}
