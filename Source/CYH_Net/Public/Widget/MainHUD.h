// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UUserWidget;
class UUI_Main;
class UUI_PickupCount;
class UUI_Timer;
/**
 *
 */
UCLASS()
class CYH_NET_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	UUI_PickupCount* GetPickupCountWidget();
	UUI_Timer* GetTimerWidget();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainHUDclass = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UUI_Main> MainWidget = nullptr;
};
