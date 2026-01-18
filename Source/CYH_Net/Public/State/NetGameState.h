// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NetGameState.generated.h"

class AMainHUD;
/**
 *
 */

UCLASS()
class CYH_NET_API ANetGameState : public AGameState
{
	GENERATED_BODY()

public:
	inline int32 GetRemainingTime() const { return RemainingTime; }
	inline void SetRemainingTime(int32 InTime)
	{
		if (HasAuthority())
		{
			RemainingTime = InTime;
			OnRep_RemainingTime();
		}
	}

	inline bool GetIsGameEnded() const { return bGameEnded; }
	inline void SetGameEnded(bool bInEnded)
	{
		if (HasAuthority())
		{
			bGameEnded = bInEnded;
			OnRep_GameEnded();
		}
	}

	inline const FString& GetWinnerName() const { return WinnerName; }
	inline void SetWinnerName(const FString& InName)
	{
		if (HasAuthority())
		{
			WinnerName = InName;
			OnRep_WinnerName();
		}
	}

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_RemainingTime();
	UFUNCTION()
	void OnRep_GameEnded();
	UFUNCTION()
	void OnRep_WinnerName();

protected:
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_RemainingTime)
	int32 RemainingTime = 60;

	UPROPERTY(ReplicatedUsing = OnRep_GameEnded)
	bool bGameEnded = false;

	UPROPERTY(ReplicatedUsing = OnRep_WinnerName)
	FString WinnerName;

	TWeakObjectPtr<AMainHUD> MainHUD = nullptr;
};
