// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemManyTextBtn.h"
#include "BWidget_SurveyItemManyTextSlot.h"
#include "Bigtamin.h"

void UBWidget_SurveyItemManyTextBtn::Init()
{
	Super::Init();

	_IsCurOnlyOne = false;
}

void UBWidget_SurveyItemManyTextBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemManyTextBtn::SetCurSurveyItem(FST_SURVEY_INFO surveyInfo)
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_AddSurveySlot();
}

void UBWidget_SurveyItemManyTextBtn::SetOverLapCheckIndex(int32 checkIndex, bool isChecked, bool isOnlyOne )
{
	if( _IsCurOnlyOne)
	{
		_CurOverLapCheckIndex.Empty();
		_IsCurOnlyOne = false;
		_CheckOtherState( checkIndex, false );
	}
	else if( isOnlyOne && isChecked )
	{
		_CurOverLapCheckIndex.Empty();
		_IsCurOnlyOne = true;
		_CheckOtherState( checkIndex, false );
	}

	if( isChecked )
	{
		_CurOverLapCheckIndex.AddUnique( checkIndex );
	}
	else
	{
		if ( _CurOverLapCheckIndex.Num() > 0)
			_CurOverLapCheckIndex.Remove( checkIndex );
	}
}

void UBWidget_SurveyItemManyTextBtn::_AddSurveySlot()
{
	if (C_UGP_Slots.IsValid())
	{
		for (int32 index = 0; index < _SurveyInfo.arExampleBtnText.Num(); index++)
		{
			UBWidget_SurveyItemManyTextSlot* manyTextSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemManyTextSlot>(EDynamicWidgetParts::SurveyItemManyTextSlot);
			if (manyTextSlotWidget != nullptr)
			{
				manyTextSlotWidget->OwnerPannel = this; 
				manyTextSlotWidget->SetSlotData(index, _SurveyInfo.arExampleBtnText[index]);
				UUniformGridSlot* uniformGridSlot = C_UGP_Slots.Get()->AddChildToUniformGrid(manyTextSlotWidget);
				if (uniformGridSlot != nullptr)
				{
					uniformGridSlot->SetColumn(index % 3);
					uniformGridSlot->SetRow(index / 3);
				}
			}
		}
	}
}

void UBWidget_SurveyItemManyTextBtn::_CheckOtherState( int32 exceptionCheckIndex, bool isChecked )
{
	if( C_UGP_Slots.IsValid() )
	{
		for( int i = 0; i < C_UGP_Slots->GetChildrenCount(); i++ )
		{
			UBWidget_SurveyItemManyTextSlot* It = Cast<UBWidget_SurveyItemManyTextSlot>( C_UGP_Slots->GetChildAt( i ) );
			if( It )
			{
				It->SetCheckOtherState( exceptionCheckIndex, isChecked );
			}
		}
	}
}
