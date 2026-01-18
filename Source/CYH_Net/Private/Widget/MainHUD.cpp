// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainHUD.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	if (APlayerController* pc = GetOwningPlayerController())
	{
		if (pc && pc->IsLocalController())
		{
			if (MainHUDclass)
			{
				MainWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainHUDclass);
				if (MainWidget.IsValid())
				{
					MainWidget->AddToViewport();
				}
			}
		}
	}
}
