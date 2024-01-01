#include "BWidget_MainRankingSlot.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"
#include "UI/Ranking/BWidget_RankingMain.h"
#include "../../FBM_SaveGame.h"

#define SHOW_RANK_NUM 3

void UBWidget_MainRankingSlot::Init()
{
	Super::Init();

	OnSuccessDownLoadPlayerImage1.BindUFunction( this, "_OnSuccessDownLoadPlayerImage1" );
	OnFailDownLoadPlayerImage1.BindUFunction( this, "_OnFailDownLoadPlayerImage1" );
	OnSuccessDownLoadPlayerImage2.BindUFunction( this, "_OnSuccessDownLoadPlayerImage2" );
	OnFailDownLoadPlayerImage2.BindUFunction( this, "_OnFailDownLoadPlayerImage2" );
	OnSuccessDownLoadPlayerImage3.BindUFunction( this, "_OnSuccessDownLoadPlayerImage3" );
	OnFailDownLoadPlayerImage3.BindUFunction( this, "_OnFailDownLoadPlayerImage3" );
	OnSuccessDownLoadPlayerImage4.BindUFunction( this, "_OnSuccessDownLoadPlayerImage4" );
	OnFailDownLoadPlayerImage4.BindUFunction( this, "_OnFailDownLoadPlayerImage4" );

	ButtonDelegate_Clicked( this, C_Btn_More, &UBWidget_MainRankingSlot::_OnClick_MoreBtn );
}

void UBWidget_MainRankingSlot::OnClose()
{
	Super::OnClose(); 
}

void UBWidget_MainRankingSlot::SetData( const E_RANKING_TYPE rankingType )
{
	_RankType = rankingType;

	C_Btn_More->SetVisibility( ESlateVisibility::Visible );
	C_WS_Medal1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	C_WS_Medal2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	C_WS_Medal3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );

	C_Grid_Rank4->SetVisibility( ESlateVisibility::Collapsed );

	switch (rankingType)
	{
	case E_RANKING_TYPE::E_RANKING_TYPE_GOAL:
		_SetDataGoal();
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_ASSIST:
		_SetDataAssist();
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_POINT:
		_SetDataPoint();
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_ATTENDANCE:
		_SetDataAttendance();
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_YEAR_MVP:
		_SetDataYearMvp();
		C_Btn_More->SetVisibility( ESlateVisibility::Hidden );
		C_WS_Medal1->SetVisibility( ESlateVisibility::Collapsed );
		C_WS_Medal2->SetVisibility( ESlateVisibility::Collapsed );
		C_WS_Medal3->SetVisibility( ESlateVisibility::Collapsed );
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_YEAR_KING:
		_SetDataYearKing();
		C_Btn_More->SetVisibility( ESlateVisibility::Hidden );
		C_Grid_Rank4->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_Medal1->SetVisibility( ESlateVisibility::Collapsed );
		C_WS_Medal2->SetVisibility( ESlateVisibility::Collapsed );
		C_WS_Medal3->SetVisibility( ESlateVisibility::Collapsed );
		C_WS_Medal4->SetVisibility( ESlateVisibility::Collapsed );
		break;
	default:
		break;
	}
}

