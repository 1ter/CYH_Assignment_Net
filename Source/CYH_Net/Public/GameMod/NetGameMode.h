// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetGameMode.generated.h"

class ANetGameState;
class ANetPlayerState;
class ASpawnBox;
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

	void SpawnPickupItem();

	ANetPlayerState* GetWinnerPlayerState(bool& bOutDraw);

protected:
	UPROPERTY(EditAnywhere)
	int32 GameDuration = 60;

	UPROPERTY(EditAnywhere)
	float TimerInterval = 1.0f;

	FTimerHandle GameTimerHandle;

	FTimerHandle SpawnTimerHandle;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PickupItemClass = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ASpawnBox> SpawnBox = nullptr;

	TWeakObjectPtr<ANetGameState> NetGameState = nullptr;
};
