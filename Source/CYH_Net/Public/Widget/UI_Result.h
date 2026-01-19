// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Result.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Result : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWinnerName(const FString& InName);

	void ShowResult(bool bShow);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WinnerName = nullptr;
};
