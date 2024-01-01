// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemManyImgSlot.h"
#include "BWidget_SurveyItemManyImgBtn.h"


void UBWidget_SurveyItemManyImgSlot::Init()
{
	Super::Init();

	if (C_CheckBox.IsValid())
	{
		C_CheckBox.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemManyImgSlot::_OnSlotCheckStateChanged);
		C_CheckBox.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemManyImgSlot::_OnSlotCheckStateChanged);
	}

	_SlotIndex = -1;
}

void UBWidget_SurveyItemManyImgSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemManyImgSlot::SetSlotData(int32 slotIndex, FString exampleTxt, FString imgUrl)
{
	_SlotIndex = slotIndex;

	if (C_Txt_Example.IsValid())
	{
		C_Txt_Example.Get()->SetText(FText::FromString(exampleTxt));
	}

	UTexture2D* textureSlot = GetTexture(imgUrl);
	if (textureSlot != nullptr)
	{
		C_Img_Slot->SetBrushFromTexture(textureSlot, true);
	}
}

void UBWidget_SurveyItemManyImgSlot::_OnSlotCheckStateChanged(bool isChecked)
{
	if (UBWidget_SurveyItemManyImgBtn* ownerSurveyItem = Cast<UBWidget_SurveyItemManyImgBtn>(OwnerPannel))
	{
		ownerSurveyItem->SetOverLapCheckIndex(_SlotIndex, isChecked);
	}
}
