#include "BWidget_NewMain.h"
#include "Bigtamin.h"
#include "../FBM_SaveGame.h"
#include "UI/Equip/BWidget_EquipMain.h"
#include "UI/Common/BWidget_CommonItemSlot.h"
#include "UI/Main/BWidget_UpdateCheck.h"
#include "GameMode/BGameMode_main.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Kismet/KismetStringLibrary.h"
#include "UI/Match/BWidget_MainMatchSlot.h"
#include "UI/Ranking/BWidget_MainRankingSlot.h"

#define MAIN_AD_BANNER_IMAGE_SIZE FVector2D( 1024.f, 512.f )
#define NEW_ITEM_MAX_NUM 5

void UBWidget_NewMain::Init()
{
	Super::Init();

	BP_Top_UMG->Init();
	BP_Top_UMG->ChangeTopMode( E_MODE::E_MODE_MAIN );
	BP_MainCategory_UMG->Init( this );
	BP_MainCategory_UMG->SetVisibility( ESlateVisibility::Collapsed );
	if( BP_MainCategory_UMG->OnClickMainCategory.IsBoundToObject( this ) == false )
	{
		BP_MainCategory_UMG->OnClickMainCategory.AddUObject( this, &UBWidget_NewMain::_OnClickCategoryEvent );
	}

	ButtonDelegate_Clicked( this, C_Btn_Schedule, &UBWidget_NewMain::_OnClick_Schedule );
	ButtonDelegate_Clicked( this, C_Btn_Result, &UBWidget_NewMain::_OnClick_Result );
	ButtonDelegate_Clicked( this, C_Btn_Ranking, &UBWidget_NewMain::_OnClick_Ranking );
	ButtonDelegate_Clicked( this, C_Btn_TeamInfo, &UBWidget_NewMain::_OnClick_TeamInfo );

	OnSuccessDownLoadImageMainBanner1.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner1" );
	OnSuccessDownLoadImageMainBanner2.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner2" );
	OnSuccessDownLoadImageMainBanner3.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner3" );
	OnSuccessDownLoadImageMainBanner4.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner4" );
	OnSuccessDownLoadImageMainBanner5.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner5" );
	OnSuccessDownLoadImageMainBanner6.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner6" );
	OnSuccessDownLoadImageMainBanner7.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner7" );
	OnSuccessDownLoadImageMainBanner8.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner8" );
	OnSuccessDownLoadImageMainBanner9.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner9" );
	OnSuccessDownLoadImageMainBanner10.BindUFunction( this, "_OnSuccessDownLoadImageMainBanner10" );

	OnFailDownLoadImageMainBanner.BindUFunction( this, "_OnFailDownLoadImageMainBanner" );

	//C_Txt_Info->SetText( GET_BTEXT( 69 ) );

	SetContentsSizeX( 1024.f );
	_InitMainADBanner();

	_InitSchedule();
	_InitResult();
	_InitRankAttendance();
	_InitRankGoal();
	_InitRankAssist();
	_InitRankPoint();
	_InitRankYearMvp();
	_InitRankYearKing();

	_Ani_Quit = GetWidgetAnimation( _Ani_QuitName );
	_Ani_CategoryOpen = GetWidgetAnimation( _Ani_CategoryOpenName );
	_Ani_CategoryClose = GetWidgetAnimation( _Ani_CategoryCloseName );

	if (_CheckServerCheckTime())
	{
		_CheckVersion();
	}
}

void UBWidget_NewMain::OnClose()
{

}

void UBWidget_NewMain::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
{
	Super::NativeTick( MyGeometry, InDeltaTime );
}

