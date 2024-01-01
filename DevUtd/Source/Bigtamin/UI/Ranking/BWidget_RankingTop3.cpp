#include "BWidget_RankingTop3.h"

void UBWidget_RankingTop3::Init()
{
	Super::Init();
}

void UBWidget_RankingTop3::OnClose()
{
	Super::OnClose();
}

void UBWidget_RankingTop3::SetData( const E_RANKING_TYPE rankingType, FString nowYear )
{
	_NowYear = nowYear;

	switch( rankingType )
	{
	case E_RANKING_TYPE::E_RANKING_TYPE_GOAL:
		_SetDataGoal( nowYear );
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_ASSIST:
		_SetDataAssist( nowYear );
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_POINT:
		_SetDataPoint( nowYear );
		break;
	case E_RANKING_TYPE::E_RANKING_TYPE_ATTENDANCE:
		_SetDataGame( nowYear );
		break;
	default:
		break;
	}
}

void UBWidget_RankingTop3::_SetDataGoal( FString nowYear )
{
	C_Txt_Top3_Title->SetText( GET_BTEXT( 14 ) );
	
	UTexture2D* textureMedalGold = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_GOLD ) );
	UTexture2D* textureMedalSilver = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_SILVER ) );
	UTexture2D* textureMedalBronze = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_BRONZE ) );
	if( textureMedalGold == nullptr || textureMedalSilver == nullptr || textureMedalBronze == nullptr )
	{
		return;
	}

	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	playerDataList.Sort( [nowYear, tmpFilter]( const FST_PLAYER_DATA& A, const FST_PLAYER_DATA& B )
	{
		if( A.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) > B.GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
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
	for( int32 index = 0; index < playerDataList.Num(); ++index )
	{
		if (index == 0)
		{
			C_Txt_Name1->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val1->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( playerDataList[index].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			C_Img_Medal1->SetBrushFromTexture( textureMedalGold, false );
			rankIndex.Add(1);
		}
		else if (index == 1)
		{
			C_Txt_Name2->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val2->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( playerDataList[index].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );

			if( playerDataList[index].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalGold, false );
				rankIndex.Add( 1 );
			}
			else
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalSilver, false );
				rankIndex.Add( 2 );
			}
		}
		else if( index == 2 )
		{
			C_Txt_Name3->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val3->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( playerDataList[index].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			if( playerDataList[index].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGoalNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal3->SetBrushFromTexture(rankIndex[index - 1] == 1 ? textureMedalGold : textureMedalSilver);
			}
			else
			{
				C_Img_Medal3->SetBrushFromTexture( textureMedalBronze, false );
			}
		}
	}
}

void UBWidget_RankingTop3::_SetDataAssist( FString nowYear )
{
	C_Txt_Top3_Title->SetText( GET_BTEXT( 15 ) );

	UTexture2D* textureMedalGold = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_GOLD ) );
	UTexture2D* textureMedalSilver = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_SILVER ) );
	UTexture2D* textureMedalBronze = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_BRONZE ) );
	if( textureMedalGold == nullptr || textureMedalSilver == nullptr || textureMedalBronze == nullptr )
	{
		return;
	}

	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

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
	for( int32 index = 0; index < playerDataList.Num(); ++index )
	{
		if( index == 0 )
		{
			C_Txt_Name1->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val1->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( playerDataList[index].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			C_Img_Medal1->SetBrushFromTexture( textureMedalGold, false );
			rankIndex.Add( 1 );
		}
		else if( index == 1 )
		{
			C_Txt_Name2->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val2->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( playerDataList[index].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );

			if( playerDataList[index].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalGold, false );
				rankIndex.Add( 1 );
			}
			else
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalSilver, false );
				rankIndex.Add( 2 );
			}
		}
		else if( index == 2 )
		{
			C_Txt_Name3->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val3->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( playerDataList[index].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			if( playerDataList[index].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewAssistNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal3->SetBrushFromTexture( rankIndex[index - 1] == 1 ? textureMedalGold : textureMedalSilver );
			}
			else
			{
				C_Img_Medal3->SetBrushFromTexture( textureMedalBronze, false );
			}
		}
	}
}

