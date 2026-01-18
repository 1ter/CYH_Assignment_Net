// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_NameEdit.h"
#include "Components/EditableTextBox.h"
#include "Character/CYH_NetCharacter.h"

void UUI_NameEdit::NativeConstruct()
{
	Super::NativeConstruct();

	NameInput->OnTextCommitted.AddDynamic(this, &UUI_NameEdit::NameCommited);
}

void UUI_NameEdit::NameCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (!PlayerCharacter.IsValid())
		{
			if (APlayerController* pc = GetOwningPlayer())
			{
				PlayerCharacter = Cast<ACYH_NetCharacter>(pc->GetPawn());
			}
			
		}
		
		if (PlayerCharacter.IsValid())
		{
			PlayerCharacter->Server_SetPlayerName(Text.ToString());
		}
	}
}
