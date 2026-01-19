// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SpawnBox.h"
#include "Components/BoxComponent.h"

ASpawnBox::ASpawnBox()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

