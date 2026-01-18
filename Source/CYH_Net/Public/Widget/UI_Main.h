// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Main.generated.h"

class UUI_Timer;
class UUI_PickupCount;
class UUI_NameTag;
class UUI_Result;
class UUI_NameEdit;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	inline UUI_Timer* GetTimerWidget() { return TimeWidget; }
	inline UUI_PickupCount* GetPickupCountWidget() { return PickupCountWidget; }

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_Timer> TimeWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_PickupCount> PickupCountWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_Result> ResultWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_NameEdit> NameEditWidget = nullptr;
};
