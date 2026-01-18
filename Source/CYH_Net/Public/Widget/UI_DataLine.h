// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_DataLine.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_DataLine : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetLabel(FText InName);

    void SetIntValue(int32 InValue);

    void SetFloatValue(float InValue);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value = nullptr;
};
