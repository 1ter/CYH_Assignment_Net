// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_PickupCount.generated.h"

class UTextBlock;
class ANetPlayerState;

/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_PickupCount : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindPlayerState(ANetPlayerState* InPlayerState);

	UFUNCTION()
	void UpdatePickupCount(int32 InCount);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PickupCount = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetPlayerState> NetPlayerState = nullptr;
};
