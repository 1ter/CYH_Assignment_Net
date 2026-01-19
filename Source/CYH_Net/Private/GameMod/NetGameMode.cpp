// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMod/NetGameMode.h"
#include "State/NetGameState.h"
#include "State/NetPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/PickupActor.h"
#include "Actor/SpawnBox.h"
#include "Components/BoxComponent.h"

void ANetGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnBox::StaticClass()))
	{
		SpawnBox = Cast<ASpawnBox>(foundActor);
	}

	NetGameState = GetGameState<ANetGameState>();
	if (NetGameState.IsValid())
	{
		NetGameState->SetRemainingTime(GameDuration);

		StartGameTimer();
	}

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&ANetGameMode::SpawnPickupItem,
			3.0f,
			true
		);
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

void ANetGameMode::SpawnPickupItem()
{
	if (HasAuthority())
	{
		if (PickupItemClass && SpawnBox)
		{
			if (UBoxComponent* boxComp = SpawnBox->FindComponentByClass<UBoxComponent>())
			{
				FVector spawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
					boxComp->GetComponentLocation(),
					boxComp->GetScaledBoxExtent()
				);

				FActorSpawnParameters spawnpParams;
				spawnpParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				APickupActor* spawned = GetWorld()->SpawnActor<APickupActor>(
					PickupItemClass,
					spawnLocation,
					FRotator::ZeroRotator,
					spawnpParams
				);

				UE_LOG(LogTemp, Warning, TEXT("스폰!"));
			}
		}
	}
}