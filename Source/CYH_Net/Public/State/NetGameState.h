// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NetGameState.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChanged, int32, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWinnerNameChanged, const FString&, NewName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnded);

UCLASS()
class CYH_NET_API ANetGameState : public AGameState
{
	GENERATED_BODY()

public:
	ANetGameState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	inline int32 GetRemainingTime() const { return RemainingTime; }
	inline void SetRemainingTime(int32 InTime)
	{
		RemainingTime = InTime;
		OnTimerChanged.Broadcast(RemainingTime);
	}

	inline bool GetIsGameEnded() const { return bGameEnded; }
	inline void SetbGameEnded(bool bInEnded)
	{
		if (HasAuthority())
		{
			bGameEnded = bInEnded;
			OnGameEnded.Broadcast();
		}
	}

	inline const FString& GetWinnerName() const { return WinnerName; }
	inline void SetWinnerName(const FString& InName)
	{
		if (HasAuthority())
		{
			WinnerName = InName;
			OnWinnerNameChanged.Broadcast(WinnerName);
		}
	}

protected:
	UFUNCTION()
	void OnRep_RemainingTime();
	UFUNCTION()
	void OnRep_bGameEnded();
	UFUNCTION()
	void OnRep_WinnerName();

public:
	UPROPERTY()
	FOnTimerChanged OnTimerChanged;
	UPROPERTY()
	FOnGameEnded OnGameEnded;
	UPROPERTY()
	FOnWinnerNameChanged OnWinnerNameChanged;

protected:
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_RemainingTime)
	int32 RemainingTime = 60;

	UPROPERTY(ReplicatedUsing = OnRep_bGameEnded)
	bool bGameEnded = false;

	UPROPERTY(ReplicatedUsing = OnRep_WinnerName)
	FString WinnerName;
};
