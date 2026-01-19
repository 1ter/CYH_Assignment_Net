// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UUserWidget;
class UUI_Main;
class ANetPlayerState;

/**
 *
 */
UCLASS()
class CYH_NET_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	void UpdateMyInfo(const FString& InName, int32 InCount);

	void UpdateOtherInfo(ANetPlayerState* InPlayerState, const FString& InName, int32 InCount);

	void UpdateTime(int32 InTime);

	void UpdateWinnerName(const FString& InName);

	void ShowResult(bool bShow);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainHUDclass = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UUserWidget> CurrentWidget = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UUI_Main> MainWidget = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameLobbyClass = nullptr;
	
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> GameLobbyWidget = nullptr;
};
