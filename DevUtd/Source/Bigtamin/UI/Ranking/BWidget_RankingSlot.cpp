#include "BWidget_RankingSlot.h"
#include "../../FBM_SaveGame.h"
#include "GameMode/BGameMode_main.h"
#include "Bigtamin.h"
#include "UI/Player/BWidget_PlayerDetail.h"

void UBWidget_RankingSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_RankingSlot, &UBWidget_RankingSlot::_OnClick_RankingSlot );
}

void UBWidget_RankingSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_RankingSlot::SetData( E_FILTER_ITEM_TYPE matchType, E_SORT_TYPE sortType, int32 rankNum, FST_PLAYER_DATA playerData, FString nowYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, bool isExceptionStadium )
{
	PlayerName = playerData.PlayerName;

	C_Txt_Num->SetText( FText::AsNumber( rankNum ) );
	C_Txt_Name->SetText( FText::FromString( playerData.PlayerName ) );
	C_Txt_Team->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData.TeamName ) ) );
	C_Txt_Team->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData.TeamName ) );
	C_Txt_Goal->SetText( FText::AsNumber( playerData.GetNewGoalNum( nowYear, curRankingFilterInfo,matchType, isExceptionStadium ) ) );
	C_Txt_Assist->SetText( FText::AsNumber( playerData.GetNewAssistNum( nowYear, curRankingFilterInfo, matchType, isExceptionStadium ) ) );
	C_Txt_Point->SetText( FText::AsNumber( playerData.GetNewPointNum( nowYear, curRankingFilterInfo, matchType, isExceptionStadium ) ) );
	C_Txt_Game->SetText( FText::AsNumber( playerData.GetNewGamesNum( nowYear, curRankingFilterInfo, matchType, isExceptionStadium ) ) );

	C_Txt_Goal->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Assist->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Point->SetColorAndOpacity( Color_StarBucksGrayFont );
	C_Txt_Game->SetColorAndOpacity( Color_StarBucksGrayFont );
	switch( sortType )
	{
	case E_SORT_TYPE::E_SORT_TYPE_GOAL:
		C_Txt_Goal->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ASSIST:
		C_Txt_Assist->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_POINT:
		C_Txt_Point->SetColorAndOpacity( Color_RankBlue );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE:
		C_Txt_Game->SetColorAndOpacity( Color_RankBlue );
	default:
		break;
	}
}

void UBWidget_RankingSlot::_OnClick_RankingSlot()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_PLAYER_DETAIL );
		UBWidget_PlayerDetail* playerDetailWidget = B_HUD->GetWidgetInViewport<UBWidget_PlayerDetail>( EBUIName::PlayerDetail );
		if( playerDetailWidget != nullptr )
		{
			GInst->SetCurSelectPlayerName( PlayerName );
			playerDetailWidget->SetPlayerData( PlayerName );
		}
	}
}
