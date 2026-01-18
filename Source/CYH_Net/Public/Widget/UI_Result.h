// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Result.generated.h"

class UUI_DataLine;
class ANetGameState;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Result : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateWinnerName(const FString& InName);

	UFUNCTION()
	void OnGameEnded();


protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_DataLine> WinnerName = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetGameState> NetGameState = nullptr;
	
};
