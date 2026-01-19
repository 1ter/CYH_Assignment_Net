// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYH_NET_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNetGameInstance();

	virtual void Init() override;

	void CreateServer();

	void JoinServer(FString IPAddress);

	void DisConnectServer();

	inline const FString& GetIPAddress() { return ServerIP; }

protected:
	UPROPERTY(EditDefaultsOnly)
	FString ServerIP;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainLevelAsset = nullptr;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> ServerLevelAsset = nullptr;

	UPROPERTY(EditAnywhere)
	int32 MaxPlayers = 4;	
};