void UBWidget_MainRankingSlot::_OnSuccessDownLoadPlayerImage1( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName1, texturl );
		if( C_Img_Person1 != nullptr )
		{
			C_Img_Person1->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MainRankingSlot::_OnFailDownLoadPlayerImage1( UTexture2DDynamic* texturl )
{

}

void UBWidget_MainRankingSlot::_OnSuccessDownLoadPlayerImage2( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName2, texturl );
		if( C_Img_Person2 != nullptr )
		{
			C_Img_Person2->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MainRankingSlot::_OnFailDownLoadPlayerImage2( UTexture2DDynamic* texturl )
{

}

void UBWidget_MainRankingSlot::_OnSuccessDownLoadPlayerImage3( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName3, texturl );
		if( C_Img_Person3 != nullptr )
		{
			C_Img_Person3->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MainRankingSlot::_OnFailDownLoadPlayerImage3( UTexture2DDynamic* texturl )
{

}

void UBWidget_MainRankingSlot::_OnSuccessDownLoadPlayerImage4( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName4, texturl );
		if( C_Img_Person4 != nullptr )
		{
			C_Img_Person4->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MainRankingSlot::_OnFailDownLoadPlayerImage4( UTexture2DDynamic* texturl )
{

}

void UBWidget_MainRankingSlot::_OnClick_MoreBtn()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_RANKING_MAIN );
		UBWidget_RankingMain* rankingMainWidget = B_HUD->GetWidgetInViewport<UBWidget_RankingMain>( EBUIName::Ranking );
		if( rankingMainWidget != nullptr )
		{
			switch (_RankType)
			{
			case E_RANKING_TYPE::E_RANKING_TYPE_GOAL:
				rankingMainWidget->ChangeSortType( E_SORT_TYPE::E_SORT_TYPE_GOAL );
				break;
			case E_RANKING_TYPE::E_RANKING_TYPE_ASSIST:
				rankingMainWidget->ChangeSortType( E_SORT_TYPE::E_SORT_TYPE_ASSIST );
				break;
			case E_RANKING_TYPE::E_RANKING_TYPE_POINT:
				rankingMainWidget->ChangeSortType( E_SORT_TYPE::E_SORT_TYPE_POINT );
				break;
			case E_RANKING_TYPE::E_RANKING_TYPE_ATTENDANCE:
				rankingMainWidget->ChangeSortType( E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE );
				break;
			default:
				break;
			}
		}
	}
}

void UBWidget_MainRankingSlot::_SetDataAttendance()
{
	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [nowYear]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
	{
		if( A.GetGamesNum( nowYear ) >= B.GetGamesNum( nowYear ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	} );

	TArray<int32> rankIndex;
	if( playerDataList.Num() > SHOW_RANK_NUM )
	{
		if( playerDataList[0].GetGamesNum( nowYear ) > playerDataList[1].GetGamesNum( nowYear ) )
		{
			rankIndex.Add( 1 );
			if( playerDataList[1].GetGamesNum( nowYear ) > playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}
			else if( playerDataList[1].GetGamesNum( nowYear ) == playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}

		}
		else if( playerDataList[0].GetGamesNum( nowYear ) == playerDataList[1].GetGamesNum( nowYear ) )
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 1 );
			if( playerDataList[1].GetGamesNum( nowYear ) > playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 3 );
			}
			else if( playerDataList[1].GetGamesNum( nowYear ) == playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 1 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}
		else
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 2 );
			if( playerDataList[1].GetGamesNum( nowYear ) > playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 3 );
			}
			else if( playerDataList[1].GetGamesNum( nowYear ) == playerDataList[2].GetGamesNum( nowYear ) )
			{
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}
	}

	C_Txt_Title->SetText( GET_BTEXT( 30 ) );

	if( playerDataList.Num() > SHOW_RANK_NUM )
	{
		// Player 1
		C_Txt_Name1->SetText( FText::FromString( playerDataList[0].PlayerName ) );
		C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[0].TeamName ) ) );
		C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[0].TeamName ) );
		C_Txt_Value1->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[0].GetGamesNum( nowYear ) ) ) );
		C_WS_Medal1->SetActiveWidgetIndex( rankIndex[0] - 1 );
		_PlayerName1 = playerDataList[0].PlayerName;
		UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerDataList[0].PlayerName );
		if( playerImg1 != nullptr )
		{
			if( C_Img_Person1 != nullptr )
			{
				C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
			}
		}
		else
		{
			const FString picturlURL1 = playerDataList[0].PictureURL;
			if( picturlURL1.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
			}
		}

		// Player 2
		C_Txt_Name2->SetText( FText::FromString( playerDataList[1].PlayerName ) );
		C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[1].TeamName ) ) );
		C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[1].TeamName ) );
		C_Txt_Value2->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[1].GetGamesNum( nowYear ) ) ) );
		C_WS_Medal2->SetActiveWidgetIndex( rankIndex[1] - 1 );
		_PlayerName2 = playerDataList[1].PlayerName;
		UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerDataList[1].PlayerName );
		if( playerImg2 != nullptr )
		{
			if( C_Img_Person2 != nullptr )
			{
				C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
			}
		}
		else
		{
			const FString picturlURL2 = playerDataList[1].PictureURL;
			if( picturlURL2.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
			}
		}

		// Player 3
		C_Txt_Name3->SetText( FText::FromString( playerDataList[2].PlayerName ) );
		C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[2].TeamName ) ) );
		C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[2].TeamName ) );
		C_Txt_Value3->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[2].GetGamesNum( nowYear ) ) ) );
		C_WS_Medal3->SetActiveWidgetIndex( rankIndex[2] - 1 );
		_PlayerName3 = playerDataList[2].PlayerName;
		UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerDataList[2].PlayerName );
		if( playerImg3 != nullptr )
		{
			if( C_Img_Person3 != nullptr )
			{
				C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
			}
		}
		else
		{
			const FString picturlURL3 = playerDataList[2].PictureURL;
			if( picturlURL3.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
			}
		}
	}
}

