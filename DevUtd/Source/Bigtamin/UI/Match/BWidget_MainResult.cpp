#include "BWidget_MainResult.h"
#include "BWidget_MatchItem.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "UI/BWidget_Top.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"

#define SCROLL_ITEM_NUM 30

void UBWidget_MainResult::Init()
{
	Super::Init();

	BP_Top_ResultMain_UMG->Init();
	BP_Top_ResultMain_UMG->ChangeTopMode( E_MODE::E_MODE_RESULT_MAIN );

	_Ani_ResultMainOpen = GetWidgetAnimation( _Ani_ResultMainOpenName );
	_Ani_ResultMainClose = GetWidgetAnimation( _Ani_ResultMainCloseName );

	ButtonDelegate_Clicked( this, C_Btn_Year_Prev, &UBWidget_MainResult::_OnClick_YearPrevBtn );
	ButtonDelegate_Clicked( this, C_Btn_Year_Next, &UBWidget_MainResult::_OnClick_YearNextBtn );

	InitResultMain();

	GInst->AddBackInput( this );

	PlayResultMainOpenAni( true );
}

void UBWidget_MainResult::OnClose()
{
	Super::OnClose();
}

void UBWidget_MainResult::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
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

void UBWidget_MainResult::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
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

void UBWidget_MainResult::InitResultMain()
{
	_YearData.Empty();
	FString tmpYear;
	const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
	for( int32 matchIndex = 0; matchIndex < matchDataList.Num(); ++matchIndex )
	{
		FString matchYear = matchDataList[matchIndex].MatchDate.Left( 4 );
		_YearData.AddUnique( matchYear );
		if ( tmpYear.IsEmpty() || tmpYear < matchYear )
		{
			tmpYear = matchYear;
		}
	}

	_NowYear = tmpYear;
	_UpdateYear();

	_MainFilterItems.Empty();
	C_SB_ResultType->ClearChildren();
	C_SB_ResultType->ScrollToStart();

	// 결과 전체 타입
	UBWidget_EquipFilterItem* resultAllWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( resultAllWidget != nullptr )
	{
		resultAllWidget->OwnerPannel = this;
		resultAllWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, 6 );
		if( resultAllWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			resultAllWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainResult::OnClickResultMainFilter );
		}
		C_SB_ResultType->AddChild( resultAllWidget );
		_MainFilterItems.Add( resultAllWidget );
	}

	// 결과 A-Match 타입
	UBWidget_EquipFilterItem* resultAMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( resultAMatchWidget != nullptr )
	{
		resultAMatchWidget->OwnerPannel = this;
		resultAMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH, 7 );
		if( resultAMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			resultAMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainResult::OnClickResultMainFilter );
		}
		C_SB_ResultType->AddChild( resultAMatchWidget );
		_MainFilterItems.Add( resultAMatchWidget );
	}

	// 일정 자체전 타입
	UBWidget_EquipFilterItem* resultOwnMatchWidget = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( resultOwnMatchWidget != nullptr )
	{
		resultOwnMatchWidget->OwnerPannel = this;
		resultOwnMatchWidget->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH, 8 );
		if( resultOwnMatchWidget->OnClickRankingFilter.IsBoundToObject( this ) == false )
		{
			resultOwnMatchWidget->OnClickRankingFilter.AddUObject( this, &UBWidget_MainResult::OnClickResultMainFilter );
		}
		C_SB_ResultType->AddChild( resultOwnMatchWidget );
		_MainFilterItems.Add( resultOwnMatchWidget );
	}

	OnClickResultMainFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL, true );
}

void UBWidget_MainResult::SetSubResultItem( const E_FILTER_ITEM_TYPE mainFilterType )
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
		if( matchDataList[matchIndex].InfoType != E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
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

		FString strYear = matchDataList[matchIndex].MatchDate.Left( 4 );
		if( _NowYear != strYear )
		{
			continue;
		}

		_ArrayMatchData.Add( matchDataList[matchIndex] );
	}

	_ArrayMatchData.Sort( []( const FST_MATCH_DATA& A, const FST_MATCH_DATA& B )
						  {
							  return (A.MatchDate == B.MatchDate) ? A.MatchTime > B.MatchTime : A.MatchDate > B.MatchDate;
						  } );

	_CurScrollInex = 0;
	_MaxScrollInex = _ArrayMatchData.Num();
	_UpdateScrollItem();
}

void UBWidget_MainResult::PlayResultMainOpenAni( const bool isOpen )
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

void UBWidget_MainResult::OnClickResultMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce /*= true */ )
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

	SetSubResultItem( mainFilterType );
}

bool UBWidget_MainResult::_OnBackInput()
{
	Super::_OnBackInput();
	PlayResultMainOpenAni( false );
	return true;
}

void UBWidget_MainResult::_OnClick_YearPrevBtn()
{
	int32 nowYear = FCString::Atoi( *_NowYear );
	FString strPrevYear = FString::FromInt( nowYear - 1 );
	int32 findIndex = _YearData.Find( strPrevYear );
	if( findIndex != INDEX_NONE )
	{
		_NowYear = strPrevYear;
		_UpdateYear();
		SetSubResultItem( _MainFilterType );
	}
}

void UBWidget_MainResult::_OnClick_YearNextBtn()
{
	int32 nowYear = FCString::Atoi( *_NowYear );
	FString strNextYear = FString::FromInt( nowYear + 1 );
	int32 findIndex = _YearData.Find( strNextYear );
	if( findIndex != INDEX_NONE )
	{
		_NowYear = strNextYear;
		_UpdateYear();
		SetSubResultItem( _MainFilterType );
	}
}

void UBWidget_MainResult::_UpdateScrollItem()
{
	int32 startIndex = _CurScrollInex;
	int32 endIndex = FMath::Min( _MaxScrollInex, startIndex + SCROLL_ITEM_NUM );
	for( int32 matchIndex = startIndex; matchIndex < endIndex; ++matchIndex )
	{
		UBWidget_MatchItem* matchItemWidget = B_HUD->CreateDynamicWidget<UBWidget_MatchItem>( EDynamicWidgetParts::MatchItemSlot );
		if( matchItemWidget != nullptr )
		{
			matchItemWidget->OwnerPannel = this;
			matchItemWidget->SetMatchItem( _ArrayMatchData[matchIndex] );
			matchItemWidget->SetMatchInfoType( E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT );
			C_SB_Item->AddChild( matchItemWidget );
			_CurScrollInex++;
		}
	}
}

void UBWidget_MainResult::_UpdateYear()
{
	C_Txt_Year->SetText( FText::FromString( _NowYear ) );

	int32 nowYear = FCString::Atoi( *_NowYear );

	FString strPrevYear = FString::FromInt( nowYear - 1 );
	int32 findPrevIndex = _YearData.Find( strPrevYear );
	//C_Btn_Year_Prev->SetDisabled( findPrevIndex == INDEX_NONE ? true : false );

	FString strNextYear = FString::FromInt( nowYear + 1 );
	int32 findNextIndex = _YearData.Find( strNextYear );
	//C_Btn_Year_Next->SetDisabled( findNextIndex == INDEX_NONE ? true : false );
}