void UBWidget_NewMain::ChangeMode( E_MODE changeMode )
{
	/*
	switch( changeMode )
	{
	case E_MODE::E_MODE_SURVEY:
		C_WidgetSwitcher_Main->SetActiveWidgetIndex( 0 );
		BP_Survey_UMG->InitSurvey();
		break;
	case E_MODE::E_MODE_SURVEY_RESULT:
		C_WidgetSwitcher_Main->SetActiveWidgetIndex( 2 );
		BP_Survey_Result_UMG->InitSurveyResult();
		break;
	case E_MODE::E_MODE_LOBBY:
		C_WidgetSwitcher_Main->SetActiveWidgetIndex( 1 );
		BP_Lobby_UMG->ChangeLobbyMode( E_LOBBY_MODE::E_LOBBY_MODE_MYINFO );
		break;
	case E_MODE::E_MODE_BOOTS_DETAIL:
		C_WidgetSwitcher_Main->SetActiveWidgetIndex( 3 );
		BP_Boots_Detail_UMG->InitBootsDetail();
		break;
	default:
		break;
	}

	BP_Top_UMG->ChangeTopMode( changeMode );
	BP_Bottom_UMG->ChangeBottomMode( changeMode );
	*/
}

void UBWidget_NewMain::PlayQuit()
{
	if( _Ani_Quit != nullptr )
	{
		if( IsAnimationPlaying( _Ani_Quit ) )
		{
			UKismetSystemLibrary::QuitGame( this->GetWorld(), this->GetPlayerController(), EQuitPreference::Quit, false );
		}
		else
		{
			PlayAnimation( _Ani_Quit );
		}
	}
	else
	{
		UKismetSystemLibrary::QuitGame( this->GetWorld(), this->GetPlayerController(), EQuitPreference::Quit, false );
	}
}

void UBWidget_NewMain::PlayCategoryAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_CategoryOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_CategoryOpen ) )
			{
				StopAnimation( _Ani_CategoryOpen );
			}

			PlayAnimation( _Ani_CategoryOpen );
		}
	}
	else
	{
		if( _Ani_CategoryClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_CategoryClose ) )
			{
				StopAnimation( _Ani_CategoryClose );
			}

			PlayAnimation( _Ani_CategoryClose );
		}
	}
}

void UBWidget_NewMain::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_CategoryCloseName )
		{
			ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
			if( gameMode != nullptr )
			{
				switch( _CurMainCategoryType )
				{
				case E_MAINCATEGORY_TYPE::NOTICE:
					gameMode->ChangeMode( E_MODE::E_MODE_NOTICE );
					break;
				case E_MAINCATEGORY_TYPE::FAQ:
					gameMode->ChangeMode( E_MODE::E_MODE_FAQ );
					break;
				case E_MAINCATEGORY_TYPE::VERSION:
					gameMode->ChangeMode( E_MODE::E_MODE_VERSION );
					break;
				case E_MAINCATEGORY_TYPE::BOOTS:
					gameMode->ChangeMode( E_MODE::E_MODE_EQUIP_MAIN );
					break;
				case E_MAINCATEGORY_TYPE::SCRAP:
					gameMode->ChangeMode( E_MODE::E_MODE_BOOKMARK );
					break;
				case E_MAINCATEGORY_TYPE::UPCOMING:
					gameMode->ChangeMode( E_MODE::E_MODE_UPCOMING );
					break;
				case E_MAINCATEGORY_TYPE::SCHEDULE:
					gameMode->ChangeMode( E_MODE::E_MODE_SCHEDULE_MAIN );
					break;
				case E_MAINCATEGORY_TYPE::RESULT:
					gameMode->ChangeMode( E_MODE::E_MODE_RESULT_MAIN );
					break;
				case E_MAINCATEGORY_TYPE::RANKING:
					gameMode->ChangeMode( E_MODE::E_MODE_RANKING_MAIN );
					break;
				case E_MAINCATEGORY_TYPE::PLAYER:
					gameMode->ChangeMode( E_MODE::E_MODE_PLAYER_MAIN );
					break;
				default:
					break;
				}
			}

			_CurMainCategoryType = E_MAINCATEGORY_TYPE::NONE;
		}
	}
}

