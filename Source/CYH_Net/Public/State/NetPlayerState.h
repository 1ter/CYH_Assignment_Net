// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountChanged, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameChanged, const FString&, NewName);

UCLASS()
class CYH_NET_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddCount(int32 InCount);

	UFUNCTION()
	void SetMyName(const FString& InName);

	inline int32 GetPickupCount() const { return PickupCount; }
	inline FString GetMyName() const { return MyName; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_PickupCount();

	UFUNCTION()
	void OnRep_MyName();

public:
	FOnCountChanged OnCountChanged;
	FOnNameChanged OnNameChanged;

private:
	UPROPERTY(ReplicatedUsing = OnRep_PickupCount)
	int32 PickupCount = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MyName)
	FString MyName;
};
