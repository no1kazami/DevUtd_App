// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemManyImgBtn.h"
#include "BWidget_SurveyItemManyImgSlot.h"
#include "Bigtamin.h"


void UBWidget_SurveyItemManyImgBtn::Init()
{
	Super::Init();

	if (C_CheckBox_Down.IsValid())
	{
		C_CheckBox_Down.Get()->OnCheckStateChanged.RemoveDynamic(this, &UBWidget_SurveyItemManyImgBtn::_OnDropDownCheckStateChanged);
		C_CheckBox_Down.Get()->OnCheckStateChanged.AddDynamic(this, &UBWidget_SurveyItemManyImgBtn::_OnDropDownCheckStateChanged);
	}
}

void UBWidget_SurveyItemManyImgBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemManyImgBtn::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_AddDropDownSlot();

	C_Txt_SlotTitle.Get()->SetText(FText::FromString(surveyInfo.strSurveySubTitle));
}

void UBWidget_SurveyItemManyImgBtn::SetOverLapCheckIndex(int32 checkIndex, bool isChecked)
{
	if (isChecked)
		_CurOverLapCheckIndex.AddUnique(checkIndex);
	else
		_CurOverLapCheckIndex.Remove(checkIndex);
}

void UBWidget_SurveyItemManyImgBtn::_OnDropDownCheckStateChanged(bool isChecked)
{
	UTexture2D* textureFrame;

	if (isChecked)
	{
		C_SizeBox_DropDownList.Get()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		C_Img_DownArrow->SetRenderTransformAngle(180.f);

		textureFrame = GetTexture(TEXT("Survey/ManySelect_OpenFrame"));
	}
	else
	{
		C_SizeBox_DropDownList.Get()->SetVisibility(ESlateVisibility::Collapsed);
		C_Img_DownArrow->SetRenderTransformAngle(0.f);

		textureFrame = GetTexture(TEXT("Survey/ManySelect_Frame"));
	}

	if (textureFrame != nullptr)
	{
		C_Img_Frame->SetBrushFromTexture(textureFrame, true);
	}
}

void UBWidget_SurveyItemManyImgBtn::_AddDropDownSlot()
{
	if (C_UGP_DropDownList.IsValid())
	{
		for (int32 index = 0; index < _SurveyInfo.arExampleBtnText.Num(); index++)
		{
			UBWidget_SurveyItemManyImgSlot* manyTextSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemManyImgSlot>(EDynamicWidgetParts::SurveyItemManyImgBtnSlot);
			if (manyTextSlotWidget != nullptr)
			{
				manyTextSlotWidget->OwnerPannel = this;
				manyTextSlotWidget->SetSlotData(index, _SurveyInfo.arExampleBtnText[index], _SurveyInfo.arExampleBtnAddress[index]);
				UUniformGridSlot* uniformGridSlot = C_UGP_DropDownList.Get()->AddChildToUniformGrid(manyTextSlotWidget);
				if (uniformGridSlot != nullptr)
				{
					uniformGridSlot->SetColumn(index % 4);
					uniformGridSlot->SetRow(index / 4);
				}
			}
		}
	}
}
