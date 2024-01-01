// Fill out your copyright notice in the Description page of Project Settings.


#include "DataBase_CKH/FirebaseDataBase_CKH.h"
#include "DataBase_CKH/DataBaseInitialize_CKH.h"
#include "UltimateMobileKitSettings.h"
#include "UltimateMobileKit.h"
#include "Util/FBMUtil.h"

FirebaseDataBase_CKH::FirebaseDataBase_CKH()
{
}

FirebaseDataBase_CKH::~FirebaseDataBase_CKH()
{
}

void FirebaseDataBase_CKH::Init( const FOnFirebaseDataBaseInitializeCompleteDelegate& Delegate /*= FOnFirebaseDataBaseCompleteDelegate() */ )
{
	if( IsInitialized() )
	{
		Delegate.ExecuteIfBound( true );
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if( UltimateMobileKit )
	{
		auto QueryTask = new FFirebaseDataBaseInitialize_CKH( UltimateMobileKit->Get(), Delegate );
		UltimateMobileKit->QueueAsyncTask( QueryTask );

		return;
	}

	Delegate.ExecuteIfBound( false );
}

void FirebaseDataBase_CKH::Shutdown()
{
	UE_LOG( LogUltimateMobileKit, Display, TEXT( "Firebase DataBase Shutdown" ) );

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	//FirebaseNativeDataBasePtr = nullptr;
#endif
}

const bool FirebaseDataBase_CKH::IsInitialized() const
{
	return bInitialized;
}

void FirebaseDataBase_CKH::SetInitialized( bool Initialized )
{
	bInitialized = Initialized;

	if( bInitialized )
	{
		UE_LOG( LogUltimateMobileKit, Display, TEXT( "Firebase DataBase is initialized successfully" ) );
	}
	else
	{
		UE_LOG( LogUltimateMobileKit, Display, TEXT( "Firebase DataBase is not initialized" ) );
	}
}

const bool FirebaseDataBase_CKH::RegisterService()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if( UltimateMobileKit )
	{
		FirebaseNativeDataBasePtr = MakeShareable( firebase::database::Database::GetInstance( UltimateMobileKit->GetFirebaseApp()->GetFirebaseNativeApp().Get() ) );

		if( FirebaseNativeDataBasePtr.IsValid() )
		{
			UE_LOG( LogUltimateMobileKit, Display, TEXT( "Firebase Native DataBase service registered" ) );

			return true;
		}
	}
#endif

	return false;
}

void FirebaseDataBase_CKH::AddChildListener()
{
	/*
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	if( IsInitialized() )
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if( UltimateMobileKit )
		{
			FFirebaseNativeDataBasePtr NativeDataBase = UltimateMobileKit->GetFirebaseDataBase()->GetFirebaseNativeDataBase();

			if( NativeDataBase.IsValid() )
			{
				NativeDataBase->GetReference().Child("BootsInfo").AddChildListener( new firebase::database::ChildListener() {
					public void OnChildAdded( const DataSnapshot & snapshot, const char* previous_sibling_key ) {
					   //Variant addValue = snapshot.value();
					   //addValue.int64_value();
					   _TestKey = snapshot.key_string();
				    }
					public void OnChildChanged( const DataSnapshot& snapshot, const char* previous_sibling_key ) {

					}
					public void OnChildMoved( const DataSnapshot& snapshot, const char* previous_sibling_key ) {

					}
					public OnChildRemoved( const DataSnapshot& snapshot ) {

					}
					public void OnCancelled( const Error& error, const char* error_message ) {

					}
				} );

			}
		}
	}
#endif
*/
}

uint32 FirebaseDataBase_CKH::GetDataBaseIntValue( const char* dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			//firebase::Future<firebase::database::DataSnapshot> result = dbref.Child( "AQ4174" ).Child( "Price" ).Child( "HMall" ).GetValue();
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					const firebase::database::DataSnapshot& snapshot = *result.result();
					return snapshot.value().int64_value();
				}
			}
		}
	}

	return 0;
#endif

	return 0;
}

