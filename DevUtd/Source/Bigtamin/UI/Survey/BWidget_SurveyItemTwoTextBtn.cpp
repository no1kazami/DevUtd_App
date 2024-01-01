// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemTwoTextBtn.h"


void UBWidget_SurveyItemTwoTextBtn::Init()
{
	Super::Init();

	if (C_CheckBox_1.IsValid())
	{
		C_CheckBox_1.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged1);
		C_CheckBox_1.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged1);
	}
	if (C_CheckBox_2.IsValid())
	{
		C_CheckBox_2.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged2);
		C_CheckBox_2.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged2);
	}
}

void UBWidget_SurveyItemTwoTextBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemTwoTextBtn::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_SetSurveyItemExampleText();
}

void UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged1(bool isChecked)
{
	if (isChecked)
	{
		_CurCheckIndex = 1;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}
}

void UBWidget_SurveyItemTwoTextBtn::_OnSurveyCheckStateChanged2(bool isChecked)
{
	if (isChecked)
	{
		_CurCheckIndex = 2;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}
}

void UBWidget_SurveyItemTwoTextBtn::_SetSurveyItemExampleText()
{
	for (int32 index = 0; index < _SurveyInfo.arExampleBtnText.Num(); index++)
	{
		if (index == 0 && C_Txt_Example_1.IsValid())
		{
			C_Txt_Example_1.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
		}
		else if (index == 1 && C_Txt_Example_2.IsValid())
		{
			C_Txt_Example_2.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
		}
	}
}

void UBWidget_SurveyItemTwoTextBtn::_CheckOtherState()
{
	C_CheckBox_1->SetCheckedState(ECheckBoxState::Unchecked);
	C_CheckBox_2->SetCheckedState(ECheckBoxState::Unchecked);

	switch (_CurCheckIndex)
	{
	case 1:
		C_CheckBox_1->SetCheckedState(ECheckBoxState::Checked);
		break;
	case 2:
		C_CheckBox_2->SetCheckedState(ECheckBoxState::Checked);
		break;
	}
}
