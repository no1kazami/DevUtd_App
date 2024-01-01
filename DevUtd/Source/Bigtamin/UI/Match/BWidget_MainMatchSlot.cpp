#include "BWidget_MainMatchSlot.h"
#include "BWidget_MatchItem.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"

void UBWidget_MainMatchSlot::Init()
{
	Super::Init();

	BP_MatchItem_UMG->Init();

	ButtonDelegate_Clicked( this, C_Btn_More, &UBWidget_MainMatchSlot::_OnClick_MoreBtn );
}

void UBWidget_MainMatchSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_MainMatchSlot::SetDataSchedule()
{
	_MatchInfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE;
	C_Txt_Title->SetText( GET_BTEXT( 2 ) );
	BP_MatchItem_UMG->SetMainDataSchedule();
}

void UBWidget_MainMatchSlot::SetDataResult()
{
	_MatchInfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT;
	C_Txt_Title->SetText( GET_BTEXT( 3 ) );
	BP_MatchItem_UMG->SetMainDataResult();
}

void UBWidget_MainMatchSlot::_OnClick_MoreBtn()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		if ( _MatchInfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE)
		{
			gameMode->ChangeMode( E_MODE::E_MODE_SCHEDULE_MAIN );
		}
		else if( _MatchInfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
		{
			gameMode->ChangeMode( E_MODE::E_MODE_RESULT_MAIN );
		}
	}
}