void UBWidget_MainRankingSlot::_SetDataGoal()
{
	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [nowYear, tmpFilter]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
	{
		if( A.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true) > B.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
		{
			return true;
		}
		else if( A.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == B.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
		{
			return A.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) <= B.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		}
		else
		{
			return false;
		}
	} );

	TArray<int32> rankIndex;
	if ( playerDataList.Num() > SHOW_RANK_NUM )
	{
		int32 playerGoal_0 = playerDataList[0].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGoal_1 = playerDataList[1].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGoal_2 = playerDataList[2].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_0 = playerDataList[0].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_1 = playerDataList[1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_2 = playerDataList[2].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		if( playerGoal_0 > playerGoal_1 )
		{
			rankIndex.Add( 1 );
			if( playerGoal_1 > playerGoal_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}

		}
		else if( playerGame_0 == playerGame_1 )
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 1 );
			if( playerGoal_1 > playerGoal_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 1 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}
		else
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 2 );
			if( playerGoal_1 > playerGoal_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}

		// Player 1
		C_Txt_Name1->SetText( FText::FromString( playerDataList[0].PlayerName ) );
		C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[0].TeamName ) ) );
		C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[0].TeamName ) );
		C_Txt_Value1->SetText( FText::Format( GET_BTEXT( 17 ), FText::AsNumber( playerGame_0 ), FText::AsNumber( playerGoal_0 ) ) );
		C_WS_Medal1->SetActiveWidgetIndex( rankIndex[0] - 1 );
		_PlayerName1 = playerDataList[0].PlayerName;
		UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerDataList[0].PlayerName );
		if( playerImg1 != nullptr )
		{
			if( C_Img_Person1 != nullptr )
			{
				C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
			}
		}
		else
		{
			const FString picturlURL1 = playerDataList[0].PictureURL;
			if( picturlURL1.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
			}
		}

		// Player 2
		C_Txt_Name2->SetText( FText::FromString( playerDataList[1].PlayerName ) );
		C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[1].TeamName ) ) );
		C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[1].TeamName ) );
		C_Txt_Value2->SetText( FText::Format( GET_BTEXT( 17 ), FText::AsNumber( playerGame_1 ), FText::AsNumber( playerGoal_1 ) ) );
		C_WS_Medal2->SetActiveWidgetIndex( rankIndex[1] - 1 );
		_PlayerName2 = playerDataList[1].PlayerName;
		UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerDataList[1].PlayerName );
		if( playerImg2 != nullptr )
		{
			if( C_Img_Person2 != nullptr )
			{
				C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
			}
		}
		else
		{
			const FString picturlURL2 = playerDataList[1].PictureURL;
			if( picturlURL2.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
			}
		}

		// Player 3
		C_Txt_Name3->SetText( FText::FromString( playerDataList[2].PlayerName ) );
		C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[2].TeamName ) ) );
		C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[2].TeamName ) );
		C_Txt_Value3->SetText( FText::Format( GET_BTEXT( 17 ), FText::AsNumber( playerGame_2 ), FText::AsNumber( playerGoal_2 ) ) );
		C_WS_Medal3->SetActiveWidgetIndex( rankIndex[2] - 1 );
		_PlayerName3 = playerDataList[2].PlayerName;
		UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerDataList[2].PlayerName );
		if( playerImg3 != nullptr )
		{
			if( C_Img_Person3 != nullptr )
			{
				C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
			}
		}
		else
		{
			const FString picturlURL3 = playerDataList[2].PictureURL;
			if( picturlURL3.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
			}
		}
	}

	C_Txt_Title->SetText( GET_BTEXT( 14 ) );
}

