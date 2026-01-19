// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_NameEdit.h"
#include "Components/EditableTextBox.h"
#include "Character/CYH_NetCharacter.h"

void UUI_NameEdit::NativeConstruct()
{
	Super::NativeConstruct();

	if (NameInput)
	{
		NameInput->OnTextCommitted.AddDynamic(this, &UUI_NameEdit::NameCommitted);
	}
}

void UUI_NameEdit::NativeDestruct()
{
	Super::NativeDestruct();

	if (NameInput)
	{
		NameInput->OnTextCommitted.RemoveDynamic(this, &UUI_NameEdit::NameCommitted);
	}
}

void UUI_NameEdit::NameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (!PlayerCharacter.IsValid())
		{
			if (APlayerController* playerController = GetOwningPlayer())
			{
				PlayerCharacter = Cast<ACYH_NetCharacter>(playerController->GetPawn());
			}
		}

		if (PlayerCharacter.IsValid())
		{
			PlayerCharacter->Server_SetPlayerName(Text.ToString());
		}
	}
}
