// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMod/NetGameMode.h"
#include "State/NetGameState.h"
#include "State/NetPlayerState.h"

void ANetGameMode::BeginPlay()
{
	Super::BeginPlay();

	NetGameState = GetGameState<ANetGameState>();
	if (NetGameState.IsValid())
	{
		NetGameState->SetRemainingTime(GameDuration);

		StartGameTimer();
	}
}

void ANetGameMode::StartGameTimer()
{
	if (UWorld* world = GetWorld())
	{
		if (!world->GetTimerManager().IsTimerActive(GameTimerHandle))
		{
			world->GetTimerManager().SetTimer(
				GameTimerHandle,
				this,
				&ANetGameMode::UpdateTimer,
				TimerInterval,
				true
			);
		}
	}
}

void ANetGameMode::UpdateTimer()
{
	if (NetGameState.IsValid())
	{
		int32 time = NetGameState->GetRemainingTime();
		time = FMath::Max(0, time - 1);

		NetGameState->SetRemainingTime(time);

		if (time <= 0)
		{
			if (UWorld* world = GetWorld())
			{
				world->GetTimerManager().ClearTimer(GameTimerHandle);

				CheckGameOver();
			}
		}
	}
}

void ANetGameMode::CheckGameOver()
{
	if (NetGameState.IsValid())
	{
		bool bDraw = false;

		ANetPlayerState* winner = GetWinnerPlayerState(bDraw);

		NetGameState->SetGameEnded(true);

		if (bDraw || !winner)
		{
			NetGameState->SetWinnerName(TEXT("무승부"));
		}
		else
		{
			NetGameState->SetWinnerName(winner->GetMyName());
		}
	}
}

ANetPlayerState* ANetGameMode::GetWinnerPlayerState(bool& bOutDraw)
{
	bOutDraw = false;
	ANetPlayerState* winner = nullptr;
	int32 bestCount = -1;

	if (!NetGameState.IsValid())
	{
		NetGameState = GetGameState<ANetGameState>();
	}

	if (NetGameState.IsValid())
	{
		for (APlayerState* playerState : NetGameState->PlayerArray)
		{
			if (ANetPlayerState* netPlayerState = Cast<ANetPlayerState>(playerState))
			{
				int32 currentCount = netPlayerState->GetPickupCount(); 

				if (currentCount > bestCount)
				{
					winner = netPlayerState;
					bestCount = currentCount;

					bOutDraw = false;
				}
				else if (bestCount == currentCount)
				{
					bOutDraw = true;
				}
			}
		}
	}

	return bOutDraw ? nullptr : winner;
}