FString FirebaseDataBase_CKH::GetDataBaseStringValue( const char* dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			//firebase::Future<firebase::database::DataSnapshot> result = dbref.Child( "AQ4174" ).Child( "Price" ).Child( "HMall" ).GetValue();
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					const firebase::database::DataSnapshot& snapshot = *result.result();
					return snapshot.value().string_value();
					//return snapshot.value().AsString();
					//UE_LOG( LogUltimateMobileKit, Display, TEXT( "CKH GetDataBaseValue Complete : %s" ), *FString( snapshot.value().string_value() ) );
				}
			}
		}
	}

	return "";
#endif

	return "";
}

bool FirebaseDataBase_CKH::GetDataBaseCrawlingData( const char* dbPath, FST_BOOTS_CRAWLING_DATA& OutCrawlingData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					auto getCrawlingData = [this, &OutCrawlingData]( const char* shopName, const firebase::database::DataSnapshot& bootsDataSnapshot, bool isDomesticShop ) -> bool
					{
						int32 priceData = 0;
						FString urlData;
						if ( isDomesticShop )
						{
							if( bootsDataSnapshot.HasChild( "Price" ) )
							{
								if( bootsDataSnapshot.Child( "Price" ).HasChild( shopName ) )
								{
									priceData = bootsDataSnapshot.Child( "Price" ).Child( shopName ).value().int64_value();
								}
							}
							if( bootsDataSnapshot.HasChild( "URL" ) )
							{
								if( bootsDataSnapshot.Child( "URL" ).HasChild( shopName ) )
								{
									urlData = bootsDataSnapshot.Child( "URL" ).Child( shopName ).value().string_value();
								}
							}
						}
						else
						{
							if( bootsDataSnapshot.HasChild( "Price_GLOBAL" ) )
							{
								if( bootsDataSnapshot.Child( "Price_GLOBAL" ).HasChild( shopName ) )
								{
									priceData = bootsDataSnapshot.Child( "Price_GLOBAL" ).Child( shopName ).value().int64_value();
								}
							}
							if( bootsDataSnapshot.HasChild( "URL_GLOBAL" ) )
							{
								if( bootsDataSnapshot.Child( "URL_GLOBAL" ).HasChild( shopName ) )
								{
									urlData = bootsDataSnapshot.Child( "URL_GLOBAL" ).Child( shopName ).value().string_value();
								}
							}
						}

						if( priceData > 0 && !urlData.IsEmpty() )
						{
							FST_BOOTS_CRAWLING_INFO_DATA infoData;
							infoData.UrlData = urlData;
							infoData.PriceData = priceData;
							infoData.IsDomestic = isDomesticShop;
							OutCrawlingData.CrawlingInfo.Add( UFBMUtil::ShopNameEnum( shopName ), infoData );
							return true;
						}

						return false;
					};

					auto getLowPriceData = [this, &OutCrawlingData]( const firebase::database::DataSnapshot& bootsDataSnapshot ) -> bool
					{
						bool isSuccess = false;
						if( bootsDataSnapshot.HasChild( "LowPrice" ) )
						{
							if( bootsDataSnapshot.Child( "LowPrice" ).HasChild( "Days" ) )
							{
								for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.Child( "LowPrice" ).Child( "Days" ).children() )
								{
									OutCrawlingData.LowPriceDay.Add( snap.key(), snap.value().int64_value() );
								}

								isSuccess = true;
							}
							if( bootsDataSnapshot.Child( "LowPrice" ).HasChild( "Week" ) )
							{
								for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.Child( "LowPrice" ).Child( "Week" ).children() )
								{
									OutCrawlingData.LowPriceWeek.Add( snap.key(), snap.value().int64_value() );
								}

								isSuccess = true;
							}
							if( bootsDataSnapshot.Child( "LowPrice" ).HasChild( "Month" ) )
							{
								for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.Child( "LowPrice" ).Child( "Month" ).children() )
								{
									OutCrawlingData.LowPriceMonth.Add( snap.key(), snap.value().int64_value() );
								}

								isSuccess = true;
							}
						}

						return isSuccess;
					};

					/////////////////////////////////////////////////////////////////////////////////////////
					// 쇼핑몰 데이터 가져오기
					bool isCrawlingSuccess = false;
					bool isLowPriceDataSuccess = false;
					const firebase::database::DataSnapshot& crawlingDataSnapshot = *result.result();
					// 국내
					isCrawlingSuccess |= getCrawlingData( "HMall", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "GMarket", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "Auction", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "ST11", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "SSG", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "Lotte", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "NSMall", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "AKMall", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "GSShop", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "HIMart", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "HalfClub", crawlingDataSnapshot, true );
					isCrawlingSuccess |= getCrawlingData( "WMP", crawlingDataSnapshot, true );

					// 해외
					isCrawlingSuccess |= getCrawlingData( "PDS", crawlingDataSnapshot, false );
					isCrawlingSuccess |= getCrawlingData( "PDS_US", crawlingDataSnapshot, false );
					isCrawlingSuccess |= getCrawlingData( "SOCCER", crawlingDataSnapshot, false );
					isCrawlingSuccess |= getCrawlingData( "UNI", crawlingDataSnapshot, false );
					////////////////////////////////////////////////////////////////////////////////////////

					////////////////////////////////////////////////////////////////////////////////////////
					// 최저가 데이터 가져오기
					isLowPriceDataSuccess = getLowPriceData( crawlingDataSnapshot );
					////////////////////////////////////////////////////////////////////////////////////////

					return isCrawlingSuccess;
					/*
					FString priceHMall;
					FString urlHMall;
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					if( bootsDataSnapshot.HasChild( "Price" ) )
					{
						if( bootsDataSnapshot.Child( "Price" ).HasChild( "HMall" ) )
						{
							priceHMall = bootsDataSnapshot.Child( "Price" ).Child( "HMall" ).value().string_value();
						}
					}
					if( bootsDataSnapshot.HasChild( "URL" ) )
					{
						if( bootsDataSnapshot.Child( "URL" ).HasChild( "HMall" ) )
						{
							urlHMall = bootsDataSnapshot.Child( "URL" ).Child( "HMall" ).value().string_value();
						}
					}

					if( !priceHMall.IsEmpty() && !urlHMall.IsEmpty() )
					{
						FST_BOOTS_CRAWLING_INFO_DATA infoData;
						infoData.UrlData = urlHMall;
						infoData.PriceData = priceHMall;
						OutCrawlingData.CrawlingInfo.Add( E_CRAWLING_WEBPAGE::HMALL, infoData );
						return true;
					}
					*/
					/////////////////////////////////////////////////////////////////////////////////////////
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseBootsDetailData( const char* dbPath, TMap<int32, FST_FOOTBALL_BOOTS_DATA>& OutBootsDetailData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 축구화 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_FOOTBALL_BOOTS_DATA bootsDetailData;
						if( snap.HasChild( "BootsIndex" ) )
						{
							bootsDetailData.BootsIndex = snap.Child( "BootsIndex" ).value().int64_value();
						}
						else
						{
							continue;
						}
						if( snap.HasChild( "BootsName" ) )
						{
							bootsDetailData.BootsName = FString( UTF8_TO_TCHAR( snap.Child( "BootsName" ).value().string_value() ) );
						}
						if( snap.HasChild( "BrandType" ) )
						{
							bootsDetailData.BrandType = static_cast<E_BRAND_TYPE>(snap.Child( "BrandType" ).value().int64_value());
						}
						if( snap.HasChild( "CollectionNum" ) )
						{
							bootsDetailData.CollectionNum = snap.Child( "CollectionNum" ).value().int64_value();
						}
						if( snap.HasChild( "CollectionType" ) )
						{
							bootsDetailData.CollectionType = static_cast<E_COLLECTION_TYPE>(snap.Child( "CollectionType" ).value().int64_value());
						}
						if( snap.HasChild( "GroundType" ) )
						{
							FString groundType = snap.Child( "GroundType" ).value().string_value();
							TArray<FString> groundTypeArray = {};
							groundType.ParseIntoArray( groundTypeArray, TEXT( "," ) );

							for (FString& ground : groundTypeArray )
							{
								bootsDetailData.GroundTypes.AddUnique( static_cast<E_GROUND_TYPE>(FCString::Atoi( *ground )) );
							}
						}
						if( snap.HasChild( "IconURL" ) )
						{
							bootsDetailData.IconURL = snap.Child( "IconURL" ).value().string_value();
						}
						if( snap.HasChild( "ModelType" ) )
						{
							bootsDetailData.ModelType = static_cast<E_MODEL_TYPE>(snap.Child( "ModelType" ).value().int64_value());
						}
						if( snap.HasChild( "OtherProductID" ) )
						{
							for( firebase::database::DataSnapshot& snapOtherProductID : snap.Child( "OtherProductID" ).children() )
							{
								bootsDetailData.Other_ProductID.AddUnique( snapOtherProductID.value().string_value());		
							}	
						}
						if( snap.HasChild( "OtherProductURL" ) )
						{
							for( firebase::database::DataSnapshot& snapOtherProductURL : snap.Child( "OtherProductURL" ).children() )
							{
								bootsDetailData.Other_ProductURL.Add( snapOtherProductURL.key(), snapOtherProductURL.value().string_value() );
							}
						}
						if( snap.HasChild( "OtherReleaseDate" ) )
						{
							for( firebase::database::DataSnapshot& snapOtherReleaseDate : snap.Child( "OtherReleaseDate" ).children() )
							{
								bootsDetailData.Other_ReleaseDate.Add( snapOtherReleaseDate.key(), snapOtherReleaseDate.value().int64_value() );
							}
						}
						if( snap.HasChild( "OtherPrice" ) )
						{
							for( firebase::database::DataSnapshot& snapOtherPrice : snap.Child( "OtherPrice" ).children() )
							{
								bootsDetailData.Other_Price.Add( snapOtherPrice.key(), snapOtherPrice.value().int64_value() );
							}
						}
						if( snap.HasChild( "SiloType" ) )
						{
							bootsDetailData.SiloType = static_cast<E_SILO_TYPE>(snap.Child( "SiloType" ).value().int64_value());
						}
						if( snap.HasChild( "StudType" ) )
						{
							bootsDetailData.StudsType = static_cast<E_STUDS_TYPE>(snap.Child( "StudType" ).value().int64_value());
						}
						if( snap.HasChild( "UpperType" ) )
						{
							bootsDetailData.UpperType = static_cast<E_UPPER_TYPE>(snap.Child( "UpperType" ).value().int64_value());
						}
						if( snap.HasChild( "Weight" ) )
						{
							bootsDetailData.Weight = snap.Child( "Weight" ).value().int64_value();
						}
						if( snap.HasChild( "Price" ) )
						{
							bootsDetailData.Price = snap.Child( "Price" ).value().int64_value();
						}
						if( snap.HasChild( "ReleaseDate" ) )
						{
							bootsDetailData.ReleaseDate = snap.Child( "ReleaseDate" ).value().int64_value();
						}
						if( snap.HasChild( "ProductID" ) )
						{
							bootsDetailData.ProductID = snap.Child( "ProductID" ).value().string_value();
						}
						if( snap.HasChild( "ReviewData" ) )
						{
							for( firebase::database::DataSnapshot& snapReviewData : snap.Child( "ReviewData" ).children() )
							{
								FST_REVIEW_DATA tempReviewData;
								if( snapReviewData.HasChild( "Title" ) )
								{									
									tempReviewData.Title = FString( UTF8_TO_TCHAR( snapReviewData.Child( "Title" ).value().string_value() ) );
								}
								if( snapReviewData.HasChild( "Source" ) )
								{
									tempReviewData.Source = FString( UTF8_TO_TCHAR( snapReviewData.Child( "Source" ).value().string_value() ) );
								}
								if( snapReviewData.HasChild( "ImgURL" ) )
								{
									tempReviewData.ImgURL = snapReviewData.Child( "ImgURL" ).value().string_value();
								}
								if( snapReviewData.HasChild( "ReviewURL" ) )
								{
									tempReviewData.ReviewURL = snapReviewData.Child( "ReviewURL" ).value().string_value();
								}
								bootsDetailData.ReviewData.Add( tempReviewData );
							}
						}
						bootsDetailData.SortReleaseDate();
						OutBootsDetailData.Add( bootsDetailData.BootsIndex, bootsDetailData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseTeamData( const char* dbPath, TArray<FST_TEAM_INFO_DATA>& OutTeamData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 팀 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_TEAM_INFO_DATA teamInfoData;
						if( snap.HasChild( "TeamName" ) )
						{
							teamInfoData.TeamName = FString( UTF8_TO_TCHAR( snap.Child( "TeamName" ).value().string_value() ) );
						}
						if( snap.HasChild( "TeamLogoURL" ) )
						{
							teamInfoData.TeamLogoURL = FString( UTF8_TO_TCHAR( snap.Child( "TeamLogoURL" ).value().string_value() ) );
						}					
						OutTeamData.Add( teamInfoData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseStadiumData( const char* dbPath, TArray<FST_STADIUM_INFO_DATA>& OutStadiumData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 구장 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_STADIUM_INFO_DATA stadiumInfoData;
						if( snap.HasChild( "StadiumName" ) )
						{
							stadiumInfoData.StadiumName = FString( UTF8_TO_TCHAR( snap.Child( "StadiumName" ).value().string_value() ) );
						}
						OutStadiumData.Add( stadiumInfoData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseMatchData( const char* dbPath, TArray<FST_MATCH_DATA>& OutMatchData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 경기 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_MATCH_DATA matchData;
						if( snap.HasChild( "MatchType" ) )
						{
							matchData.MatchType = static_cast<E_MATCH_TYPE>(snap.Child( "MatchType" ).value().int64_value());
						}
						if( snap.HasChild( "InfoType" ) )
						{
							matchData.InfoType = static_cast<E_MATCH_INFO_TYPE>(snap.Child( "InfoType" ).value().int64_value());
						}
						if( snap.HasChild( "HomeTeamName" ) )
						{
							matchData.HomeTeamName = FString( UTF8_TO_TCHAR( snap.Child( "HomeTeamName" ).value().string_value() ) );
						}
						if( snap.HasChild( "AwayTeamName" ) )
						{
							matchData.AwayTeamName = FString( UTF8_TO_TCHAR( snap.Child( "AwayTeamName" ).value().string_value() ) );
						}
						if( snap.HasChild( "Comment" ) )
						{
							matchData.Comment = FString( UTF8_TO_TCHAR( snap.Child( "Comment" ).value().string_value() ) );
						}
						if( snap.HasChild( "MatchDate" ) )
						{
							matchData.MatchDate = FString( UTF8_TO_TCHAR( snap.Child( "MatchDate" ).value().string_value() ) );
						}
						if( snap.HasChild( "MatchTime" ) )
						{
							matchData.MatchTime = FString( UTF8_TO_TCHAR( snap.Child( "MatchTime" ).value().string_value() ) );
						}
						if( snap.HasChild( "HomeGoal" ) )
						{
							matchData.HomeGoal = snap.Child( "HomeGoal" ).value().int64_value();
						}
						if( snap.HasChild( "AwayGoal" ) )
						{
							matchData.AwayGoal = snap.Child( "AwayGoal" ).value().int64_value();
						}
						if( snap.HasChild( "HomeGoalInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapHomeGoalData : snap.Child( "HomeGoalInfo" ).children() )
							{
								FString valueData;
								if( snapHomeGoalData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapHomeGoalData.Child( "Name" ).value().string_value() ) );
								}
								matchData.HomeGoalInfo.Add( valueData );
							}
						}
						if( snap.HasChild( "AwayGoalInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapAwayGoalData : snap.Child( "AwayGoalInfo" ).children() )
							{
								FString valueData;
								if( snapAwayGoalData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapAwayGoalData.Child( "Name" ).value().string_value() ) );
								}
								matchData.AwayGoalInfo.Add( valueData );
							}
						}
						if( snap.HasChild( "HomeAssistInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapHomeAssistData : snap.Child( "HomeAssistInfo" ).children() )
							{
								FString valueData;
								if( snapHomeAssistData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapHomeAssistData.Child( "Name" ).value().string_value() ) );
								}
								matchData.HomeAssistInfo.Add( valueData );
							}
						}
						if( snap.HasChild( "AwayAssistInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapAwayAssistData : snap.Child( "AwayAssistInfo" ).children() )
							{
								FString valueData;
								if( snapAwayAssistData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapAwayAssistData.Child( "Name" ).value().string_value() ) );
								}
								matchData.AwayAssistInfo.Add( valueData );
							}
						}
						if( snap.HasChild( "HomePlayerInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapHomePlayerData : snap.Child( "HomePlayerInfo" ).children() )
							{
								FString valueData;
								if( snapHomePlayerData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapHomePlayerData.Child( "Name" ).value().string_value() ) );
								}
								matchData.HomePlayerInfo.Add( valueData );
							}
						}
						if( snap.HasChild( "AwayPlayerInfo" ) )
						{
							for( firebase::database::DataSnapshot& snapAwayPlayerData : snap.Child( "AwayPlayerInfo" ).children() )
							{
								FString valueData;
								if( snapAwayPlayerData.HasChild( "Name" ) )
								{
									valueData = FString( UTF8_TO_TCHAR( snapAwayPlayerData.Child( "Name" ).value().string_value() ) );
								}
								matchData.AwayPlayerInfo.Add( valueData );
							}
						}						

						OutMatchData.Add( matchData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBasePlayerData( const char* dbPath, TArray<FST_PLAYER_DATA>& OutPlayerData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 선수 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_PLAYER_DATA playerData;
						if( snap.HasChild( "PlayerName" ) )
						{
							playerData.PlayerName = FString( UTF8_TO_TCHAR( snap.Child( "PlayerName" ).value().string_value() ) );
						}
						if( snap.HasChild( "TeamName" ) )
						{
							playerData.TeamName = FString( UTF8_TO_TCHAR( snap.Child( "TeamName" ).value().string_value() ) );
						}
						if( snap.HasChild( "PictureURL" ) )
						{
							playerData.PictureURL = FString( UTF8_TO_TCHAR( snap.Child( "PictureURL" ).value().string_value() ) );
						}
						if( snap.HasChild( "MvpNum" ) )
						{
							playerData.MvpNum = snap.Child( "MvpNum" ).value().int64_value();
						}
						if( snap.HasChild( "TopScorerNum" ) )
						{
							playerData.TopScorerNum = snap.Child( "TopScorerNum" ).value().int64_value();
						}
						if( snap.HasChild( "TopAssistNum" ) )
						{
							playerData.TopAssistNum = snap.Child( "TopAssistNum" ).value().int64_value();
						}
						if( snap.HasChild( "TopAttendanceNum" ) )
						{
							playerData.TopAttendanceNum = snap.Child( "TopAttendanceNum" ).value().int64_value();
						}
						if( snap.HasChild( "TopPointNum" ) )
						{
							playerData.TopPointNum = snap.Child( "TopPointNum" ).value().int64_value();
						}
						if( snap.HasChild( "TopDefenceNum" ) )
						{
							playerData.TopDefenceNum = snap.Child( "TopDefenceNum" ).value().int64_value();
						}

						OutPlayerData.Add( playerData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseYearMvpData( const char* dbPath, TArray<FST_YEAR_MVP_DATA>& OutYearMvpData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// MVP 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_YEAR_MVP_DATA mvpData;
						if( snap.HasChild( "Mvp1" ) )
						{
							mvpData.Name.Add( FString( UTF8_TO_TCHAR( snap.Child( "Mvp1" ).value().string_value() ) ) );
						}
						if( snap.HasChild( "Mvp2" ) )
						{
							mvpData.Name.Add( FString( UTF8_TO_TCHAR( snap.Child( "Mvp2" ).value().string_value() ) ) );
						}
						if( snap.HasChild( "Mvp3" ) )
						{
							mvpData.Name.Add( FString( UTF8_TO_TCHAR( snap.Child( "Mvp3" ).value().string_value() ) ) );
						}
						if( snap.HasChild( "Year" ) )
						{
							mvpData.Year = FString( UTF8_TO_TCHAR( snap.Child( "Year" ).value().string_value() ) );
						}

						OutYearMvpData.Add( mvpData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseYearKingData( const char* dbPath, TArray<FST_YEAR_KING_DATA>& OutYearKingData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// 랭커 데이터 가져오기
					const firebase::database::DataSnapshot& bootsDataSnapshot = *result.result();
					for( firebase::database::DataSnapshot& snap : bootsDataSnapshot.children() )
					{
						FST_YEAR_KING_DATA kingData;
						if( snap.HasChild( "Goal" ) )
						{
							kingData.GoalKing = FString( UTF8_TO_TCHAR( snap.Child( "Goal" ).value().string_value() ) );
						}
						if( snap.HasChild( "Assist" ) )
						{
							kingData.AssistKing = FString( UTF8_TO_TCHAR( snap.Child( "Assist" ).value().string_value() ) );
						}
						if( snap.HasChild( "TotalPoint" ) )
						{
							kingData.TotalPointKing = FString( UTF8_TO_TCHAR( snap.Child( "TotalPoint" ).value().string_value() ) );
						}
						if( snap.HasChild( "Attendance" ) )
						{
							kingData.AttendanceKing = FString( UTF8_TO_TCHAR( snap.Child( "Attendance" ).value().string_value() ) );
						}
						if( snap.HasChild( "Defence" ) )
						{
							kingData.DefenceKing = FString( UTF8_TO_TCHAR( snap.Child( "Defence" ).value().string_value() ) );
						}
						if( snap.HasChild( "Year" ) )
						{
							kingData.Year = FString( UTF8_TO_TCHAR( snap.Child( "Year" ).value().string_value() ) );
						}

						OutYearKingData.Add( kingData );
					}
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

bool FirebaseDataBase_CKH::GetDataBaseStaffData( const char* dbPath, FST_STAFF_DATA& OutStaffData )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{
					/////////////////////////////////////////////////////////////////////////////////////////
					// Staff 데이터 가져오기
					const firebase::database::DataSnapshot& staffDataSnapshot = *result.result();
					if( staffDataSnapshot.HasChild( "Owner" ) )
					{
						OutStaffData.Owner = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "Owner" ).value().string_value() ) );
					}
					if( staffDataSnapshot.HasChild( "GeneralManager" ) )
					{
						OutStaffData.GeneralManager = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "GeneralManager" ).value().string_value() ) );
					}
					if( staffDataSnapshot.HasChild( "HeadCoach" ) )
					{
						OutStaffData.HeadCoach = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "HeadCoach" ).value().string_value() ) );
					}
					if( staffDataSnapshot.HasChild( "SecondCoach" ) )
					{
						OutStaffData.SecondCoach = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "SecondCoach" ).value().string_value() ) );
					}
					if( staffDataSnapshot.HasChild( "ThirdCoach" ) )
					{
						OutStaffData.ThirdCoach = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "ThirdCoach" ).value().string_value() ) );
					}
					if( staffDataSnapshot.HasChild( "FourthCoach" ) )
					{
						OutStaffData.FourthCoach = FString( UTF8_TO_TCHAR( staffDataSnapshot.Child( "FourthCoach" ).value().string_value() ) );
					}					
					////////////////////////////////////////////////////////////////////////////////////////

					return true;
				}
			}
		}
	}

	return false;
