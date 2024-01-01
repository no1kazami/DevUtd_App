#include "BWidget_MatchItem.h"
#include "../../FBM_SaveGame.h"
#include "GameMode/BGameMode_main.h"
#include "Bigtamin.h"
#include "UI/Match/BWidget_ResultDetail.h"

void UBWidget_MatchItem::Init()
{
	Super::Init();

	OnSuccessDownLoadHomeTeamLogoImage.BindUFunction( this, "_OnSuccessDownLoadHomeTeamLogoImage" );
	OnFailDownLoadHomeTeamLogoImage.BindUFunction( this, "_OnFailDownLoadHomeTeamLogoImage" );
	OnSuccessDownLoadAwayTeamLogoImage.BindUFunction( this, "_OnSuccessDownLoadAwayTeamLogoImage" );
	OnFailDownLoadHomeTeamLogoImage.BindUFunction( this, "_OnFailDownLoadAwayTeamLogoImage" );

	ButtonDelegate_Clicked( this, C_Btn_Match, &UBWidget_MatchItem::_OnClick_ItemBtn );

	C_VB_UnderLine->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBWidget_MatchItem::OnClose()
{
	Super::OnClose();
}

void UBWidget_MatchItem::SetMainDataSchedule()
{
	C_VB_UnderLine->SetVisibility( ESlateVisibility::Collapsed );

	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );
	FString nowMonth = FString::Printf( TEXT( "%02d" ), nowDateTime.GetMonth() );
	FString nowDay = FString::Printf( TEXT( "%02d" ), nowDateTime.GetDay() );
	FString nowHour = FString::Printf( TEXT( "%02d" ), nowDateTime.GetHour() );
	FString nowCalcTime = nowYear + nowMonth + nowDay + nowHour;

	const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
	FString finalCalcTime;
	int32 resultIndex = 0;
	for( int32 matchIndex = 0; matchIndex < matchDataList.Num(); ++matchIndex )
	{
		if( matchDataList[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_SCHEDULE )
		{
			FString strHour = matchDataList[matchIndex].MatchTime.Left( 2 );
			FString strCalcTime = matchDataList[matchIndex].MatchDate + strHour;
			if( nowCalcTime < strCalcTime )
			{
				if ( finalCalcTime.IsEmpty() || finalCalcTime > strCalcTime )
				{
					finalCalcTime = strCalcTime;
					resultIndex = matchIndex;
				}
			}
		}
	}

	if( !finalCalcTime.IsEmpty() )
	{
		SetMatchItem( matchDataList[resultIndex] );
	}
}

void UBWidget_MatchItem::SetMainDataResult()
{
	C_VB_UnderLine->SetVisibility( ESlateVisibility::Collapsed );

	const TArray<FST_MATCH_DATA> matchDataList = UFBM_SaveGame::Get().GetMatchData_DB();
	int32 resultDate = 0;
	int32 resultIndex = 0;
	for( int32 matchIndex = 0; matchIndex < matchDataList.Num(); ++matchIndex )
	{
		if( matchDataList[matchIndex].InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
		{
			int32 matchDate = FCString::Atoi( *matchDataList[matchIndex].MatchDate );
			if ( resultDate < matchDate )
			{
				resultDate = matchDate;
				resultIndex = matchIndex;
			}
		}
	}

	if( resultDate > 0 )
	{
		SetMatchItem( matchDataList[resultIndex] );
	}
}

void UBWidget_MatchItem::SetMatchItem( FST_MATCH_DATA matchData )
{
	_MatchData = matchData;

	// 매치 타입
	switch( matchData.MatchType )
	{
	case E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH:
		C_Txt_Title->SetText( GET_BTEXT( 7 ) );
		break;
	case E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH:
		C_Txt_Title->SetText( GET_BTEXT( 8 ) );
		break;
	case E_MATCH_TYPE::E_MATCH_TYPE_ETC:
		break;
	default:
		break;
	}

	// 코멘트
	C_Txt_Comment->SetText( FText::FromString( matchData.Comment ) );

	// VS or 점수
	if( matchData.InfoType == E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_RESULT )
	{
		C_Txt_Change->SetText( FText::Format( GET_BTEXT( 12 ), FText::AsNumber( matchData.HomeGoal ), FText::AsNumber( matchData.AwayGoal ) ) );
	}
	else
	{
		C_Txt_Change->SetText( GET_BTEXT( 13 ) );
	}

	// 날짜
	FString MatchDate = matchData.MatchDate;
	FString strYear = MatchDate.Left( 4 );
	FString strMon = MatchDate.Mid( 4, 2 );
	FString strDay = MatchDate.Right( 2 );
	MatchDate = strYear + "." + strMon + "." + strDay;
	C_Txt_MatchDate->SetText( FText::FromString( MatchDate ) );

	// 시간
	C_Txt_Time->SetText( FText::FromString( matchData.MatchTime ) );

	// 홈팀
	C_Txt_Home->SetText( FText::FromString( matchData.HomeTeamName ) );

	// 원정팀
	C_Txt_Away->SetText( FText::FromString( matchData.AwayTeamName ) );

	// 홈팀 로고 이미지
	C_Img_Home->SetVisibility( ESlateVisibility::Visible );
	_HomeTeamName = matchData.HomeTeamName;
	UTexture2DDynamic* homeTeamDownLoadImg = GInst->GetDownLoadTeamLogoImage( matchData.HomeTeamName );
	if( homeTeamDownLoadImg != nullptr )
	{
		if( C_Img_Home != nullptr )
		{
			C_Img_Home->SetBrushFromTextureDynamic( homeTeamDownLoadImg, false );
		}
	}
	else
	{
		const FString homeLogoURL = UFBM_SaveGame::Get().GetTeamLogoURL_DB( matchData.HomeTeamName );
		if( homeLogoURL.IsEmpty() == false )
		{
			DownLoadTexture_URL( homeLogoURL, OnSuccessDownLoadHomeTeamLogoImage, OnFailDownLoadHomeTeamLogoImage );
		}
		else
		{
			C_Img_Home->SetVisibility( ESlateVisibility::Hidden );
		}
	}

	// 원정팀 로고 이미지
	C_Img_Away->SetVisibility( ESlateVisibility::Visible );
	_AwayTeamName = matchData.AwayTeamName;
	UTexture2DDynamic* awayTeamDownLoadImg = GInst->GetDownLoadTeamLogoImage( matchData.AwayTeamName );
	if( awayTeamDownLoadImg != nullptr )
	{
		if( C_Img_Away != nullptr )
		{
			C_Img_Away->SetBrushFromTextureDynamic( awayTeamDownLoadImg, false );
		}
	}
	else
	{
		const FString awayLogoURL = UFBM_SaveGame::Get().GetTeamLogoURL_DB( matchData.AwayTeamName );
		if( awayLogoURL.IsEmpty() == false )
		{
			DownLoadTexture_URL( awayLogoURL, OnSuccessDownLoadAwayTeamLogoImage, OnFailDownLoadAwayTeamLogoImage );
		}
		else
		{
			C_Img_Away->SetVisibility( ESlateVisibility::Hidden );
		}
	}
}

void UBWidget_MatchItem::SetShowDetail( const bool isShowDetail )
{
	_IsDetailShow = isShowDetail;
}

void UBWidget_MatchItem::_OnSuccessDownLoadHomeTeamLogoImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadTeamLogoImage( _HomeTeamName, texturl );
		if( C_Img_Home != nullptr )
		{
			C_Img_Home->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MatchItem::_OnFailDownLoadHomeTeamLogoImage( UTexture2DDynamic* texturl )
{

}

void UBWidget_MatchItem::_OnSuccessDownLoadAwayTeamLogoImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadTeamLogoImage( _AwayTeamName, texturl );
		if( C_Img_Away != nullptr )
		{
			C_Img_Away->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_MatchItem::_OnFailDownLoadHomeAwayLogoImage( UTexture2DDynamic* texturl )
{

}

void UBWidget_MatchItem::_OnClick_ItemBtn()
{
	if ( _IsDetailShow )
	{
		ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
		if( gameMode != nullptr )
		{
			gameMode->ChangeMode( E_MODE::E_MODE_RESULT_DETAIL );
			UBWidget_ResultDetail* resultDetailWidget = B_HUD->GetWidgetInViewport<UBWidget_ResultDetail>( EBUIName::ResultDetail );
			if( resultDetailWidget != nullptr )
			{
				resultDetailWidget->SetData( _MatchData );
			}
		}
	}
}
