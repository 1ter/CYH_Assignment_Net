// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NetPlayerController.h"

void ANetPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
}
