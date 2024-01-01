#include "BWidget_PlayerMain.h"
#include "BWidget_PlayerSlot.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "Bigtamin.h"

#define SCROLL_ITEM_NUM 30
#define SCROLL_ROW_NUM 3.f

void UBWidget_PlayerMain::Init()
{
	Super::Init();

	BP_Top_PlayerMain_UMG->Init();
	BP_Top_PlayerMain_UMG->ChangeTopMode( E_MODE::E_MODE_PLAYER_MAIN );

	_Ani_ResultMainOpen = GetWidgetAnimation( _Ani_ResultMainOpenName );
	_Ani_ResultMainClose = GetWidgetAnimation( _Ani_ResultMainCloseName );

	InitPlayerMain();

	GInst->AddBackInput( this );

	PlayResultMainOpenAni( true );
}

void UBWidget_PlayerMain::OnClose()
{
	Super::OnClose();
}

void UBWidget_PlayerMain::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
{
	Super::NativeTick( MyGeometry, InDeltaTime );

	// 스크롤 박스 동적 로딩
	if( _UpdateScrollTime > 0.5f )
	{
		if( _CurScrollInex < _MaxScrollInex && C_SB_Item->IsNeeded() && C_SB_Item->IsScrolling() )
		{
			//if( FMath::IsNearlyZero( C_SB_Item->DistanceFromBottom() ))
			if( C_SB_Item->DistanceFromBottom() < 0.0000001f )
			{
				_UpdateScrollItem();
				_UpdateScrollTime = 0.f;
			}
		}
	}

	_UpdateScrollTime += InDeltaTime;
}

void UBWidget_PlayerMain::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_ResultMainCloseName )
		{
			CloseUI();
		}
	}
}

void UBWidget_PlayerMain::InitPlayerMain()
{
	_MainFilterItems.Empty();
	C_SB_PlayerType->ClearChildren();
	C_SB_PlayerType->ScrollToStart();

	// 주황팀 타입
	UBWidget_EquipFilterItem* teamAWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( teamAWidget != nullptr )
	{
		teamAWidget->OwnerPannel = this;
		teamAWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A, 20 );
		if( teamAWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			teamAWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_PlayerMain::OnClickPlayerMainTab );
		}
		C_SB_PlayerType->AddChild( teamAWidget );
		_MainFilterItems.Add( teamAWidget );
	}

	// 형광팀 타입
	UBWidget_EquipFilterItem* teamBWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( teamBWidget != nullptr )
	{
		teamBWidget->OwnerPannel = this;
		teamBWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B, 21 );
		if( teamBWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			teamBWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_PlayerMain::OnClickPlayerMainTab );
		}
		C_SB_PlayerType->AddChild( teamBWidget );
		_MainFilterItems.Add( teamBWidget );
	}

	// 코치진 타입
	UBWidget_EquipFilterItem* coachWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( coachWidget != nullptr )
	{
		coachWidget->OwnerPannel = this;
		coachWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_COACH, 52 );
		if( coachWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			coachWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_PlayerMain::OnClickPlayerMainTab );
		}
		C_SB_PlayerType->AddChild( coachWidget );
		_MainFilterItems.Add( coachWidget );
	}

	// 프런트 타입
	UBWidget_EquipFilterItem* frontWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( frontWidget != nullptr )
	{
		frontWidget->OwnerPannel = this;
		frontWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_FRONT, 51 );
		if( frontWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			frontWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_PlayerMain::OnClickPlayerMainTab );
		}
		C_SB_PlayerType->AddChild( frontWidget );
		_MainFilterItems.Add( frontWidget );
	}

	OnClickPlayerMainTab( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A, true );
}

