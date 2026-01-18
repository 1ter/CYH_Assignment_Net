// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetGameMode.generated.h"

class ANetGameState;
class ANetPlayerState;

/**
 * 
 */


UCLASS()
class CYH_NET_API ANetGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void StartGameTimer();

	void UpdateTimer();

	void CheckGameOver();

	ANetPlayerState* GetWinnerPlayerState(bool& bOutDraw);

protected:
	UPROPERTY()
	int32 GameDuration = 60;

	UPROPERTY()
	float TimerInterval = 1.0f;

	FTimerHandle GameTimerHandle;

protected:
	TWeakObjectPtr<ANetGameState> NetGameState = nullptr;
};