void UBWidget_RankingTop3::_SetDataPoint( FString nowYear )
{
	C_Txt_Top3_Title->SetText( GET_BTEXT( 16 ) );

	UTexture2D* textureMedalGold = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_GOLD ) );
	UTexture2D* textureMedalSilver = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_SILVER ) );
	UTexture2D* textureMedalBronze = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_BRONZE ) );
	if( textureMedalGold == nullptr || textureMedalSilver == nullptr || textureMedalBronze == nullptr )
	{
		return;
	}

	FST_RANKING_FILTER_INFO tmpFilter;
	tmpFilter.InitFilterInfo();

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
	for( int32 index = 0; index < playerDataList.Num(); ++index )
	{
		if( index == 0 )
		{
			C_Txt_Name1->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val1->SetText( FText::Format( GET_BTEXT( 24 ), FText::AsNumber( playerDataList[index].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			C_Img_Medal1->SetBrushFromTexture( textureMedalGold, false );
			rankIndex.Add( 1 );
		}
		else if( index == 1 )
		{
			C_Txt_Name2->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val2->SetText( FText::Format( GET_BTEXT( 24 ), FText::AsNumber( playerDataList[index].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );

			if( playerDataList[index].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalGold, false );
				rankIndex.Add( 1 );
			}
			else
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalSilver, false );
				rankIndex.Add( 2 );
			}
		}
		else if( index == 2 )
		{
			C_Txt_Name3->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val3->SetText( FText::Format( GET_BTEXT( 24 ), FText::AsNumber( playerDataList[index].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) ) ) );
			if( playerDataList[index].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewPointNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) &&
				playerDataList[index].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) == playerDataList[index - 1].GetNewGamesNum( nowYear, tmpFilter, E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true ) )
			{
				C_Img_Medal3->SetBrushFromTexture( rankIndex[index - 1] == 1 ? textureMedalGold : textureMedalSilver );
			}
			else
			{
				C_Img_Medal3->SetBrushFromTexture( textureMedalBronze, false );
			}
		}
	}
}

void UBWidget_RankingTop3::_SetDataGame( FString nowYear )
{
	C_Txt_Top3_Title->SetText( GET_BTEXT( 30 ) );

	UTexture2D* textureMedalGold = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_GOLD ) );
	UTexture2D* textureMedalSilver = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_SILVER ) );
	UTexture2D* textureMedalBronze = GetTexture( UFBMUtil::MedalImgPath( E_MEDAL_TYPE::E_MEDAL_TYPE_BRONZE ) );
	if( textureMedalGold == nullptr || textureMedalSilver == nullptr || textureMedalBronze == nullptr )
	{
		return;
	}

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
	for( int32 index = 0; index < playerDataList.Num(); ++index )
	{
		if( index == 0 )
		{
			C_Txt_Name1->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val1->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[index].GetGamesNum( nowYear ) ) ) );
			C_Img_Medal1->SetBrushFromTexture( textureMedalGold, false );
			rankIndex.Add( 1 );
		}
		else if( index == 1 )
		{
			C_Txt_Name2->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val2->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[index].GetGamesNum( nowYear ) ) ) );

			if( playerDataList[index].GetGamesNum( nowYear ) == playerDataList[index - 1].GetGamesNum( nowYear ) )
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalGold, false );
				rankIndex.Add( 1 );
			}
			else
			{
				C_Img_Medal2->SetBrushFromTexture( textureMedalSilver, false );
				rankIndex.Add( 2 );
			}
		}
		else if( index == 2 )
		{
			C_Txt_Name3->SetText( FText::FromString( playerDataList[index].PlayerName ) );
			C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerDataList[index].TeamName ) ) );
			C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerDataList[index].TeamName ) );
			C_Txt_Val3->SetText( FText::Format( GET_BTEXT( 31 ), FText::AsNumber( playerDataList[index].GetGamesNum( nowYear ) ) ) );
			if( playerDataList[index].GetGamesNum( nowYear ) == playerDataList[index - 1].GetGamesNum( nowYear ) )
			{
				C_Img_Medal3->SetBrushFromTexture( rankIndex[index - 1] == 1 ? textureMedalGold : textureMedalSilver );
			}
			else
			{
				C_Img_Medal3->SetBrushFromTexture( textureMedalBronze, false );
			}
		}
	}
}