void UBWidget_NewMain::_OnClickSwipeScrollItem( int32 itemIndex )
{
	Super::_OnClickSwipeScrollItem(itemIndex);

	_OnClickMainBanner(itemIndex - 1);
}

void UBWidget_NewMain::_OnClick_Ranking()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_RANKING_MAIN );
	}
}

void UBWidget_NewMain::_OnClick_Schedule()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_SCHEDULE_MAIN );
	}
}

void UBWidget_NewMain::_OnClick_Result()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_RESULT_MAIN );
	}
}

void UBWidget_NewMain::_OnClick_TeamInfo()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_PLAYER_MAIN );
	}
}

void UBWidget_NewMain::_OnClickCategoryEvent( const E_MAINCATEGORY_TYPE mainCategoryType )
{
	_CurMainCategoryType = mainCategoryType;

	switch(mainCategoryType)
	{
	case E_MAINCATEGORY_TYPE::NOTICE:
	case E_MAINCATEGORY_TYPE::FAQ:
	case E_MAINCATEGORY_TYPE::VERSION:
	case E_MAINCATEGORY_TYPE::BOOTS:
	case E_MAINCATEGORY_TYPE::SCRAP:
	case E_MAINCATEGORY_TYPE::UPCOMING:
	case E_MAINCATEGORY_TYPE::SCHEDULE:
	case E_MAINCATEGORY_TYPE::RESULT:
	case E_MAINCATEGORY_TYPE::RANKING:
	case E_MAINCATEGORY_TYPE::PLAYER:
		PlayCategoryAni( false );
		break;
	default:
		break;
	}
}

void UBWidget_NewMain::_InitMainADBanner()
{
	InitSwipeScrollComponent();

#if PLATFORM_ANDROID
	const TArray<FST_MAIN_BANNER_DATA> mainBannerData = UFBM_SaveGame::Get().GetMainBannerData();
#else	
	TArray<FST_MAIN_BANNER_DATA> mainBannerData;
	FST_MAIN_BANNER_DATA tempData1( E_BANNER_TYPE::NONE , TEXT( "empty" ), TEXT( "https://i.postimg.cc/LXq2Wq24/Banner-Test01.jpg" ));
	FST_MAIN_BANNER_DATA tempData2( E_BANNER_TYPE::URL, TEXT( "www.naver.com" ), TEXT( "https://i.postimg.cc/pXMR0X7x/Banner-Test02.jpg" ));
	FST_MAIN_BANNER_DATA tempData3( E_BANNER_TYPE::PRODUCT, TEXT( "99" ), TEXT( "https://i.postimg.cc/mZHTNFm8/Banner-Test03.jpg" ));
	mainBannerData.Add( tempData1 );
	mainBannerData.Add( tempData2 );
	mainBannerData.Add( tempData3 );
#endif

	for( int32 slotIndex = 0; slotIndex < mainBannerData.Num(); ++slotIndex )
	{
		UAsyncTaskDownloadImage* taskDownLoadImage = UAsyncTaskDownloadImage::DownloadImage( mainBannerData[slotIndex].BannerImgURL );
		if( taskDownLoadImage != nullptr )
		{
			if( taskDownLoadImage->OnSuccess.IsBound() == false )
			{
				switch( slotIndex )
				{
				case 0:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner1 );
					break;
				case 1:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner2 );
					break;
				case 2:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner3 );
					break;
				case 3:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner4 );
					break;
				case 4:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner5 );
					break;
				case 5:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner6 );
					break;
				case 6:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner7 );
					break;
				case 7:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner8 );
					break;
				case 8:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner9 );
					break;
				case 9:
					taskDownLoadImage->OnSuccess.Add( OnSuccessDownLoadImageMainBanner10 );
					break;
				default:
					break;
				}
				
			}
			if( taskDownLoadImage->OnFail.IsBound() == false )
			{
				taskDownLoadImage->OnFail.Add( OnFailDownLoadImageMainBanner );
			}
		}
	}

	FBM_LOG_FUNCTION_INFO( Log, TEXT( "mainBannerUrl Num : %d" ), mainBannerData.Num() )
	/*
	FString mURL = TEXT( "https://blogfiles.pstatic.net/MjAyMDA0MjZfMjYw/MDAxNTg3ODk4Nzg2MjU1.V8H3Kod3_XvO8kVrDJIU_P4vcMdTMOnkVe-CGJsP6zcg.SACU_dgcKJYbxSJ2izIK2YiQb14IIKIeSjpCSP1TlW4g.JPEG.usinggo/Banner_Test01.jpg" );
	UAsyncTaskDownloadImage* mDownloadTask = NewObject<UAsyncTaskDownloadImage>();
	mDownloadTask->OnSuccess.AddDynamic( this, &UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner );
	mDownloadTask->OnFail.AddDynamic( this, &UBWidget_NewMain::_OnFailDownLoadImageMainBanner );
	mDownloadTask->Start( mURL );
	*/
}

