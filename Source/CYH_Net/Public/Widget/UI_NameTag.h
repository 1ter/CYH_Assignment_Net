// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_NameTag.generated.h"

class UTextBlock;
class ANetPlayerState;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_NameTag : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
    void UpdateName(const FString& InName);
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetPlayerState> NetPlayerState = nullptr;
};