#endif
	return false;
}

/*
const firebase::database::DataSnapshot* FirebaseDataBase_CKH::GetDataBaseSnapshot( const char* dbPath )
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FFirebaseNativeDataBasePtr NativeDataBase = GetFirebaseNativeDataBase();
	if( NativeDataBase.IsValid() )
	{
		firebase::database::DatabaseReference dbref = NativeDataBase->GetReference( dbPath );
		if( dbref.is_valid() )
		{
			firebase::Future<firebase::database::DataSnapshot> result = dbref.GetValue();
			_WaitForCompletion( result, dbPath );
			if( result.status() != firebase::kFutureStatusPending )
			{
				if( result.status() != firebase::kFutureStatusComplete )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned an invalid result." ) );
				}
				else if( result.error() != firebase::database::kErrorNone )
				{
					UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: GetValue() returned error %d: %s" ), result.error(), *FString( result.error_message() ) );
				}
				else
				{			
					return result.result();
				}
			}
		}
	}

	return nullptr;
#endif

	return nullptr;
}
*/

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
void FirebaseDataBase_CKH::_WaitForCompletion( const firebase::FutureBase& future, const char* name )
{
	while( future.status() == firebase::kFutureStatusPending )
	{
		FPlatformProcess::Sleep( 0.1 );
		//UKismetSystemLibrary::Delay();
	}
	if( future.status() != firebase::kFutureStatusComplete )
	{
		UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: %s returned an invalid result." ), *FString( name ) );
	}
	else if( future.error() != 0 )
	{		
		UE_LOG( LogUltimateMobileKit, Display, TEXT( "ERROR: %s returned error %d: %s" ), *FString( name ), future.error(), *FString( future.error_message() ) );
	}
}
#endif