void UBWidget_MainRankingSlot::_SetDataAssist()
{
	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [nowYear, tmpFilter]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
						 {
							 if( A.GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) > B.GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
							 {
								 return true;
							 }
							 else if( A.GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == B.GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
							 {
								 return A.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) <= B.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
							 }
							 else
							 {
								 return false;
							 }
						 } );

	TArray<int32> rankIndex;
	if( playerDataList.Num() > SHOW_RANK_NUM )
	{
		int32 playerAssist_0 = playerDataList[0].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerAssist_1 = playerDataList[1].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerAssist_2 = playerDataList[2].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_0 = playerDataList[0].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_1 = playerDataList[1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_2 = playerDataList[2].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );

		if( playerAssist_0 > playerAssist_1 )
		{
			rankIndex.Add( 1 );
			if( playerAssist_1 > playerAssist_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}

		}
		else if( playerGame_0 == playerGame_1 )
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 1 );
			if( playerAssist_1 > playerAssist_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 1 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}
		else
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 2 );
			if( playerAssist_1 > playerAssist_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}

		// Player 1
		C_Txt_Name1->SetText( FText::FromString( playerDataList[0].PlayerName ) );
		C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[0].TeamName ) ) );
		C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[0].TeamName ) );
		C_Txt_Value1->SetText( FText::Format( GET_BTEXT( 18 ), FText::AsNumber( playerGame_0 ), FText::AsNumber( playerAssist_0 ) ) );
		C_WS_Medal1->SetActiveWidgetIndex( rankIndex[0] - 1 );
		_PlayerName1 = playerDataList[0].PlayerName;
		UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerDataList[0].PlayerName );
		if( playerImg1 != nullptr )
		{
			if( C_Img_Person1 != nullptr )
			{
				C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
			}
		}
		else
		{
			const FString picturlURL1 = playerDataList[0].PictureURL;
			if( picturlURL1.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
			}
		}

		// Player 2
		C_Txt_Name2->SetText( FText::FromString( playerDataList[1].PlayerName ) );
		C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[1].TeamName ) ) );
		C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[1].TeamName ) );
		C_Txt_Value2->SetText( FText::Format( GET_BTEXT( 18 ), FText::AsNumber( playerGame_1 ), FText::AsNumber( playerAssist_1 ) ) );
		C_WS_Medal2->SetActiveWidgetIndex( rankIndex[1] - 1 );
		_PlayerName2 = playerDataList[1].PlayerName;
		UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerDataList[1].PlayerName );
		if( playerImg2 != nullptr )
		{
			if( C_Img_Person2 != nullptr )
			{
				C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
			}
		}
		else
		{
			const FString picturlURL2 = playerDataList[1].PictureURL;
			if( picturlURL2.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
			}
		}

		// Player 3
		C_Txt_Name3->SetText( FText::FromString( playerDataList[2].PlayerName ) );
		C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[2].TeamName ) ) );
		C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[2].TeamName ) );
		C_Txt_Value3->SetText( FText::Format( GET_BTEXT( 18 ), FText::AsNumber( playerGame_2 ), FText::AsNumber( playerAssist_2 ) ) );
		C_WS_Medal3->SetActiveWidgetIndex( rankIndex[2] - 1 );
		_PlayerName3 = playerDataList[2].PlayerName;
		UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerDataList[2].PlayerName );
		if( playerImg3 != nullptr )
		{
			if( C_Img_Person3 != nullptr )
			{
				C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
			}
		}
		else
		{
			const FString picturlURL3 = playerDataList[2].PictureURL;
			if( picturlURL3.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
			}
		}
	}

	C_Txt_Title->SetText( GET_BTEXT( 15 ) );
}

