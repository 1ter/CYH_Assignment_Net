// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/NetGameInstance.h"
#include "Kismet/GameplayStatics.h"

UNetGameInstance::UNetGameInstance()
{
	ServerIP = "127.0.0.1";
}

void UNetGameInstance::Init()
{
	Super::Init();
}

void UNetGameInstance::CreateServer()
{
	FString MapName;
	if (!ServerLevelAsset.IsNull())
	{
		MapName = ServerLevelAsset.GetLongPackageName();
	}
	else
	{
		MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	}

	if (UWorld* world = GetWorld())
	{
		FString options = FString::Printf(TEXT("listen?MaxPlayers=%d"), MaxPlayers);
		UGameplayStatics::OpenLevel(world, FName(*MapName), true, options);
	}
}

void UNetGameInstance::JoinServer(FString IPAddress)
{
	if (IPAddress.IsEmpty())
	{
		IPAddress = ServerIP;
	}

	if (UWorld* world = GetWorld())
	{
		if (APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0))
		{
			playerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UNetGameInstance::DisConnectServer()
{
	FString MapName;
	if (!MainLevelAsset.IsNull())
	{
		MapName = MainLevelAsset.GetLongPackageName();
	}
	else
	{
		return;
	}

	if (UWorld* world = GetWorld())
	{
		if (APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0))
		{
			playerController->ClientTravel(MapName, ETravelType::TRAVEL_Absolute);
		}
	}
}