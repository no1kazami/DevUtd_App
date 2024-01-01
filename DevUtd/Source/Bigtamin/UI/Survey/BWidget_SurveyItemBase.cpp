// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemBase.h"


void UBWidget_SurveyItemBase::Init()
{
	_CurOverLapCheckIndex.Empty();
	_CurCheckIndex = 0;
	_CurDownCheckIndex = 0;
}

void UBWidget_SurveyItemBase::OnClose()
{

}

bool UBWidget_SurveyItemBase::IsCheckSelected() const
{
	bool isSelected = false;

	switch( _SurveyInfo.eSurveyType )
	{
	case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_RECT_BTN:
	case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_CIRCLE_BTN:
	case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN:
	case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_BTN:
		{
			isSelected = _CurCheckIndex > 0;
		}
		break;
	case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN:
		{
			if( _CurCheckIndex == 1 )
			{
				isSelected = _CurDownCheckIndex > 0;
			}
			else
			{
				isSelected = _CurCheckIndex > 0;
			}
		}
		break;
	case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN:
	case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN:
		{
			isSelected = _CurOverLapCheckIndex.Num() > 0;
		}
		break;
	}

	return isSelected;
}

void UBWidget_SurveyItemBase::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	_SurveyInfo = surveyInfo;
}

void UBWidget_SurveyItemBase::_SetTitleText()
{
	if (C_Txt_Title.IsValid())
	{
		C_Txt_Title.Get()->SetText(FText::FromString(_SurveyInfo.strSurveyTitle));
	}
}
