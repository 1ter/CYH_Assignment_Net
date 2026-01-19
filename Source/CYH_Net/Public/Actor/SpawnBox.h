// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

class UBoxComponent;

UCLASS()
class CYH_NET_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnBox();

	UBoxComponent* GetBox() { return SpawnBox; }

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> SpawnBox = nullptr;
};