void UBWidget_NewMain::_InitSchedule()
{
	BP_ScheduleSlot_UMG->Init();
	BP_ScheduleSlot_UMG->SetDataSchedule();
}

void UBWidget_NewMain::_InitResult()
{
	BP_ResultSlot_UMG->Init();
	BP_ResultSlot_UMG->SetDataResult();
}

void UBWidget_NewMain::_InitRankAttendance()
{
	BP_Rank_Attendance_UMG->Init();
	BP_Rank_Attendance_UMG->SetData( E_RANKING_TYPE::E_RANKING_TYPE_ATTENDANCE );
}

void UBWidget_NewMain::_InitRankGoal()
{
	BP_Rank_Goal_UMG->Init();
	BP_Rank_Goal_UMG->SetData(E_RANKING_TYPE::E_RANKING_TYPE_GOAL);
}

void UBWidget_NewMain::_InitRankAssist()
{
	BP_Rank_Assist_UMG->Init();
	BP_Rank_Assist_UMG->SetData( E_RANKING_TYPE::E_RANKING_TYPE_ASSIST );
}

void UBWidget_NewMain::_InitRankPoint()
{
	BP_Rank_Point_UMG->Init();
	BP_Rank_Point_UMG->SetData( E_RANKING_TYPE::E_RANKING_TYPE_POINT );
}

void UBWidget_NewMain::_InitRankYearMvp()
{
	BP_Rank_Year_Mvp_UMG->Init();
	BP_Rank_Year_Mvp_UMG->SetData( E_RANKING_TYPE::E_RANKING_TYPE_YEAR_MVP );
}

