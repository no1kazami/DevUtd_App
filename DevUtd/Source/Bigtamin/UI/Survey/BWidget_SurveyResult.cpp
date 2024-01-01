// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyResult.h"
#include "GameMode/BGameMode_main.h"
#include "UI/Boots/BWidget_BootsSlot.h"
#include "UI/BWidget_Top.h"
#include "Bigtamin.h"


void UBWidget_SurveyResult::Init()
{
	Super::Init();

	BP_Top_SurveyResult_UMG->Init();
	BP_Top_SurveyResult_UMG->ChangeTopMode( E_MODE::E_MODE_SURVEY_RESULT );
	InitSurveyResult();

	GInst->AddBackInput( this );
}

void UBWidget_SurveyResult::OnClose()
{

}

bool UBWidget_SurveyResult::_OnBackInput()
{
	Super::_OnBackInput();
	CloseUI();

	return true;
}

void UBWidget_SurveyResult::InitSurveyResult()
{
	_SetSurveyResulData();
}

void UBWidget_SurveyResult::_SetSurveyResulData()
{
	if( C_ScrollBox_ResultItem.IsValid() )
	{
		C_ScrollBox_ResultItem.Get()->ClearChildren();
		C_ScrollBox_ResultItem.Get()->ScrollToStart();

 		//for( auto stDataTemp : _ResultItem )
 		//{
 		//}

		for (int32 bootsIndex = 0; bootsIndex < 10; ++bootsIndex)
		{
			UBWidget_BootsSlot* bootsSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_BootsSlot>( EDynamicWidgetParts::BootsSlot );
			if( bootsSlotWidget != nullptr )
			{
				bootsSlotWidget->OwnerPannel = this;
#if DB_BOOTS_DATA
				bootsSlotWidget->SetBootSlotData_DB( bootsIndex, bootsIndex + 1 );
#else
				bootsSlotWidget->SetBootSlotData( bootsIndex, bootsIndex + 1 );
#endif
				C_ScrollBox_ResultItem.Get()->AddChild( bootsSlotWidget );
			}
		}
	}
}
