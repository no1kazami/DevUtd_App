// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemTwoTextDownBtn.h"



void UBWidget_SurveyItemTwoTextDownBtn::Init()
{
	Super::Init();

	if (C_CheckBox_1.IsValid())
	{
		C_CheckBox_1.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged1);
		C_CheckBox_1.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged1);
	}
	if (C_CheckBox_2.IsValid())
	{
		C_CheckBox_2.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged2);
		C_CheckBox_2.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged2);
	}
	if (C_CheckBox_Down1.IsValid())
	{
		C_CheckBox_Down1.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged1);
		C_CheckBox_Down1.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged1);
	}
	if (C_CheckBox_Down2.IsValid())
	{
		C_CheckBox_Down2.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged2);
		C_CheckBox_Down2.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged2);
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemTwoTextDownBtn::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_SetSubTitleText();
	_SetSurveyItemExampleText();
	_SetSurveyItemDownExampleText();
}

void UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged1(bool isChecked)
{
	if (isChecked)
	{
		_CurCheckIndex = 1;
		_CheckOtherState();
		C_VB_DownSurvey->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		_CurCheckIndex = 0;
		C_VB_DownSurvey->SetVisibility(ESlateVisibility::Collapsed);
		_OnSurveyDownCheckStateChanged1(false);
		_OnSurveyDownCheckStateChanged2(false);
		_CheckDownOtherState();
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyCheckStateChanged2(bool isChecked)
{
	if (isChecked)
	{
		_CurCheckIndex = 2;
		_CheckOtherState();
		C_VB_DownSurvey->SetVisibility(ESlateVisibility::Collapsed);
		_OnSurveyDownCheckStateChanged1(false);
		_OnSurveyDownCheckStateChanged2(false);
		_CheckDownOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
		C_VB_DownSurvey->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged1(bool isChecked)
{
	if (isChecked)
	{
		_CurDownCheckIndex = 1;
		_CheckDownOtherState();
	}
	else
	{
		_CurDownCheckIndex = 0;
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_OnSurveyDownCheckStateChanged2(bool isChecked)
{
	if (isChecked)
	{
		_CurDownCheckIndex = 2;
		_CheckDownOtherState();
	}
	else
	{
		_CurDownCheckIndex = 0;
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_SetSubTitleText()
{
	if (C_Txt_SubTitle.IsValid())
	{
		C_Txt_SubTitle.Get()->SetText(FText::FromString(_SurveyInfo.strSurveySubTitle));
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_SetSurveyItemExampleText()
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

void UBWidget_SurveyItemTwoTextDownBtn::_SetSurveyItemDownExampleText()
{
	for (int32 index = 0; index < _SurveyInfo.arDownExampleBtnText.Num(); index++)
	{
		if (index == 0 && C_Txt_Example_Down1.IsValid())
		{
			C_Txt_Example_Down1.Get()->SetText(FText::FromString(_SurveyInfo.arDownExampleBtnText[index]));
		}
		else if (index == 1 && C_Txt_Example_Down2.IsValid())
		{
			C_Txt_Example_Down2.Get()->SetText(FText::FromString(_SurveyInfo.arDownExampleBtnText[index]));
		}
	}
}

void UBWidget_SurveyItemTwoTextDownBtn::_CheckOtherState()
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

void UBWidget_SurveyItemTwoTextDownBtn::_CheckDownOtherState()
{
	C_CheckBox_Down1->SetCheckedState(ECheckBoxState::Unchecked);
	C_CheckBox_Down2->SetCheckedState(ECheckBoxState::Unchecked);

	switch (_CurDownCheckIndex)
	{
	case 1:
		C_CheckBox_Down1->SetCheckedState(ECheckBoxState::Checked);
		break;
	case 2:
		C_CheckBox_Down2->SetCheckedState(ECheckBoxState::Checked);
		break;
	}
}