void UBWidget_NewMain::_InitRankYearKing()
{
	BP_Rank_Year_King_UMG->Init();
	BP_Rank_Year_King_UMG->SetData( E_RANKING_TYPE::E_RANKING_TYPE_YEAR_KING );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner1( UTexture2DDynamic* texturl )
{
	_SetBannerImg(texturl, 1);
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner2( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 2 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner3( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 3 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner4( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 4 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner5( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 5 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner6( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 6 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner7( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 7 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner8( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 8 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner9( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 9 );
}

void UBWidget_NewMain::_OnSuccessDownLoadImageMainBanner10( UTexture2DDynamic* texturl )
{
	_SetBannerImg( texturl, 10 );
}

void UBWidget_NewMain::_OnFailDownLoadImageMainBanner( UTexture2DDynamic* texturl )
{

}

void UBWidget_NewMain::_SetBannerImg( UTexture2DDynamic* texturl, int32 bannerIndex )
{
	if( texturl != nullptr )
	{
		UImage* adImage = NewObject<UImage>( UImage::StaticClass() );
		if( adImage != nullptr )
		{			
			adImage->SetBrushFromTextureDynamic( texturl, true );
			adImage->SetBrushSize( MAIN_AD_BANNER_IMAGE_SIZE );
			adImage->SetVisibility( ESlateVisibility::Visible );
			AddSwipeScrollChild( adImage, bannerIndex, false );
		}
	}
}

void UBWidget_NewMain::_OnClickMainBanner( const int32 bannerIndex )
{
#if PLATFORM_ANDROID
	const TArray<FST_MAIN_BANNER_DATA> mainBannerData = UFBM_SaveGame::Get().GetMainBannerData();
#else
	TArray<FST_MAIN_BANNER_DATA> mainBannerData;
	FST_MAIN_BANNER_DATA tempData1( E_BANNER_TYPE::NONE, TEXT( "empty" ), TEXT( "https://i.postimg.cc/LXq2Wq24/Banner-Test01.jpg" ) );
	FST_MAIN_BANNER_DATA tempData2( E_BANNER_TYPE::URL, TEXT( "www.naver.com" ), TEXT( "https://i.postimg.cc/pXMR0X7x/Banner-Test02.jpg" ) );
	FST_MAIN_BANNER_DATA tempData3( E_BANNER_TYPE::PRODUCT, TEXT( "99" ), TEXT( "https://i.postimg.cc/mZHTNFm8/Banner-Test03.jpg" ) );
	mainBannerData.Add( tempData1 );
	mainBannerData.Add( tempData2 );
	mainBannerData.Add( tempData3 );
#endif

	if ( bannerIndex >= 0 && bannerIndex < mainBannerData.Num())
	{
		if( mainBannerData[bannerIndex].BannerType == E_BANNER_TYPE::URL )
		{
			UKismetSystemLibrary::LaunchURL( mainBannerData[bannerIndex].BannerValue );
		}
		else if( mainBannerData[bannerIndex].BannerType == E_BANNER_TYPE::PRODUCT )
		{
			ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
			if( gameMode != nullptr )
			{
				GInst->SetCurSelectBootsIndex( FCString::Atoi( *(mainBannerData[bannerIndex].BannerValue) ) );
				gameMode->ChangeMode( E_MODE::E_MODE_BOOTS_DETAIL );
			}
		}
	}
}

bool UBWidget_NewMain::_CheckServerCheckTime()
{
#if PLATFORM_ANDROID
	FString serverCheckTime = UFBM_SaveGame::Get().GetServetCheckTime();
#else
	//FString serverCheckTime = TEXT( "10:00 ~ 12:00" );
	FString serverCheckTime;
#endif

	if (serverCheckTime.IsEmpty())
	{
		return true;
	}

	UBWidget_UpdateCheck* updateCheckWidget = B_HUD->CreateDynamicWidget<UBWidget_UpdateCheck>( EDynamicWidgetParts::UpdateCheck, true, 9999 );
	if( updateCheckWidget != nullptr )
	{
		updateCheckWidget->InitUpdateCheck( E_UPDATE_CHECK_TYPE::SERVER_CHECK );
	}

	return false;
}

bool UBWidget_NewMain::_CheckVersion()
{
#if PLATFORM_ANDROID
	FString curServerVer = UFBM_SaveGame::Get().GetCurVersion();
#else
	FString curServerVer = TEXT( "1.0.3" );
#endif

	FString curClientVersion;
	bool isFound = GConfig->GetString( TEXT( "/Script/AndroidRuntimeSettings.AndroidRuntimeSettings" ), TEXT( "VersionDisplayName" ), curClientVersion, GEngineIni );
	if ( isFound && curServerVer.Compare( curClientVersion ) == 0)
	{
		return true;
	}

	UBWidget_UpdateCheck* updateCheckWidget = B_HUD->CreateDynamicWidget<UBWidget_UpdateCheck>( EDynamicWidgetParts::UpdateCheck, true, 9999 );
	if( updateCheckWidget != nullptr )
	{
		updateCheckWidget->InitUpdateCheck( E_UPDATE_CHECK_TYPE::UPDATE );
	}

	return false;
}