void UBWidget_MainRankingSlot::_SetDataPoint()
{
	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [nowYear, tmpFilter]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
						 {
							 if( A.GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) > B.GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
							 {
								 return true;
							 }
							 else if( A.GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == B.GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
							 {
								 return A.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) <= B.GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
							 }
							 else
							 {
								 return false;
							 }
						 } );

	TArray<int32> rankIndex;
	if( playerDataList.Num() > SHOW_RANK_NUM )
	{
		int32 playerPoint_0 = playerDataList[0].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerPoint_1 = playerDataList[1].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerPoint_2 = playerDataList[2].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_0 = playerDataList[0].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_1 = playerDataList[1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
		int32 playerGame_2 = playerDataList[2].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );

		if( playerPoint_0 > playerPoint_1 )
		{
			rankIndex.Add( 1 );
			if( playerPoint_1 > playerPoint_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 2 );
				rankIndex.Add( 3 );
			}

		}
		else if( playerGame_0 == playerGame_1 )
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 1 );
			if( playerPoint_1 > playerPoint_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 1 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}
		else
		{
			rankIndex.Add( 1 );
			rankIndex.Add( 2 );
			if( playerPoint_1 > playerPoint_2 )
			{
				rankIndex.Add( 3 );
			}
			else if( playerGame_1 == playerGame_2 )
			{
				rankIndex.Add( 2 );
			}
			else
			{
				rankIndex.Add( 3 );
			}
		}

		// Player 1
		C_Txt_Name1->SetText( FText::FromString( playerDataList[0].PlayerName ) );
		C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[0].TeamName ) ) );
		C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[0].TeamName ) );
		C_Txt_Value1->SetText( FText::Format( GET_BTEXT( 19 ), FText::AsNumber( playerGame_0 ), FText::AsNumber( playerPoint_0 ) ) );
		C_WS_Medal1->SetActiveWidgetIndex( rankIndex[0] - 1 );
		_PlayerName1 = playerDataList[0].PlayerName;
		UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerDataList[0].PlayerName );
		if( playerImg1 != nullptr )
		{
			if( C_Img_Person1 != nullptr )
			{
				C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
			}
		}
		else
		{
			const FString picturlURL1 = playerDataList[0].PictureURL;
			if( picturlURL1.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
			}
		}

		// Player 2
		C_Txt_Name2->SetText( FText::FromString( playerDataList[1].PlayerName ) );
		C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[1].TeamName ) ) );
		C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[1].TeamName ) );
		C_Txt_Value2->SetText( FText::Format( GET_BTEXT( 19 ), FText::AsNumber( playerGame_1 ), FText::AsNumber( playerPoint_1 ) ) );
		C_WS_Medal2->SetActiveWidgetIndex( rankIndex[1] - 1 );
		_PlayerName2 = playerDataList[1].PlayerName;
		UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerDataList[1].PlayerName );
		if( playerImg2 != nullptr )
		{
			if( C_Img_Person2 != nullptr )
			{
				C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
			}
		}
		else
		{
			const FString picturlURL2 = playerDataList[1].PictureURL;
			if( picturlURL2.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
			}
		}

		// Player 3
		C_Txt_Name3->SetText( FText::FromString( playerDataList[2].PlayerName ) );
		C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[2].TeamName ) ) );
		C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[2].TeamName ) );
		C_Txt_Value3->SetText( FText::Format( GET_BTEXT( 19 ), FText::AsNumber( playerGame_2 ), FText::AsNumber( playerPoint_2 ) ) );
		C_WS_Medal3->SetActiveWidgetIndex( rankIndex[2] - 1 );
		_PlayerName3 = playerDataList[2].PlayerName;
		UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerDataList[2].PlayerName );
		if( playerImg3 != nullptr )
		{
			if( C_Img_Person3 != nullptr )
			{
				C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
			}
		}
		else
		{
			const FString picturlURL3 = playerDataList[2].PictureURL;
			if( picturlURL3.IsEmpty() == false )
			{
				DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
			}
		}
	}

	C_Txt_Title->SetText( GET_BTEXT( 16 ) );
}

