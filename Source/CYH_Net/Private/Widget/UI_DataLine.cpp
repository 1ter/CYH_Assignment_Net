// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UI_DataLine.h"
#include "Components/TextBlock.h"

void UUI_DataLine::SetLabel(FText InName)
{
	Label->SetText(InName);
}

void UUI_DataLine::SetIntValue(int32 InValue)
{
	Value->SetText(FText::AsNumber(InValue));
}

void UUI_DataLine::SetFloatValue(float InValue)
{
	Value->SetText(FText::AsNumber(static_cast<int32>(InValue)));
}

