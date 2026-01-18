// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Main.generated.h"

class UUI_DataLine;
class UEditableTextBox;
class ANetGameState;
class ANetPlayerState;

/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateName(const FString& InName);

	UFUNCTION()
	void UpdatePickupCount(int32 InCount);

	UFUNCTION()
	void UpdateTime(int32 InTime);


protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_DataLine> Name = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_DataLine> PickupCount = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_DataLine> Timer = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> NameInput = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetGameState> NetGameState = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetPlayerState> NetPlayerState = nullptr;
};
