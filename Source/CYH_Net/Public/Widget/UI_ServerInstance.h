// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_ServerInstance.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_ServerInstance : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCreateButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnDisconnectButtonClicked();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreateButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DisconnectButton = nullptr;	
};
