// Fill out your copyright notice in the Description page of Project Settings.
#include "FireBaseManager.h"
#include "Bigtamin.h"
#include "../FBM_SaveGame.h"
#include "Kismet/KismetStringLibrary.h"
#include "../Plugins/UltimateMobileKit/Source/UltimateMobileKit/Public/App/AppLibrary.h"
#include "../Plugins/UltimateMobileKit/Source/UltimateMobileKit/Public/App/AppMakeGooglePlayAvailableProxy.h"

UFireBaseManager::UFireBaseManager()
{
	/*
	TArray<UFirebaseVariant*> Parameters = TArray<UFirebaseVariant*>();
	UFirebaseVariant* Parameter1 = UFirebaseVariant::FirebaseStringVariant( TEXT( "Parameter1_Name" ), TEXT( "Parameter1_Value" ) );
	UFirebaseVariant* Parameter2 = UFirebaseVariant::FirebaseBooleanVariant( TEXT( "Parameter2_Name" ), true );
	UFirebaseVariant* Parameter3 = UFirebaseVariant::FirebaseIntegerVariant( TEXT( "Parameter3_Name" ), 28 );
	UFirebaseVariant* Parameter4 =UFirebaseVariant::FirebaseFloatVariant( TEXT( "Parameter4_Name" ), 67.12f );
	*/
}

UFireBaseManager::~UFireBaseManager()
{
}

void UFireBaseManager::Startup()
{
	MakeGooglePlayAvailableProxyOnSuccess.BindUFunction( this, "_OnMakeGooglePlayAvailableProxyOnSuccess" );
	MakeGooglePlayAvailableProxyOnFail.BindUFunction( this, "_OnMakeGooglePlayAvailableProxyOnFail" );

#if PLATFORM_ANDROID
	InitMyFireBase();
#endif
}

void UFireBaseManager::Shutdown()
{

}

void UFireBaseManager::LogOut()
{

}

void UFireBaseManager::InitMyFireBase()
{
	bool isFirebaseInit = UUltimateMobileKitApp::IsFirebaseInitialized();
	if( isFirebaseInit )
	{
		_InitFirebaseAnalytics();

		FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseInitialized Success" ) );

		/*
		EGooglePlayAvailability googlePlayAvailability = UUltimateMobileKitApp::CheckGooglePlayAvailability();
		if( googlePlayAvailability == EGooglePlayAvailability::Available )
		{
			_InitFirebaseAnalytics();
		}
		else
		{
			UFirebaseAppMakeGooglePlayAvailableProxy* firebaseAppMakeGooglePlayAvailableProxy = UFirebaseAppMakeGooglePlayAvailableProxy::MakeGooglePlayAvailable();
			if( firebaseAppMakeGooglePlayAvailableProxy != nullptr )
			{
				if( firebaseAppMakeGooglePlayAvailableProxy->OnSuccess.IsBound() == false )
				{
					firebaseAppMakeGooglePlayAvailableProxy->OnSuccess.Add( MakeGooglePlayAvailableProxyOnSuccess );
				}
				if( firebaseAppMakeGooglePlayAvailableProxy->OnFailure.IsBound() == false )
				{
					firebaseAppMakeGooglePlayAvailableProxy->OnFailure.Add( MakeGooglePlayAvailableProxyOnFail );
				}
			}
		}
		*/
	}
	else
	{
		FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseInitialized Failed" ) );
	}
}

bool UFireBaseManager::IsInitSuccess() const
{
#if PLATFORM_ANDROID
	return _IsInitSuccess;
#endif

	return true;
}

FString UFireBaseManager::GetDataBaseStringValue( FString dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseStringValue( TCHAR_TO_ANSI( *dbPath ) );
	}
#endif
	return "";
}

uint32 UFireBaseManager::GetDataBaseIntValue( FString dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseIntValue( TCHAR_TO_ANSI( *dbPath ) );
	}
