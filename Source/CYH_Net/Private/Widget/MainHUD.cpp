// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainHUD.h"
#include "Widget/UI_Main.h"
#include "Widget/UI_PickupCount.h"
#include "Widget/UI_Timer.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = GetOwningPlayerController())
	{
		if (playerController && playerController->IsLocalController())
		{
			if (MainHUDclass)
			{
				CurrentWidget = CreateWidget<UUserWidget>(playerController, MainHUDclass);
				if (CurrentWidget.IsValid())
				{
					CurrentWidget->AddToViewport();

					MainWidget = Cast<UUI_Main>(CurrentWidget);
				}
			}

			if (GameLobbyClass)
			{
				GameLobbyWidget = CreateWidget<UUserWidget>(playerController, GameLobbyClass);
				if (GameLobbyWidget.IsValid())
				{
					GameLobbyWidget->AddToViewport(1);
				}
			}
		}
	}
}

void AMainHUD::UpdateMyInfo(const FString& InName, int32 InCount)
{
	if (MainWidget.IsValid())
	{
		MainWidget->UpdateMyInfo(InName, InCount);
	}
}

void AMainHUD::UpdateOtherInfo(ANetPlayerState* InPlayerState, const FString& InName, int32 InCount)
{
	if (MainWidget.IsValid())
	{
		MainWidget->UpdateOtherInfo(InPlayerState, InName, InCount);
	}
}

void AMainHUD::UpdateTime(int32 InTime)
{
	if (MainWidget.IsValid())
	{
		MainWidget->UpdateTime(InTime);
	}
}

void AMainHUD::UpdateWinnerName(const FString& InName)
{
	if (MainWidget.IsValid())
	{
		MainWidget->UpdateWinnerName(InName);
	}
}

void AMainHUD::ShowResult(bool bShow)
{
	if (MainWidget.IsValid())
	{
		MainWidget->ShowResult(bShow);
	}
}