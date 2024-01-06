#include "BWidget_ScheduleDetail.h"
#include "BWidget_MatchItem.h"
#include "BWidget_ResultDetailSlot.h"
#include "UI/BWidget_Top.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"
#include "Kismet/KismetSystemLibrary.h"

void UBWidget_ScheduleDetail::Init()
{
	Super::Init();

	BP_Top_MainScheduleDetail_UMG->Init();
	BP_Top_MainScheduleDetail_UMG->ChangeTopMode( E_MODE::E_MODE_SCHEDULE_DETAIL );

	BP_MatchItem_UMG->Init();

	_Ani_ResultDetailOpen = GetWidgetAnimation( _Ani_ResultDetailOpenName );
	_Ani_ResultDetailClose = GetWidgetAnimation( _Ani_ResultDetailCloseName );

	ButtonDelegate_Clicked( this, C_Btn_TMap, &UBWidget_ScheduleDetail::_OnClick_TMap );
	ButtonDelegate_Clicked( this, C_Btn_KakaoNavi, &UBWidget_ScheduleDetail::_OnClick_KakaoNavi );
	ButtonDelegate_Clicked( this, C_Btn_NaverMap, &UBWidget_ScheduleDetail::_OnClick_NaverMap );

	GInst->AddBackInput( this );

	PlayResultDetailOpenAni( true );
}

void UBWidget_ScheduleDetail::OnClose()
{
	Super::OnClose();
}

void UBWidget_ScheduleDetail::SetData( FST_MATCH_DATA matchData )
{
	_MatchData = matchData;
	BP_MatchItem_UMG->SetMatchItem( matchData );

	const FST_STADIUM_INFO_DATA* stadiumData = UFBM_SaveGame::Get().GetStadiumData_DB_ByName( _MatchData.Comment );
	if( stadiumData )
	{
		FText stadiumAddress = FText::FromString( stadiumData->Address );
		C_Txt_Address->SetText( stadiumAddress );
	}
}

void UBWidget_ScheduleDetail::PlayResultDetailOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_ResultDetailOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultDetailOpen ) )
			{
				StopAnimation( _Ani_ResultDetailOpen );
			}

			PlayAnimation( _Ani_ResultDetailOpen );
		}
	}
	else
	{
		if( _Ani_ResultDetailClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultDetailClose ) )
			{
				StopAnimation( _Ani_ResultDetailClose );
			}

			PlayAnimation( _Ani_ResultDetailClose );
		}
	}
}

bool UBWidget_ScheduleDetail::_OnBackInput()
{
	Super::_OnBackInput();
	PlayResultDetailOpenAni( false );
	return true;
}

void UBWidget_ScheduleDetail::_OnClick_TMap()
{
	const FST_STADIUM_INFO_DATA* stadiumData = UFBM_SaveGame::Get().GetStadiumData_DB_ByName( _MatchData.Comment );
	if( stadiumData && stadiumData->NaviURL_TMap.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( stadiumData->NaviURL_TMap );
	}
}

void UBWidget_ScheduleDetail::_OnClick_KakaoNavi()
{
	const FST_STADIUM_INFO_DATA* stadiumData = UFBM_SaveGame::Get().GetStadiumData_DB_ByName( _MatchData.Comment );
	if( stadiumData && stadiumData->NaviURL_Kakao.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( stadiumData->NaviURL_Kakao );
	}
}

void UBWidget_ScheduleDetail::_OnClick_NaverMap()
{
	const FST_STADIUM_INFO_DATA* stadiumData = UFBM_SaveGame::Get().GetStadiumData_DB_ByName( _MatchData.Comment );
	if( stadiumData && stadiumData->NaviURL_Naver.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( stadiumData->NaviURL_Naver );
	}
}
