// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemManyTextSlot.h"
#include "BWidget_SurveyItemManyTextBtn.h"


void UBWidget_SurveyItemManyTextSlot::Init()
{
	Super::Init();

	if (C_CheckBox.IsValid())
	{
		C_CheckBox.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemManyTextSlot::_OnSurveyCheckStateChanged);
		C_CheckBox.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemManyTextSlot::_OnSurveyCheckStateChanged);
	}

	_SlotIndex = -1;
	_IsOnlyOne = false;
}

void UBWidget_SurveyItemManyTextSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemManyTextSlot::SetSlotData( int32 slotIndex, FString exampleTxt )
{
	_SlotIndex = slotIndex;

	if (C_Txt_Example.IsValid())
	{
		C_Txt_Example.Get()->SetText(FText::FromString(exampleTxt));
	}

	FText textExample = FText::FromString( exampleTxt );
	FText onlyOneText1 = GET_BTEXT( 112 );
	FText onlyOneText2 = GET_BTEXT( 113 );
	if ( textExample.EqualTo(onlyOneText1) || textExample.EqualTo( onlyOneText2 ) )
	{
		_IsOnlyOne = true;
	}
	else
	{
		_IsOnlyOne = false;
	}
}

void UBWidget_SurveyItemManyTextSlot::SetCheckOtherState( int32 exceptionCheckIndex, bool isCheck )
{
	if( C_CheckBox.IsValid() )
	{
		if( exceptionCheckIndex != _SlotIndex )
		{
			C_CheckBox->SetCheckedState( isCheck ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
		}
	}
}

void UBWidget_SurveyItemManyTextSlot::_OnSurveyCheckStateChanged(bool isChecked)
{
	if (UBWidget_SurveyItemManyTextBtn* ownerSurveyItem = Cast<UBWidget_SurveyItemManyTextBtn>(OwnerPannel))
	{
		ownerSurveyItem->SetOverLapCheckIndex(_SlotIndex, isChecked, _IsOnlyOne );
	}
}
