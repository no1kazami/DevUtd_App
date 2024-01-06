#include "BWidget_MainSchedule.h"
#include "BWidget_MatchItem.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "UI/BWidget_Top.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"

#define SCROLL_ITEM_NUM 30

void UBWidget_MainSchedule::Init()
{
	Super::Init();

	BP_Top_ScheduleMain_UMG->Init();
	BP_Top_ScheduleMain_UMG->ChangeTopMode( E_MODE::E_MODE_SCHEDULE_MAIN );

	_Ani_ScheduleMainOpen = GetWidgetAnimation( _Ani_ScheduleMainOpenName );
	_Ani_ScheduleMainClose = GetWidgetAnimation( _Ani_ScheduleMainCloseName );

	InitScheduleMain();

	GInst->AddBackInput( this );

	PlayScheduleMainOpenAni( true );
}

void UBWidget_MainSchedule::OnClose()
{
	Super::OnClose();
}

void UBWidget_MainSchedule::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
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

void UBWidget_MainSchedule::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_ScheduleMainCloseName )
		{
			CloseUI();
		}
	}
}

void UBWidget_MainSchedule::InitScheduleMain()
{
	_MainFilterItems.Empty();
	C_SB_ScheduleType->ClearChildren();
	C_SB_ScheduleType->ScrollToStart();

	// 일정 전체 타입
	UBWidget_EquipFilterItem* scheduleAllWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( scheduleAllWidget != nullptr )
	{
		scheduleAllWidget->OwnerPannel = this;
		scheduleAllWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, 6 );
		if( scheduleAllWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			scheduleAllWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainSchedule::OnClickScheduleMainFilter );
		}
		C_SB_ScheduleType->AddChild( scheduleAllWidget );
		_MainFilterItems.Add( scheduleAllWidget );
	}

	// 일정 A-Match 타입
	UBWidget_EquipFilterItem* scheduleAMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( scheduleAMatchWidget != nullptr )
	{
		scheduleAMatchWidget->OwnerPannel = this;
		scheduleAMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH, 7 );
		if( scheduleAMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			scheduleAMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainSchedule::OnClickScheduleMainFilter );
		}
		C_SB_ScheduleType->AddChild( scheduleAMatchWidget );
		_MainFilterItems.Add( scheduleAMatchWidget );
	}

	// 일정 자체전 타입
	UBWidget_EquipFilterItem* scheduleOwnMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( scheduleOwnMatchWidget != nullptr )
	{
		scheduleOwnMatchWidget->OwnerPannel = this;
		scheduleOwnMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH, 8 );
		if( scheduleOwnMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			scheduleOwnMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainSchedule::OnClickScheduleMainFilter );
		}
		C_SB_ScheduleType->AddChild( scheduleOwnMatchWidget );
		_MainFilterItems.Add( scheduleOwnMatchWidget );
	}

	OnClickScheduleMainFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
}

void UBWidget_MainSchedule::SetSubScheduleItem( const E_FILTER_ITEM_TYPE mainFilterType )
{
	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();
	_ArrayMatchData.Empty();

	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	FString nowMonth = FString::Printf( TEXT( "%02d" ), nowDateTime.GetMonth() );
	FString nowDay = FString::Printf( TEXT( "%02d" ), nowDateTime.GetDay() );
	FString nowHour = FString::Printf( TEXT( "%02d" ), nowDateTime.GetHour() );
	FString nowCalcTime = nowYear + nowMonth + nowDay + nowHour;

	const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
	for( int32 matchIndex = 0; matchIndex < matchDataList.Num(); ++matchIndex )
	{
		if( matchDataList[matchIndex].InfoType != E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE )
		{
			continue;
		}

		if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
		{
			if( matchDataList[matchIndex].MatchType != E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
			{
				continue;
			}
		}
		else if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
		{
			if( matchDataList[matchIndex].MatchType != E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
			{
				continue;
			}
		}

		FString strHour = matchDataList[matchIndex].MatchTime.Left( 2 );
		FString strCalcTime = matchDataList[matchIndex].MatchDate + strHour;
		if( nowCalcTime < strCalcTime )
		{
			_ArrayMatchData.Add( matchDataList[matchIndex] );
		}		
	}

	_ArrayMatchData.Sort( []( const FST_MATCH_DATA& A, const FST_MATCH_DATA& B )
						{
							return (A.MatchDate == B.MatchDate) ? A.MatchTime < B.MatchTime : A.MatchDate < B.MatchDate;
						} );

	_CurScrollInex = 0;
	_MaxScrollInex = _ArrayMatchData.Num();
	_UpdateScrollItem();
}

void UBWidget_MainSchedule::PlayScheduleMainOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_ScheduleMainOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ScheduleMainOpen ) )
			{
				StopAnimation( _Ani_ScheduleMainOpen );
			}

			PlayAnimation( _Ani_ScheduleMainOpen );
		}
	}
	else
	{
		if( _Ani_ScheduleMainClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ScheduleMainClose ) )
			{
				StopAnimation( _Ani_ScheduleMainClose );
			}

			PlayAnimation( _Ani_ScheduleMainClose );
		}
	}
}

void UBWidget_MainSchedule::OnClickScheduleMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce /*= true */ )
{
	if( isForce == false && _MainFilterType == mainFilterType )
	{
		return;
	}

	_MainFilterType = mainFilterType;

	switch( mainFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL:
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
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH:
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
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH:
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
		break;
	}


	SetSubScheduleItem( mainFilterType );
}

bool UBWidget_MainSchedule::_OnBackInput()
{
	Super::_OnBackInput();
	PlayScheduleMainOpenAni( false );
	return true;
}

void UBWidget_MainSchedule::_UpdateScrollItem()
{
	int32 startIndex = _CurScrollInex;
	int32 endIndex = FMath::Min( _MaxScrollInex, startIndex + SCROLL_ITEM_NUM );
	for( int32 matchIndex = startIndex; matchIndex < endIndex; ++matchIndex )
	{
		UBWidget_MatchItem* matchItemWidget = B_HUD->CreateDynamicWidget<UBWidget_MatchItem>( EDynamicWidgetParts::MatchItemSlot );
		if( matchItemWidget != nullptr )
		{
			matchItemWidget->OwnerPannel = this;
			matchItemWidget->SetMatchItem( _ArrayMatchData[matchIndex]);
			matchItemWidget->SetMatchInfoType( E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE );
			C_SB_Item->AddChild( matchItemWidget );
			_CurScrollInex++;
		}
	}
}
