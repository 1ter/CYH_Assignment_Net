// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_ServerInstance.h"
#include "Components/Button.h"
#include "GameInstance/NetGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UUI_ServerInstance::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &UUI_ServerInstance::OnCreateButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UUI_ServerInstance::OnJoinButtonClicked);
	}
	if (DisconnectButton)
	{
		DisconnectButton->OnClicked.AddDynamic(this, &UUI_ServerInstance::OnDisconnectButtonClicked);
	}
}

void UUI_ServerInstance::OnCreateButtonClicked()
{
	UNetGameInstance* GI = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->CreateServer();
	}
}

void UUI_ServerInstance::OnJoinButtonClicked()
{
	UNetGameInstance* GI = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->JoinServer(TEXT("127.0.0.1"));
	}
}

void UUI_ServerInstance::OnDisconnectButtonClicked()
{
	UNetGameInstance* GI = Cast<UNetGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->DisConnectServer();
	}
}