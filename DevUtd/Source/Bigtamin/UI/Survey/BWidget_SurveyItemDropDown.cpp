// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemDropDown.h"
#include "BWidget_SurveyItemDropDownSLot.h"
#include "Bigtamin.h"


void UBWidget_SurveyItemDropDown::Init()
{
	Super::Init();

	if (C_CheckBox_Down.IsValid())
	{
		C_CheckBox_Down.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemDropDown::_OnDropDownCheckStateChanged);
		C_CheckBox_Down.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemDropDown::_OnDropDownCheckStateChanged);
	}
}

void UBWidget_SurveyItemDropDown::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemDropDown::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_SetDropDownListInfo();
}

void UBWidget_SurveyItemDropDown::OnClickDropDownSlot(int32 checkIndex, FString slotString)
{
	C_Img_DownArrow->SetRenderTransformAngle(0.f);
	C_OL_DropDownList->SetVisibility(ESlateVisibility::Collapsed);
	C_Txt_DropDownSelect.Get()->SetText(FText::FromString(slotString));
	_CurCheckIndex = checkIndex + 1;
}

void UBWidget_SurveyItemDropDown::_OnDropDownCheckStateChanged(bool isChecked)
{
	if (isChecked)
	{
		C_Img_DownArrow->SetRenderTransformAngle(180.f);
		C_OL_DropDownList->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		C_Img_DownArrow->SetRenderTransformAngle(0.f);
		C_OL_DropDownList->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBWidget_SurveyItemDropDown::_SetDropDownListInfo()
{
	if (C_SB_DropDownList.IsValid())
	{
		C_SB_DropDownList.Get()->ClearChildren();

		for (int32 index = 0; index < _SurveyInfo.arExampleBtnText.Num(); index++)
		{
			UBWidget_SurveyItemDropDownSLot* dropDownSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemDropDownSLot>(EDynamicWidgetParts::SurveyItemDropDownSlot);
			if (dropDownSlotWidget != nullptr)
			{
				dropDownSlotWidget->OwnerPannel = this;
				dropDownSlotWidget->SetSlotData(index, _SurveyInfo.arExampleBtnText[index]);

				C_SB_DropDownList->AddChild(dropDownSlotWidget);
			}
		}
	}
}
