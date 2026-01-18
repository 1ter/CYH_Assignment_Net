// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_Result.h"
#include "Widget/UI_NameTag.h"
#include "State/NetGameState.h"
#include "Components/TextBlock.h"

void UUI_Result::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	if (UWorld* world = GetWorld())
	{
		NetGameState = Cast<ANetGameState>(world->GetGameState());
		if (NetGameState.IsValid())
		{
			NetGameState->OnWinnerNameChanged.AddDynamic(this, &UUI_Result::UpdateWinnerName);
			NetGameState->OnGameEnded.AddDynamic(this, &UUI_Result::OnGameEnded);

			UpdateWinnerName(NetGameState->GetWinnerName());
		}
	}
}

void UUI_Result::NativeDestruct()
{
	Super::NativeDestruct();

	if (NetGameState.IsValid())
	{
		NetGameState->OnWinnerNameChanged.RemoveDynamic(this, &UUI_Result::UpdateWinnerName);
		NetGameState->OnGameEnded.RemoveDynamic(this, &UUI_Result::OnGameEnded);
	}
}

void UUI_Result::UpdateWinnerName(const FString& InName)
{
	if (WinnerName)
	{ 
		WinnerName->SetText(FText::FromString(InName));
	}
}

void UUI_Result::OnGameEnded()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if (NetGameState.IsValid())
	{
		UpdateWinnerName(NetGameState->GetWinnerName());
	}

}