void UBWidget_MainRankingSlot::_SetDataYearMvp()
{
	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() - 1);
	TArray<FST_YEAR_MVP_DATA> MvpDataList = UFBM_SaveGame::Get().GetYearMvpData_DB();

	C_Txt_Title->SetText( FText::Format( GET_BTEXT( 33 ), FText::FromString( nowYear ) ) );
	int32 CurYearIndex = -1;
	for (int mvpIndex = 0; mvpIndex < MvpDataList.Num(); ++mvpIndex)
	{
		if ( nowYear == MvpDataList[mvpIndex].Year )
		{
			CurYearIndex = mvpIndex;
			break;
		}
	}

	if (CurYearIndex != -1)
	{
		this->SetVisibility( ESlateVisibility::Visible );
		// Player 1
		if ( MvpDataList[CurYearIndex].Name.Num() > 0)
		{
			const FST_PLAYER_DATA* playerData = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( MvpDataList[CurYearIndex].Name[0] );
			if ( playerData )
			{
				C_Txt_Name1->SetText( FText::FromString( MvpDataList[CurYearIndex].Name[0] ) );
				C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
				C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
				C_Txt_Value1->SetVisibility( ESlateVisibility::Collapsed );
				C_WS_Medal1->SetActiveWidgetIndex( 0 );
				_PlayerName1 = playerData->PlayerName;
				UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerData->PlayerName );
				if( playerImg1 != nullptr )
				{
					if( C_Img_Person1 != nullptr )
					{
						C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
					}
				}
				else
				{
					const FString picturlURL1 = playerData->PictureURL;
					if( picturlURL1.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
					}
				}
			}
		}

		// Player 2
		if( MvpDataList[CurYearIndex].Name.Num() > 1 )
		{
			const FST_PLAYER_DATA* playerData2 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( MvpDataList[CurYearIndex].Name[1] );
			if( playerData2 )
			{
				C_Txt_Name2->SetText( FText::FromString( MvpDataList[CurYearIndex].Name[1] ) );
				C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData2->TeamName ) ) );
				C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData2->TeamName ) );
				C_Txt_Value2->SetVisibility( ESlateVisibility::Collapsed );
				C_WS_Medal2->SetActiveWidgetIndex( 1 );
				_PlayerName2 = playerData2->PlayerName;
				UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerData2->PlayerName );
				if( playerImg2 != nullptr )
				{
					if( C_Img_Person2 != nullptr )
					{
						C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
					}
				}
				else
				{
					const FString picturlURL2 = playerData2->PictureURL;
					if( picturlURL2.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
					}
				}
			}
		}

		// Player 3
		if( MvpDataList[CurYearIndex].Name.Num() > 2 )
		{
			const FST_PLAYER_DATA* playerData3 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( MvpDataList[CurYearIndex].Name[2] );
			if( playerData3 )
			{
				C_Txt_Name3->SetText( FText::FromString( MvpDataList[CurYearIndex].Name[2] ) );
				C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData3->TeamName ) ) );
				C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData3->TeamName ) );
				C_Txt_Value3->SetVisibility( ESlateVisibility::Collapsed );
				C_WS_Medal3->SetActiveWidgetIndex( 2 );
				_PlayerName3 = playerData3->PlayerName;
				UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerData3->PlayerName );
				if( playerImg3 != nullptr )
				{
					if( C_Img_Person3 != nullptr )
					{
						C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
					}
				}
				else
				{
					const FString picturlURL3 = playerData3->PictureURL;
					if( picturlURL3.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
					}
				}
			}
		}

		if( MvpDataList[CurYearIndex].Name.Num() == 2 )
		{
			C_Grid_Rank3->SetVisibility( ESlateVisibility::Collapsed );
		}
		else if( MvpDataList[CurYearIndex].Name.Num() == 1 )
		{
			C_Grid_Rank2->SetVisibility( ESlateVisibility::Collapsed );
			C_Grid_Rank3->SetVisibility( ESlateVisibility::Collapsed );
		}
		
	}
	else
	{
		this->SetVisibility( ESlateVisibility::Collapsed );
	}
}

