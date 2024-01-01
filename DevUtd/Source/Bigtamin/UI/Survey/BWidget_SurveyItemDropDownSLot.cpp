// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemDropDownSLot.h"
#include "BWidget_SurveyItemDropDown.h"



void UBWidget_SurveyItemDropDownSLot::Init()
{
	Super::Init();

	if (C_Btn_DropDownSlot.IsValid())
		ButtonDelegate_Clicked(this, C_Btn_DropDownSlot.Get(), &UBWidget_SurveyItemDropDownSLot::_OnClickDropDownSlotBtn);

	_SlotIndex = -1;
}

void UBWidget_SurveyItemDropDownSLot::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemDropDownSLot::SetSlotData(int32 slotIndex, FString exampleTxt)
{
	_SlotIndex = slotIndex;
	_slotText = exampleTxt;

	if (C_Txt_DropDownSlot.IsValid())
	{
		C_Txt_DropDownSlot.Get()->SetText(FText::FromString(_slotText));
	}
}

void UBWidget_SurveyItemDropDownSLot::_OnClickDropDownSlotBtn()
{
	if (UBWidget_SurveyItemDropDown* ownerDropDown = Cast<UBWidget_SurveyItemDropDown>(OwnerPannel))
	{
		ownerDropDown->OnClickDropDownSlot(_SlotIndex, _slotText);
	}
}
