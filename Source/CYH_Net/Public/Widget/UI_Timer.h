// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Timer.generated.h"

class UTextBlock;
class ANetGameState;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Timer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(ANetGameState* InGameState);

	UFUNCTION()
	void UpdateTime(int32 InTime);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Timer = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetGameState> NetGameState = nullptr;

};