void UBWidget_MainRankingSlot::_SetDataYearKing()
{
	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() - 1 );
	TArray<FST_YEAR_KING_DATA> KingDataList = UFBM_SaveGame::Get().GetYearKingData_DB();

	C_Txt_Title->SetText( FText::Format( GET_BTEXT( 34 ), FText::FromString( nowYear ) ) );
	int32 CurYearIndex = -1;
	for( int kingIndex = 0; kingIndex < KingDataList.Num(); ++kingIndex )
	{
		if( nowYear == KingDataList[kingIndex].Year )
		{
			CurYearIndex = kingIndex;
			break;
		}
	}

	if( CurYearIndex != -1 )
	{
		this->SetVisibility( ESlateVisibility::Visible );

		// 득점왕
		if( !KingDataList[CurYearIndex].GoalKing.IsEmpty() )
		{
			const FST_PLAYER_DATA* playerData = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( KingDataList[CurYearIndex].GoalKing );
			if( playerData )
			{
				C_Txt_Name1->SetText( FText::FromString( KingDataList[CurYearIndex].GoalKing ) );
				C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
				C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
				C_Txt_Value1->SetText( GET_BTEXT( 35 ) );
				C_Txt_Value1->SetColorAndOpacity( Color_BootsCompare_Red );
				C_WS_Medal1->SetVisibility(ESlateVisibility::Hidden);
				_PlayerName1 = playerData->PlayerName;
				UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( playerData->PlayerName );
				if( playerImg1 != nullptr )
				{
					if( C_Img_Person1 != nullptr )
					{
						C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
					}
				}
				else
				{
					const FString picturlURL1 = playerData->PictureURL;
					if( picturlURL1.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
					}
				}
			}
		}

		// 도움왕
		if( !KingDataList[CurYearIndex].AssistKing.IsEmpty() )
		{
			const FST_PLAYER_DATA* playerData2 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( KingDataList[CurYearIndex].AssistKing );
			if( playerData2 )
			{
				C_Txt_Name2->SetText( FText::FromString( KingDataList[CurYearIndex].AssistKing) );
				C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData2->TeamName ) ) );
				C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData2->TeamName ) );
				C_Txt_Value2->SetText( GET_BTEXT( 36 ) );
				C_Txt_Value2->SetColorAndOpacity( Color_BootsCompare_Red );
				C_WS_Medal2->SetVisibility( ESlateVisibility::Hidden );
				_PlayerName2 = playerData2->PlayerName;
				UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( playerData2->PlayerName );
				if( playerImg2 != nullptr )
				{
					if( C_Img_Person2 != nullptr )
					{
						C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
					}
				}
				else
				{
					const FString picturlURL2 = playerData2->PictureURL;
					if( picturlURL2.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
					}
				}
			}
		}

		// 수비왕
		if( !KingDataList[CurYearIndex].DefenceKing.IsEmpty() )
		{
			const FST_PLAYER_DATA* playerData3 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( KingDataList[CurYearIndex].DefenceKing );
			if( playerData3 )
			{
				C_Txt_Name3->SetText( FText::FromString( KingDataList[CurYearIndex].DefenceKing ) );
				C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData3->TeamName ) ) );
				C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData3->TeamName ) );
				C_Txt_Value3->SetText( GET_BTEXT( 59 ) );
				C_Txt_Value3->SetColorAndOpacity( Color_BootsCompare_Red );
				C_WS_Medal3->SetVisibility( ESlateVisibility::Hidden );
				_PlayerName3 = playerData3->PlayerName;
				UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( playerData3->PlayerName );
				if( playerImg3 != nullptr )
				{
					if( C_Img_Person3 != nullptr )
					{
						C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
					}
				}
				else
				{
					const FString picturlURL3 = playerData3->PictureURL;
					if( picturlURL3.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
					}
				}
			}
		}

		// 출석왕
		if( !KingDataList[CurYearIndex].AttendanceKing.IsEmpty())
		{
			const FST_PLAYER_DATA* playerData4 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( KingDataList[CurYearIndex].AttendanceKing );
			if( playerData4 )
			{
				C_Txt_Name4->SetText( FText::FromString( KingDataList[CurYearIndex].AttendanceKing ) );
				C_Txt_Team4->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData4->TeamName ) ) );
				C_Txt_Team4->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData4->TeamName ) );
				C_Txt_Value4->SetText( GET_BTEXT( 38 ) );
				C_Txt_Value4->SetColorAndOpacity( Color_BootsCompare_Red );
				C_WS_Medal4->SetVisibility( ESlateVisibility::Hidden );
				_PlayerName4 = playerData4->PlayerName;
				UTexture2DDynamic* playerImg4 = GInst->GetDownLoadPlayerImage( playerData4->PlayerName );
				if( playerImg4 != nullptr )
				{
					if( C_Img_Person4 != nullptr )
					{
						C_Img_Person4->SetBrushFromTextureDynamic( playerImg4, false );
					}
				}
				else
				{
					const FString picturlURL4 = playerData4->PictureURL;
					if( picturlURL4.IsEmpty() == false )
					{
						DownLoadTexture_URL( picturlURL4, OnSuccessDownLoadPlayerImage4, OnFailDownLoadPlayerImage4 );
					}
				}
			}
		}
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}