#endif
	return 0;
}

bool UFireBaseManager::GetDataBaseCrawlingData( FString dbPath, FST_BOOTS_CRAWLING_DATA& OutCrawlingData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseCrawlingData( TCHAR_TO_ANSI( *dbPath ), OutCrawlingData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseBootsDetailData( FString dbPath, TMap<int32, FST_FOOTBALL_BOOTS_DATA>& OutBootsDetailData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseBootsDetailData( TCHAR_TO_ANSI( *dbPath ), OutBootsDetailData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseTeamData( FString dbPath, TArray<FST_TEAM_INFO_DATA>& OutTeamData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseTeamData( TCHAR_TO_ANSI( *dbPath ), OutTeamData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseStadiumData( FString dbPath, TArray<FST_STADIUM_INFO_DATA>& OutStadiumData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseStadiumData( TCHAR_TO_ANSI( *dbPath ), OutStadiumData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseMatchData( FString dbPath, TArray<FST_MATCH_DATA>& OutMatchData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseMatchData( TCHAR_TO_ANSI( *dbPath ), OutMatchData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBasePlayerData( FString dbPath, TArray<FST_PLAYER_DATA>& OutPlayerData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBasePlayerData( TCHAR_TO_ANSI( *dbPath ), OutPlayerData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseYearMvpData( FString dbPath, TArray<FST_YEAR_MVP_DATA>& OutYearMvpData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseYearMvpData( TCHAR_TO_ANSI( *dbPath ), OutYearMvpData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseYearKingData( FString dbPath, TArray<FST_YEAR_KING_DATA>& OutYearKingData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseYearKingData( TCHAR_TO_ANSI( *dbPath ), OutYearKingData );
	}
#endif

	return false;
}

bool UFireBaseManager::GetDataBaseStaffData( FString dbPath, FST_STAFF_DATA& OutStaffData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseStaffData( TCHAR_TO_ANSI( *dbPath ), OutStaffData );
	}
#endif

	return false;
}

/*
const firebase::database::DataSnapshot* UFireBaseManager::GetDataBaseSnapshot( FString dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		return _FirebaseDataBase->GetDataBaseSnapshot( TCHAR_TO_ANSI( *dbPath ) );
	}
#endif
	return nullptr;
}
*/

void UFireBaseManager::_InitFirebaseAnalytics()
{
	// Retrieving Ultimate Mobile Kit subsystem
	FUltimateMobileKit* ultimateMobileKit = FUltimateMobileKit::Get();
	// Checking if Ultimate Mobile Kit subsystem is valid
	if( ultimateMobileKit )
	{
		// Retrieving Firebase Analytics module (we recommend using Shared Pointers)
		_FirebaseAnalytics = ultimateMobileKit->GetFirebaseAnalytics();

		// Checking if Firebase Analytics module is valid
		if( _FirebaseAnalytics.IsValid() )
		{
			// Creating delegate for Init function
			FOnFirebaseAnalyticsInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseAnalyticsInitializeCompleteDelegate::CreateUObject( this, &UFireBaseManager::_OnInitFirebaseAnalyticsCompleted );

			// Calling Firebase Analytics Init function
			_FirebaseAnalytics->Init( InitializeCompleteDelegate );
			return;
		}
	}

	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseAnalytics Failed" ) );
}

void UFireBaseManager::_InitFirebaseMessaging()
{
	FUltimateMobileKit* ultimateMobileKit = FUltimateMobileKit::Get();
	if( ultimateMobileKit )
	{
		_FirebaseMessaging = ultimateMobileKit->GetFirebaseMessaging();
		if( _FirebaseMessaging.IsValid() )
		{
			FOnFirebaseMessagingInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseMessagingInitializeCompleteDelegate::CreateUObject( this, &UFireBaseManager::_OnInitFirebaseMessagingCompleted );
			_FirebaseMessaging->Init( true, InitializeCompleteDelegate );
			return;
		}
	}

	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseMessaging Failed" ) );
}

void UFireBaseManager::_InitFirebaseDataBase()
{
	FUltimateMobileKit* ultimateMobileKit = FUltimateMobileKit::Get();
	if( ultimateMobileKit )
	{
		_FirebaseDataBase = ultimateMobileKit->GetFirebaseDataBase();
		if( _FirebaseDataBase.IsValid() )
		{
			FOnFirebaseDataBaseInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseDataBaseInitializeCompleteDelegate::CreateUObject( this, &UFireBaseManager::_OnInitDataBaseCompleted );
			_FirebaseDataBase->Init( InitializeCompleteDelegate );
			return;
		}
	}

	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseDataBase Failed" ) );
}

void UFireBaseManager::_InitFirebaseRemoteConfig()
{
	FUltimateMobileKit* ultimateMobileKit = FUltimateMobileKit::Get();
	if( ultimateMobileKit )
	{
		_FirebaseRemoteConfig = ultimateMobileKit->GetFirebaseConfig();
		if( _FirebaseRemoteConfig.IsValid() )
		{
			UFirebaseVariant* defaultParameter1 = UFirebaseVariant::FirebaseStringVariant( TEXT( "MainBanner" ), TEXT( "naver.com" ) );
			_RemoteConfigDefaultParameters.Empty();
			_RemoteConfigDefaultParameters.AddUnique( defaultParameter1 );
			FOnFirebaseConfigInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseConfigInitializeCompleteDelegate::CreateUObject( this, &UFireBaseManager::_OnInitFirebaseRemoteConfigCompleted );
			_FirebaseRemoteConfig->Init( _RemoteConfigDefaultParameters, FString(), InitializeCompleteDelegate );
			return;
		}
	}

	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseRemoteConfig Failed" ) );
}

void UFireBaseManager::_SuccessInit()
{
	_UpdateRemoteConfigData();
	_UpdateDataBase();

	// 크롤링 데이터 버전 업데이트
	//UFBM_SaveGame::Get().UpdateFireBaseCrawlingDBVersion();

	// 현재 앱 버전 업데이트
	UFBM_SaveGame::Get().UpdateAppVersion();

	// 데이터 버전 업데이트
	bool isChangeVersion = UFBM_SaveGame::Get().UpdateFireBaseDetailDBVersion();

	// 데이터 업데이트
	if ( isChangeVersion )
	{
		//UFBM_SaveGame::Get().UpdateFireBaseBootsDetailData();
		UFBM_SaveGame::Get().UpdateFireBaseTeamData();
		UFBM_SaveGame::Get().UpdateFireBaseStadiumData();
		UFBM_SaveGame::Get().UpdateFireBaseMatchData();
		UFBM_SaveGame::Get().UpdateFireBasePlayerData();
		UFBM_SaveGame::Get().UpdateFireBaseYearMvpData();
		UFBM_SaveGame::Get().UpdateFireBaseYearKingData();
		UFBM_SaveGame::Get().UpdateFireBaseStaffData();
		UFBM_SaveGame::Get().UpdateRecordData();
	}

	_IsInitSuccess = true;
}

void UFireBaseManager::_OnInitFirebaseAnalyticsCompleted( bool isSuccess )
{
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseAnalytics %s" ), isSuccess ? "Success" : "Failed" );

	UKismetSystemLibrary::RegisterForRemoteNotifications();
	_InitFirebaseMessaging();
}

void UFireBaseManager::_OnInitFirebaseMessagingCompleted( bool isSuccess )
{
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseMessaging %s" ), isSuccess ? "Success" : "Failed" );

	_InitFirebaseDataBase();
}

void UFireBaseManager::_OnInitDataBaseCompleted( bool isSuccess )
{
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseDataBase %s" ), isSuccess ? "Success" : "Failed" );

	_InitFirebaseRemoteConfig();
}

void UFireBaseManager::_OnInitFirebaseRemoteConfigCompleted( bool isSuccess )
{
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FirebaseRemoteConfig %s" ), isSuccess ? "Success" : "Failed" );

	if (isSuccess)	
	{
		if( _FirebaseRemoteConfig.IsValid() )
		{
			FOnFirebaseConfigFetchCompleteDelegate FetchCompleteDelegate = FOnFirebaseConfigFetchCompleteDelegate::CreateUObject( this, &UFireBaseManager::_OnFetchFirebaseRemoteConfigCompleted );
			_FirebaseRemoteConfig->Fetch( FetchCompleteDelegate, 0);
		}
	}
}

void UFireBaseManager::_OnFetchFirebaseRemoteConfigCompleted( bool isSuccess )
{
	FBM_LOG_FUNCTION_INFO( Log, TEXT( "FetchFirebaseRemoteConfig %s" ), isSuccess ? "Success" : "Failed" );

	if( isSuccess )
	{
		_SuccessInit();
	}
}

void UFireBaseManager::_OnMakeGooglePlayAvailableProxyOnSuccess()
{
	_InitFirebaseAnalytics();
}

void UFireBaseManager::_OnMakeGooglePlayAvailableProxyOnFail()
{
	_InitFirebaseAnalytics();
}

void UFireBaseManager::_UpdateRemoteConfigData()
{
	if( _FirebaseRemoteConfig.IsValid() && _FirebaseRemoteConfig->IsInitialized() )
	{
		_FirebaseRemoteConfig->ActivateFetched();
		//if( _FirebaseRemoteConfig->ActivateFetched() )
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// 현재 버전
// 			_CurVersion = _FirebaseRemoteConfig->GetString( TEXT( "Cur_Version" ), FString());
// 			UFBM_SaveGame::Get().SetCurVersion( _CurVersion );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 서버 점검 유무
			FString servetCheckTime = _FirebaseRemoteConfig->GetString( TEXT( "ServerCheckTime" ), FString() );
			UFBM_SaveGame::Get().SetServetCheckTime( servetCheckTime );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 스크롤 클릭 감도
			int32 scrollClickSensitivity = _FirebaseRemoteConfig->GetInteger( TEXT( "ScrollClick_Sensitivity" ), FString() );
			UFBM_SaveGame::Get().SetScrollClickSensitivity( scrollClickSensitivity );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 리뷰하기
			FString reviewUrl = _FirebaseRemoteConfig->GetString( TEXT( "Review_URL" ), FString() );
			UFBM_SaveGame::Get().SetReviewURL( reviewUrl );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 회칙 URL
			FString ruleUrl = _FirebaseRemoteConfig->GetString( TEXT( "Rule_URL" ), FString() );
			UFBM_SaveGame::Get().SetRuleURL( ruleUrl );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 개발자에게 후원하기 활성화 여부
			int32 showSupport = _FirebaseRemoteConfig->GetInteger( TEXT( "Show_Support" ), FString() );
			UFBM_SaveGame::Get().SetShowSupport( showSupport );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 문의하기 이메일 주소
			FString emailAddress = _FirebaseRemoteConfig->GetString( TEXT( "SendEmail_Address" ), FString() );
			UFBM_SaveGame::Get().SetSendEmailAddress( emailAddress );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 앱 공유하기 주소
			FString shareAddress = _FirebaseRemoteConfig->GetString( TEXT( "ShareApp_Address" ), FString() );
			UFBM_SaveGame::Get().SetShareAppAddress( shareAddress );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 광고 제휴 문의 활성화 여부
			int32 showPartnership = _FirebaseRemoteConfig->GetInteger( TEXT( "Show_Partnership" ), FString() );
			UFBM_SaveGame::Get().SetShowPartnership( showPartnership );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/*
			/////////////////////////////////////////////////////////////////////////////////////////////
			// New 표시 축구화 갯수
			int32 newMaxCount = _FirebaseRemoteConfig->GetInteger( TEXT( "NewBoots_MaxCount" ), FString() );
			UFBM_SaveGame::Get().SetNewBootsMaxCount( newMaxCount );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 축구화 상세정보 Show (0 : 모두 오픈, 1 : 제품 정보만 오픈, 2 : 제품 정보, 리뷰 오픈, 3 : 제품 정보, 구매하기 오픈)
			int32 showBootsDetail = _FirebaseRemoteConfig->GetInteger( TEXT( "ShowBootsDetail" ), FString() );
			UFBM_SaveGame::Get().SetShowBootsDetail( showBootsDetail );
			/////////////////////////////////////////////////////////////////////////////////////////////
			*/

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 메인 배너 데이터
			TArray<FST_MAIN_BANNER_DATA> remoteMainBannerData;
			FString mainBannerPrefixKey = TEXT( "MainBanner_" );
			const TArray<FString> mainBannerKey = _FirebaseRemoteConfig->GetKeysByPrefix( mainBannerPrefixKey, FString() );
			for( auto& mainBannerItem : mainBannerKey )
			{
				FString mainBannerValue = _FirebaseRemoteConfig->GetString( mainBannerItem, FString() );
				if( mainBannerValue.Len() > 0 )
				{
					int32 bannerType = UKismetStringLibrary::FindSubstring( mainBannerValue, TEXT( "#" ) );
					if( bannerType != -1 )
					{
						FST_MAIN_BANNER_DATA tempBannerData;
						FString mainBannerType = UKismetStringLibrary::GetSubstring( mainBannerValue, 0, bannerType );					
						tempBannerData.BannerType = static_cast<E_BANNER_TYPE>(FCString::Atoi( *mainBannerType ));

						int32 bannerValueStartIndex = bannerType + 1;
						int32 bannerValueEndIndex = UKismetStringLibrary::FindSubstring( mainBannerValue, TEXT( "#" ), false, false, bannerValueStartIndex );
						if( bannerValueEndIndex != -1 )
						{
							tempBannerData.BannerValue = UKismetStringLibrary::GetSubstring( mainBannerValue, bannerValueStartIndex, bannerValueEndIndex - bannerValueStartIndex );
							int32 imgUrlStartIndex = bannerValueEndIndex + 1;
							int32 imgUrlEndIndex = UKismetStringLibrary::FindSubstring( mainBannerValue, TEXT( "#" ), false, false, imgUrlStartIndex );
							if( imgUrlEndIndex != -1 )
							{
								tempBannerData.BannerImgURL = UKismetStringLibrary::GetSubstring( mainBannerValue, imgUrlStartIndex, imgUrlEndIndex - imgUrlStartIndex );
								remoteMainBannerData.AddUnique( tempBannerData );
							}
						}
					}
				}
			}

			UFBM_SaveGame::Get().SetMainBannerData( remoteMainBannerData );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/*
			/////////////////////////////////////////////////////////////////////////////////////////////
			// 이달의 브랜드
			_MainBrand = _FirebaseRemoteConfig->GetString( TEXT( "MainBrand" ), FString() );
			UFBM_SaveGame::Get().SetMainBrand( _MainBrand );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 메인 커스텀 메뉴
			auto mainCustomMenuUpdate = [this]( FString customMenuKey )
			{
				FString tempUrl = _FirebaseRemoteConfig->GetString( customMenuKey, FString() );
				if( tempUrl.Len() > 0 )
				{
					tempUrl = tempUrl.Replace( TEXT( "\\n" ), TEXT( "\n" ) );
					_MainCustomMenu.AddUnique( tempUrl );
				}
			};

			_MainCustomMenu.Empty();
			mainCustomMenuUpdate( TEXT( "MainCustomMenu_01" ) );
			mainCustomMenuUpdate( TEXT( "MainCustomMenu_02" ) );
			mainCustomMenuUpdate( TEXT( "MainCustomMenu_03" ) );
			mainCustomMenuUpdate( TEXT( "MainCustomMenu_04" ) );
			mainCustomMenuUpdate( TEXT( "MainCustomMenu_05" ) );

			UFBM_SaveGame::Get().SetMainCustomMenu( _MainCustomMenu );
			/////////////////////////////////////////////////////////////////////////////////////////////
			*/

			/////////////////////////////////////////////////////////////////////////////////////////////
			// 공지사항
			TArray<FST_NOTICE_DATA> remoteNoticeData;
			FString noticePrefixKey = TEXT( "Notice_" );
			const TArray<FString> noticeKey = _FirebaseRemoteConfig->GetKeysByPrefix( noticePrefixKey, FString() );
			for( auto& noticeItem : noticeKey )
			{
				FString noticeValue = _FirebaseRemoteConfig->GetString( noticeItem, FString() );
				if( noticeValue.Len() > 0 )
				{
					noticeValue = noticeValue.Replace( TEXT( "\\n" ), TEXT( "\n" ) );
					int32 dateIndex = UKismetStringLibrary::FindSubstring( noticeValue, TEXT( "#" ) );
					if( dateIndex != -1 )
					{
						FST_NOTICE_DATA tempNoticeData;
						tempNoticeData.NoticeDate = UKismetStringLibrary::GetSubstring( noticeValue, 0, dateIndex );
						int32 titleStartIndex = dateIndex + 1;
						int32 titleEndIndex = UKismetStringLibrary::FindSubstring( noticeValue, TEXT( "#" ), false, false, titleStartIndex );
						if( titleEndIndex != -1 )
						{
							tempNoticeData.NoticeTitle = UKismetStringLibrary::GetSubstring( noticeValue, titleStartIndex, titleEndIndex - titleStartIndex );
							int32 contentsStartIndex = titleEndIndex + 1;
							int32 contentsEndIndex = UKismetStringLibrary::FindSubstring( noticeValue, TEXT( "#" ), false, false, contentsStartIndex );
							if( contentsEndIndex != -1 )
							{
								tempNoticeData.NoticeContents = UKismetStringLibrary::GetSubstring( noticeValue, contentsStartIndex, contentsEndIndex - contentsStartIndex );
								remoteNoticeData.AddUnique( tempNoticeData );
							}
						}
					}
				}
			}
			remoteNoticeData.Sort([](const FST_NOTICE_DATA& A, const FST_NOTICE_DATA& B) {
								   return A.NoticeDate > B.NoticeDate;
								   });

			UFBM_SaveGame::Get().SetNoticeData( remoteNoticeData );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////
			// FAQ
			TArray<FST_FAQ_DATA> remoteFaqData;
			FString faqPrefixKey = TEXT( "Faq_" );
			const TArray<FString> faqKey = _FirebaseRemoteConfig->GetKeysByPrefix( faqPrefixKey, FString() );
			for( auto& faqItem : faqKey )
			{
				FString faqValue = _FirebaseRemoteConfig->GetString( faqItem, FString() );
				if( faqValue.Len() > 0 )
				{
					faqValue = faqValue.Replace( TEXT( "\\n" ), TEXT( "\n" ) );
					int32 titleIndex = UKismetStringLibrary::FindSubstring( faqValue, TEXT( "#" ) );
					if( titleIndex != -1 )
					{
						FST_FAQ_DATA tempFaqData;
						tempFaqData.FaqTitle = UKismetStringLibrary::GetSubstring( faqValue, 0, titleIndex );
						int32 contentsStartIndex = titleIndex + 1;
						int32 contentsEndIndex = UKismetStringLibrary::FindSubstring( faqValue, TEXT( "#" ), false, false, contentsStartIndex );
						if( contentsEndIndex != -1 )
						{
							tempFaqData.FaqContents = UKismetStringLibrary::GetSubstring( faqValue, contentsStartIndex, contentsEndIndex - contentsStartIndex );
							remoteFaqData.AddUnique( tempFaqData );
						}
					}
				}
			}

			UFBM_SaveGame::Get().SetFaqData( remoteFaqData );
			/////////////////////////////////////////////////////////////////////////////////////////////

			/*
			/////////////////////////////////////////////////////////////////////////////////////////////
			// 출시 예정 데이터
			TArray<FST_UPCOMING_DATA> remoteUpcomingData;
			FString upcomingPrefixKey = TEXT( "Upcoming_" );
			const TArray<FString> upcomingKey = _FirebaseRemoteConfig->GetKeysByPrefix( upcomingPrefixKey, FString() );
			for( auto& upcomingItem : upcomingKey )
			{
				FString upcomingValue = _FirebaseRemoteConfig->GetString( upcomingItem, FString() );
				if( upcomingValue.Len() > 0 )
				{
					upcomingValue = upcomingValue.Replace( TEXT( "\\n" ), TEXT( "\n" ) );
					int32 dateIndex = UKismetStringLibrary::FindSubstring( upcomingValue, TEXT( "#" ) );
					if( dateIndex != -1 )
					{
						FST_UPCOMING_DATA tempUpcomingeData;
						tempUpcomingeData.UpcomingDate = UKismetStringLibrary::GetSubstring( upcomingValue, 0, dateIndex );
						int32 brandStartIndex = dateIndex + 1;
						int32 brandEndIndex = UKismetStringLibrary::FindSubstring( upcomingValue, TEXT( "#" ), false, false, brandStartIndex );
						if( brandEndIndex != -1 )
						{
							FString brandType = UKismetStringLibrary::GetSubstring( upcomingValue, brandStartIndex, brandEndIndex - brandStartIndex );
							tempUpcomingeData.UpcomingBrandType = static_cast<E_BRAND_TYPE>(FCString::Atoi( *brandType ));
							int32 nameStartIndex = brandEndIndex + 1;
							int32 nameEndIndex = UKismetStringLibrary::FindSubstring( upcomingValue, TEXT( "#" ), false, false, nameStartIndex );
							if( nameEndIndex != -1 )
							{
								tempUpcomingeData.UpcomingBootsName = UKismetStringLibrary::GetSubstring( upcomingValue, nameStartIndex, nameEndIndex - nameStartIndex );
								int32 urlStartIndex = nameEndIndex + 1;
								int32 urlEndIndex = UKismetStringLibrary::FindSubstring( upcomingValue, TEXT( "#" ), false, false, urlStartIndex );
								if( urlEndIndex != -1 )
								{
									tempUpcomingeData.UpcomingURL = UKismetStringLibrary::GetSubstring( upcomingValue, urlStartIndex, urlEndIndex - urlStartIndex );
									remoteUpcomingData.AddUnique( tempUpcomingeData );
								}
							}
						}
					}
				}
			}
			remoteUpcomingData.Sort( []( const FST_UPCOMING_DATA& A, const FST_UPCOMING_DATA& B )
								   {
									   return A.UpcomingDate < B.UpcomingDate;
								   } );

			UFBM_SaveGame::Get().SetUpcomingData( remoteUpcomingData );
			/////////////////////////////////////////////////////////////////////////////////////////////
			*/

			UFBM_SaveGame::Get().SaveFile();
			FBM_LOG_FUNCTION_INFO( Log, TEXT( "UpdateRemoteConfigData Success" ) );
		}
// 		else
// 		{
// 			FBM_LOG_FUNCTION_INFO( Log, TEXT( "UpdateRemoteConfigData Failed" ) );
// 		}
	}
}

void UFireBaseManager::_UpdateDataBase()
{
	if( _FirebaseDataBase.IsValid() && _FirebaseDataBase->IsInitialized() )
	{
		_FirebaseDataBase->AddChildListener();
	}
}