void UBWidget_PlayerMain::SetSubResultItem( const E_FILTER_ITEM_TYPE mainFilterType )
{
	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();
	_PlaterNameData.Empty();

	FST_STAFF_DATA StaffDataList = UFBM_SaveGame::Get().GetStaffData_DB();
	TArray<FST_PLAYER_DATA> playerDataList = UFBM_SaveGame::Get().GetPlayerData_DB();
	for( auto& playerData : playerDataList )
	{
		if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A )
		{
			if( UFBM_SaveGame::Get().GetDevUtdTeamType( playerData.TeamName ) == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A )
			{
				_PlaterNameData.Add( playerData.PlayerName );
			}
		}
		else if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B )
		{
			if( UFBM_SaveGame::Get().GetDevUtdTeamType( playerData.TeamName ) == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B )
			{
				_PlaterNameData.Add( playerData.PlayerName );
			}
		}
		else if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_COACH )
		{
			if( playerData.PlayerName == StaffDataList.HeadCoach )
			{
				_PlaterNameData.Add( FText::Format( GET_BTEXT( 53 ), FText::FromString( playerData.PlayerName ) ).ToString() );
			}
			else if (playerData.PlayerName == StaffDataList.SecondCoach || playerData.PlayerName == StaffDataList.ThirdCoach || 
					  playerData.PlayerName == StaffDataList.FourthCoach )
			{
				_PlaterNameData.Add( FText::Format( GET_BTEXT( 54 ), FText::FromString( playerData.PlayerName ) ).ToString() );
			}
		}
		else if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_FRONT )
		{
			if( playerData.PlayerName == StaffDataList.Owner )
			{
				_PlaterNameData.Add( FText::Format( GET_BTEXT( 55 ), FText::FromString( playerData.PlayerName ) ).ToString() );
			}
			else if( playerData.PlayerName == StaffDataList.GeneralManager )
			{
				_PlaterNameData.Add( FText::Format( GET_BTEXT( 56 ), FText::FromString( playerData.PlayerName ) ).ToString() );
			}
		}
	}

	_PlaterNameData.Sort( []( const FString& A, const FString& B )
						  {
							  return A < B;
						  } );

	_CurScrollInex = 0;
	_MaxScrollInex = FMath::CeilToInt(_PlaterNameData.Num() / SCROLL_ROW_NUM );
	_UpdateScrollItem();
}

void UBWidget_PlayerMain::PlayResultMainOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_ResultMainOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultMainOpen ) )
			{
				StopAnimation( _Ani_ResultMainOpen );
			}

			PlayAnimation( _Ani_ResultMainOpen );
		}
	}
	else
	{
		if( _Ani_ResultMainClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultMainClose ) )
			{
				StopAnimation( _Ani_ResultMainClose );
			}

			PlayAnimation( _Ani_ResultMainClose );
		}
	}
}

void UBWidget_PlayerMain::OnClickPlayerMainTab( const E_FILTER_ITEM_TYPE mainTabType, bool isForce /*= true */ )
{
	if( isForce == false && _MainFilterType == mainTabType )
	{
		return;
	}

	_MainFilterType = mainTabType;

	switch( mainTabType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 3 ) )
		{
			_MainFilterItems[3]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 3 ) )
		{
			_MainFilterItems[3]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_COACH:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 3 ) )
		{
			_MainFilterItems[3]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_FRONT:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 2 ) )
		{
			_MainFilterItems[2]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 3 ) )
		{
			_MainFilterItems[3]->SelectEquipFilterItem( true );
		}
		break;
	}

	SetSubResultItem( mainTabType );
}

bool UBWidget_PlayerMain::_OnBackInput()
{
	Super::_OnBackInput();
	PlayResultMainOpenAni( false );
	return true;
}

void UBWidget_PlayerMain::_UpdateScrollItem()
{
	int32 startIndex = _CurScrollInex;
	int32 endIndex = FMath::Min( _MaxScrollInex, startIndex + SCROLL_ITEM_NUM );
	for( int32 playerIndex = startIndex; playerIndex < endIndex; ++playerIndex )
	{
		UBWidget_PlayerSlot* playerSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_PlayerSlot>( EDynamicWidgetParts::PlayerSlot );
		if( playerSlotWidget != nullptr )
		{
			TArray<FString> playDatas;
			int32 startNameIndex = playerIndex * SCROLL_ROW_NUM;
			for( int32 nameIndex = startNameIndex; nameIndex < startNameIndex + 3 && nameIndex < _PlaterNameData.Num(); ++nameIndex )
			{
				playDatas.Add( _PlaterNameData[nameIndex] );
			}
			playerSlotWidget->OwnerPannel = this;
			playerSlotWidget->SetData( playDatas );
			C_SB_Item->AddChild( playerSlotWidget );
			_CurScrollInex++;
		}
	}
}