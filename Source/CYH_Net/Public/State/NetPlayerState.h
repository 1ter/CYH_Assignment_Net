// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */

UCLASS()
class CYH_NET_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddCount(int32 InCount);

	UFUNCTION()
	void SetMyName(const FString& InName);

	void UpdateHUD();

	inline int32 GetPickupCount() const { return PickupCount; }
	inline const FString& GetMyName() const { return MyName; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_PickupCount();

	UFUNCTION()
	void OnRep_MyName();

	void UpdateNameTag();

private:
	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_PickupCount)
	int32 PickupCount = 0;

	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = OnRep_MyName)
	FString MyName;
};
