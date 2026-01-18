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
		if (ANetGameState* gamestate = Cast<ANetGameState>(world->GetGameState()))
		{
			UpdateWinnerName(gamestate->GetWinnerName());


			ShowResult(gamestate->GetIsGameEnded());
		}
	}
}
void UUI_Result::UpdateWinnerName(const FString& InName)
{
	if (WinnerName)
	{ 
		WinnerName->SetText(FText::FromString(InName));
	}
}

void UUI_Result::ShowResult(bool bShow)
{
	SetVisibility(bShow ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}


