// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Main.generated.h"

class UUI_Timer;
class UUI_PickupCount;
class UUI_Result;
class UUI_NameEdit;
class ANetPlayerState;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class CYH_NET_API UUI_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMyInfo(const FString& InName, int32 InCount);

	void UpdateOtherInfo(ANetPlayerState* InPlayerState, const FString& InName, int32 InCount);

	void UpdateTime(int32 InTime);

	void UpdateWinnerName(const FString& InName);

	void ShowResult(bool bShow);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_Timer> TimeWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_PickupCount> MyCountWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_Result> ResultWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUI_NameEdit> NameEditWidget = nullptr;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> PlayerList;

	UPROPERTY()
	TMap<ANetPlayerState*, UUI_PickupCount*> PlayerWidgetMap;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUI_PickupCount> PickupCountWidgetClass;

	UPROPERTY()
	TWeakObjectPtr<ANetPlayerState> MyPlayerState = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ANetPlayerState> OtherPlayerState = nullptr;
};
