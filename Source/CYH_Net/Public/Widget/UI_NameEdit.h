// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_NameEdit.generated.h"

class ACYH_NetCharacter;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_NameEdit : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void NameCommited(const FText& Text, ETextCommit::Type CommitMethod);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> NameInput = nullptr;

private:
	TWeakObjectPtr<ACYH_NetCharacter> PlayerCharacter = nullptr;

};
