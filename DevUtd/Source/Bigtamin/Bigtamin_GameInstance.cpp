// Fill out your copyright notice in the Description page of Project Settings.

#include "Bigtamin_GameInstance.h"
#include "Bigtamin.h"
#include "FBM_SaveGame.h"
#include "PlayerController/Bigtamin_PlayerController.h"
#include "GameMode/BGameMode.h"
#include "UI/BWidget_NewMain.h"
#include "UI/BWidget_Warning.h"
#include "UI/Common/BWidget_Loading.h"
#include "Kismet/KismetStringLibrary.h"
//#include "MoviePlayer.h"

/** Global GameInstance pointer */
UGameInstanceProxy GInst;

UBigtamin_GameInstance::UBigtamin_GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GInst = this;
#if PLATFORM_ANDROID
	bIsSaveFileSuccess = false;
#else
	bIsSaveFileSuccess = true;
#endif
}

UBigtamin_GameInstance::~UBigtamin_GameInstance()
{
	
}

void UBigtamin_GameInstance::Init()
{
	Super::Init();

	if( _GlobalAccessMgrClass )
	{
		_GlobalAccessMgr = NewObject<UGlobalAccessMgr>( this, _GlobalAccessMgrClass );
	}
	else
	{
		_GlobalAccessMgr = NewObject<UGlobalAccessMgr>( this, UGlobalAccessMgr::StaticClass() );
	}

	verify( _GlobalAccessMgr );
	_GlobalAccessMgr->Startup();

	UFBM_SaveGame::Get().IsTodayFirstLogin( true );

	InitDataTable();

	_DownLoadBootsImage.Empty();
	_DownLoadLogoImage.Empty();
	_DownLoadPlayerImage.Empty();

	///// Test
	///////////////////////////////////

	SetCurMode(E_MODE::E_MODE_NONE);
	SetCurSelectBootsIndex( 1 );

	_BackInputStack.Empty( SIZE_WIDGET_STACK );
}

void UBigtamin_GameInstance::Shutdown()
{
	_GlobalAccessMgr->Shutdown();

	UGameInstance::Shutdown();
}

ABHUDBase* UBigtamin_GameInstance::GetHUDBase()
{
	ABHUDBase* bHud = nullptr;

	APlayerController* playerController = GetFirstLocalPlayerController( GetWorld() );
	if( playerController )
	{
		AHUD* hud = playerController->GetHUD();
		if( hud )
			bHud = Cast<ABHUDBase>( hud );
	}

	return bHud;
}

class ABGameMode* UBigtamin_GameInstance::GetGameMode()
{
	return GetWorld() ? Cast<ABGameMode>( GetWorld()->GetAuthGameMode() ) : nullptr;
}

class ABigtamin_PlayerController* UBigtamin_GameInstance::GetPlayerController()
{
	APlayerController* getController = GetFirstLocalPlayerController( GetWorld() );
	if( getController )
		return Cast<ABigtamin_PlayerController>( getController );

	return nullptr;
}

void UBigtamin_GameInstance::InitDataTable()
{
	_StringInfoTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/DataTable/DataTable_StringInfo.DataTable_StringInfo'")));
	_SurveyInfoTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/DataTable/DataTable_SurveyInfo.DataTable_SurveyInfo'")));
	_BootsInfoTable = Cast<UDataTable>( StaticLoadObject( UDataTable::StaticClass(), NULL, TEXT( "DataTable'/Game/DataTable/DataTable_FootBallBootsInfo.DataTable_FootBallBootsInfo'" ) ) );
}

FST_StringInfoData UBigtamin_GameInstance::GetStringInfoRowByName(FName nameIndex, bool& bResult)
{
	bResult = false;

	if ( _StringInfoTable != NULL)
	{
		FST_StringInfoData* data = _StringInfoTable->FindRow<FST_StringInfoData>(nameIndex, "", false);
		if (data != NULL)
		{
			bResult = true;
			return *data;
		}
	}

	return FST_StringInfoData();
}

FText UBigtamin_GameInstance::GetStringByTable(int32 nStrIndex)
{
	bool bIsResult;
	FName nameIndex = FName(*FString::FromInt(nStrIndex));
	FST_StringInfoData fStringInfoData = GetStringInfoRowByName(nameIndex, bIsResult);
	if (bIsResult)
	{
		return fStringInfoData.tStr;
	}
	else
	{
		return FText::FromString(FString::Printf(TEXT("%d Failed StrIndex"), nStrIndex));
	}
}

FST_SurveyInfoData UBigtamin_GameInstance::GetSurveyInfoRowByName( int32 nSurveyIndex, bool& bResult )
{
	bResult = false;
	FName nameIndex = FName( *FString::FromInt( nSurveyIndex ) );

	if ( _SurveyInfoTable != NULL)
	{
		FST_SurveyInfoData* data = _SurveyInfoTable->FindRow<FST_SurveyInfoData>(nameIndex, "", false);
		if (data != NULL)
		{
			bResult = true;
			return *data;
		}
	}

	return FST_SurveyInfoData();
}

FST_FootBallBootsData UBigtamin_GameInstance::GetBootsInfo( int32 bootsIndex, bool& bResult )
{
	bResult = false;
	FName bootsIndexName = FName( *FString::FromInt( bootsIndex ) );

	if( _BootsInfoTable != NULL )
	{
		FST_FootBallBootsData* data = _BootsInfoTable->FindRow<FST_FootBallBootsData>( bootsIndexName, "", false );
		if( data != NULL )
		{
			bResult = true;
			return *data;
		}
	}

	return FST_FootBallBootsData();
}

void UBigtamin_GameInstance::SearchBootsInfo( FText searchText, TArray<int>& OUT_BootsInexInfoByBrand )
{
#if DB_BOOTS_DATA
	UFBM_SaveGame::Get().SearchBootsInfo_DB( searchText, OUT_BootsInexInfoByBrand );
#else
	TArray<FST_FootBallBootsData*> arAllRows;
	_BootsInfoTable->GetAllRows<FST_FootBallBootsData>( "", arAllRows );

	FString searchString = searchText.ToString();
	for( int32 nIndex = 0; nIndex < arAllRows.Num(); ++nIndex )
	{
		// 브랜드 검색
		/*
		FString brandString = UFBMUtil::BrandNameText( arAllRows[nIndex]->eBrandType ).ToString();
		int32 findIndexBrand = searchString.Find( brandString );
		if( findIndexBrand != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
			continue;
		}
		*/
		// Name 검색
		FString nameString = arAllRows[nIndex]->BootsName.ToString();
		int32 findIndex = nameString.Find( searchString );
		if( findIndex != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
			continue;
		}
		else
		{
			int32 searchSuccessNum = 0;
			TArray<FString> searchParse = UKismetStringLibrary::ParseIntoArray( searchString );
			for( auto& parseWord : searchParse )
			{
				int32 findIndexParse = nameString.Find( parseWord );
				if( findIndexParse != INDEX_NONE )
				{
					searchSuccessNum++;
					continue;
				}
			}

			if( searchSuccessNum == searchParse.Num() )
			{
				OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
				continue;
			}
		}
		
		// 품번 검색
		FString productIDString = arAllRows[nIndex]->ProductID.ToString();
		int32 findIndexProductID = productIDString.Find( searchString );
		if( findIndexProductID != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
			continue;
		}
		else
		{
			for( auto& otherID : arAllRows[nIndex]->Other_ProductID )
			{
				FString otherIDString = otherID.ToString();
				int32 findIndexOtherID = otherIDString.Find( searchString );
				if( findIndexOtherID != INDEX_NONE )
				{
					OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
					break;
				}
			}
		}
	}
#endif
}

void UBigtamin_GameInstance::GetBootsIndexInfoByBrand( E_BRAND_TYPE brandType, TArray<int>& OUT_BootsInexInfoByBrand )
{
	TArray<FST_FootBallBootsData*> arAllRows;
	_BootsInfoTable->GetAllRows<FST_FootBallBootsData>( "", arAllRows );

	for( int32 nIndex = 0; nIndex < arAllRows.Num(); ++nIndex )
	{
		if( brandType == E_BRAND_TYPE::E_BRAND_TYPE_ALL || arAllRows[nIndex]->eBrandType == brandType )
		{
			OUT_BootsInexInfoByBrand.AddUnique( arAllRows[nIndex]->nIndex );
		}
	}
}

void UBigtamin_GameInstance::GetBootsIndexInfoByBrandSort( TArray<E_BRAND_TYPE> brandType, E_SORT_TYPE sortType, TArray<int>& OUT_BootsInexInfoByBrandSort )
{
#if DB_BOOTS_DATA
	UFBM_SaveGame::Get().GetBootsIndexInfoByBrandSort_DB( brandType, sortType, OUT_BootsInexInfoByBrandSort );
#else
	TArray<FST_FootBallBootsData*> arAllRows;
	_BootsInfoTable->GetAllRows<FST_FootBallBootsData>( "", arAllRows );

	arAllRows.Sort( [sortType]( FST_FootBallBootsData A, FST_FootBallBootsData B )
	{
		switch( sortType )
		{
		case E_SORT_TYPE::E_SORT_TYPE_NEW:
			return A.nReleaseDate >= B.nReleaseDate;
		case E_SORT_TYPE::E_SORT_TYPE_PRICE_LOW:
			{
				if( A.nPrice == 0 )
				{
					return false;
				}
				else if( B.nPrice == 0 )
				{
					return true;
				}

				return A.nPrice <= B.nPrice;
			}
		case E_SORT_TYPE::E_SORT_TYPE_PRICE_HIGH:
			return A.nPrice >= B.nPrice;
		case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_LOW:
			return A.nWeight <= B.nWeight;
		case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_HIGH:
			return A.nWeight >= B.nWeight;
		case E_SORT_TYPE::E_SORT_TYPE_ABC:
			{
				FString splitStringA = A.BootsName.ToString();
				FString splitLeftA;
				FString splitRightA;
				splitStringA.Split( TEXT( " " ), &splitLeftA, &splitRightA );

				FString splitStringB = B.BootsName.ToString();
				FString splitLeftB;
				FString splitRightB;
				splitStringB.Split( TEXT( " " ), &splitLeftB, &splitRightB );

				return splitRightA <= splitRightB;
			}
		case E_SORT_TYPE::E_SORT_TYPE_ABC_REVERS:
			{
				FString splitStringA = A.BootsName.ToString();
				FString splitLeftA;
				FString splitRightA;
				splitStringA.Split( TEXT( " " ), &splitLeftA, &splitRightA );

				FString splitStringB = B.BootsName.ToString();
				FString splitLeftB;
				FString splitRightB;
				splitStringB.Split( TEXT( " " ), &splitLeftB, &splitRightB );

				return splitRightA >= splitRightB;
			}
		default:
			return A.nIndex < B.nIndex;
		}
	} );

	for( int32 nIndex = 0; nIndex < arAllRows.Num(); ++nIndex )
	{
		int32 findAllTypeIndex = brandType.Find( E_BRAND_TYPE::E_BRAND_TYPE_ALL );
		int32 findIndex = brandType.Find( arAllRows[nIndex]->eBrandType );
		if( findAllTypeIndex != INDEX_NONE || findIndex != INDEX_NONE )
		{
			OUT_BootsInexInfoByBrandSort.AddUnique( arAllRows[nIndex]->nIndex );
		}
	}
#endif
}

void UBigtamin_GameInstance::GetAllBootsBrand( TArray<E_BRAND_TYPE>& OUT_BootsBrand )
{
	TArray<FST_FootBallBootsData*> arAllRows;
	_BootsInfoTable->GetAllRows<FST_FootBallBootsData>( "", arAllRows );

	for( int32 nIndex = 0; nIndex < arAllRows.Num(); ++nIndex )
	{
		OUT_BootsBrand.AddUnique( arAllRows[nIndex]->eBrandType );
	}
}


void UBigtamin_GameInstance::GetBootsIndexInfoByFiltering( TArray<int>& OUT_BootsInexInfoByFiltering, FST_BOOTS_FILTER_INFO filterData, E_SORT_TYPE sortType /*= E_SORT_TYPE::E_SORT_TYPE_NONE */, E_BRAND_TYPE curBrandType/* = E_BRAND_TYPE::E_BRAND_TYPE_ALL*/ )
{
	TArray<FST_FootBallBootsData*> arAllRows;
	_BootsInfoTable->GetAllRows<FST_FootBallBootsData>( "", arAllRows );

	// 필터링 Data 없을때
	if( filterData.IsNotFilter() )
	{
		TArray< E_BRAND_TYPE> arrCurBrandType;
		arrCurBrandType.AddUnique( curBrandType );
		GInst->GetBootsIndexInfoByBrandSort( arrCurBrandType, sortType, OUT_BootsInexInfoByFiltering );
		return;
	}

	// 브랜드 필터링
	if( filterData.BrandType.Num() > 0 )
	{
		GInst->GetBootsIndexInfoByBrandSort( filterData.BrandType, sortType, OUT_BootsInexInfoByFiltering );
	}
	else
	{
		TArray< E_BRAND_TYPE> arrBrandType;
		arrBrandType.AddUnique( curBrandType );
		GInst->GetBootsIndexInfoByBrandSort( arrBrandType, sortType, OUT_BootsInexInfoByFiltering );
	}

	// COLLECTION 필터링
	if( filterData.CollectionType.Num() > 0 )
	{
		TArray<int32> removeCollectionIndex;
		for( auto& collectionItemIndex : OUT_BootsInexInfoByFiltering )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( collectionItemIndex );
			if( bootsSlotInfo_DB != nullptr )
			{
				bool isFind = false;
				for( auto& collectionType : filterData.CollectionType )
				{
					if( bootsSlotInfo_DB->CollectionType == collectionType )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeCollectionIndex.AddUnique( collectionItemIndex );
				}
			}
#else
			bool isSuccess = false;
			FST_FootBallBootsData bootsSlotInfo = GetBootsInfo( collectionItemIndex, isSuccess );
			if( isSuccess )
			{
				bool isFind = false;
				for( auto& collectionType : filterData.CollectionType )
				{
					if ( bootsSlotInfo.eCollectionType == collectionType)
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeCollectionIndex.AddUnique( collectionItemIndex );
				}
			}
#endif
		}

		for( auto& index : removeCollectionIndex )
		{
			OUT_BootsInexInfoByFiltering.Remove( index );
		}
	}

	// Model 필터링
	if( filterData.ModelType.Num() > 0 )
	{
		TArray<int32> removeModelIndex;
		for( auto& modelItemIndex : OUT_BootsInexInfoByFiltering )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( modelItemIndex );
			if( bootsSlotInfo_DB != nullptr )
			{
				bool isFind = false;
				for( auto& modelType : filterData.ModelType )
				{
					if( bootsSlotInfo_DB->ModelType == modelType )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeModelIndex.AddUnique( modelItemIndex );
				}
			}
#else
			bool isSuccess = false;
			FST_FootBallBootsData bootsSlotInfo = GetBootsInfo( modelItemIndex, isSuccess );
			if( isSuccess )
			{
				bool isFind = false;
				for( auto& modelType : filterData.ModelType )
				{
					if( bootsSlotInfo.eModelType == modelType )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeModelIndex.AddUnique( modelItemIndex );
				}
			}
#endif
		}

		for( auto& index : removeModelIndex )
		{
			OUT_BootsInexInfoByFiltering.Remove( index );
		}
	}

	// 스터드 필터링
	if( filterData.StudsTYpe.Num() > 0 )
	{
		TArray<int32> removeStudsIndex;
		for( auto& studsItemIndex : OUT_BootsInexInfoByFiltering )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( studsItemIndex );
			if( bootsSlotInfo_DB != nullptr )
			{
				bool isFind = false;
				for( auto& studsType : filterData.StudsTYpe )
				{
					if( bootsSlotInfo_DB->StudsType == studsType
						|| (studsType == E_STUDS_TYPE::E_STUDS_TF && bootsSlotInfo_DB->StudsType == E_STUDS_TYPE::E_STUDS_AS) )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeStudsIndex.AddUnique( studsItemIndex );
				}
			}
#else
			bool isSuccess = false;
			FST_FootBallBootsData bootsSlotInfo = GetBootsInfo( studsItemIndex, isSuccess );
			if( isSuccess )
			{
				bool isFind = false;
				for( auto& studsType : filterData.StudsTYpe )
				{
					if( bootsSlotInfo.eStudsType == studsType
						|| (studsType == E_STUDS_TYPE::E_STUDS_TF && bootsSlotInfo.eStudsType == E_STUDS_TYPE::E_STUDS_AS) )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeStudsIndex.AddUnique( studsItemIndex );
				}
			}
#endif
		}

		for( auto& index : removeStudsIndex )
		{
			OUT_BootsInexInfoByFiltering.Remove( index );
		}
	}

	// 사일로 필터링
	if( filterData.SiloType.Num() > 0 )
	{
		TArray<int32> removeSiloIndex;
		for( auto& siloItemIndex : OUT_BootsInexInfoByFiltering )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( siloItemIndex );
			if( bootsSlotInfo_DB != nullptr )
			{
				bool isFind = false;
				for( auto& siloType : filterData.SiloType )
				{
					if( bootsSlotInfo_DB->SiloType == siloType )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeSiloIndex.AddUnique( siloItemIndex );
				}
			}
#else
			bool isSuccess = false;
			FST_FootBallBootsData bootsSlotInfo = GetBootsInfo( siloItemIndex, isSuccess );
			if( isSuccess )
			{
				bool isFind = false;
				for( auto& siloType : filterData.SiloType )
				{
					if( bootsSlotInfo.eSiloType == siloType )
					{
						isFind = true;
						break;
					}
				}

				if( isFind == false )
				{
					removeSiloIndex.AddUnique( siloItemIndex );
				}
			}
#endif
		}

		for( auto& index : removeSiloIndex )
		{
			OUT_BootsInexInfoByFiltering.Remove( index );
		}
	}
}

void UBigtamin_GameInstance::SetCurMode(E_MODE eCurMode)
{
	_CurMode = eCurMode;
}

E_MODE UBigtamin_GameInstance::GetCurMode()
{
	return _CurMode;
}

void UBigtamin_GameInstance::SetCurSelectBootsIndex( int32 selectBootsIndex )
{
	_CurSelectBootsIndex = selectBootsIndex;
}

int32 UBigtamin_GameInstance::GetCurSelectBootsIndex()
{
	return _CurSelectBootsIndex;
}

void UBigtamin_GameInstance::InitCompareBootsIndex()
{
	_CompareBootsIndex1 = 0;
	_CompareBootsIndex2 = 0;
	_CompareBootsIndex3 = 0;
}

bool UBigtamin_GameInstance::AddCompareBootsIndex( const int32 bootsIndex )
{
	if( IsAlReadyAddSlot( bootsIndex ) )
	{
		return false;
	}

	if ( _CompareBootsIndex1 == 0)
	{
		_CompareBootsIndex1 = bootsIndex;
	}
	else if( _CompareBootsIndex2 == 0 )
	{
		_CompareBootsIndex2 = bootsIndex;
	}
	else if( _CompareBootsIndex3 == 0 )
	{
		_CompareBootsIndex3 = bootsIndex;
	}
	else
	{
		return false;
	}

	return true;
}

bool UBigtamin_GameInstance::RemoveCompareBootsSlot( const int32 slotIndex )
{
	switch( slotIndex )
	{
	case 1:
		_CompareBootsIndex1 = _CompareBootsIndex2;
		_CompareBootsIndex2 = _CompareBootsIndex3;
		_CompareBootsIndex3 = 0;
		break;
	case 2:
		_CompareBootsIndex2 = _CompareBootsIndex3;
		_CompareBootsIndex3 = 0;
		break;
	case 3:
		_CompareBootsIndex3 = 0;
		break;
	default:
		break;
	}

	return true;
}

int32 UBigtamin_GameInstance::GetCompareBootsIndex( const int32 slotIndex )
{
	if (slotIndex < 1 || slotIndex > 3)
	{
		return 0;
	}

	return slotIndex == 1 ? _CompareBootsIndex1 : slotIndex == 2 ? _CompareBootsIndex2 : _CompareBootsIndex3;
}

int32 UBigtamin_GameInstance::GetCompareBootsSlotCount()
{
	if( _CompareBootsIndex3 > 0 )
	{
		return 3;
	}
	else if( _CompareBootsIndex2 > 0 )
	{
		return 2;
	}
	else if( _CompareBootsIndex1 > 0 )
	{
		return 1;
	}

	return 0;
}

bool UBigtamin_GameInstance::IsAlReadyAddSlot( const int32 bootsIndex )
{
	if( bootsIndex == _CompareBootsIndex1 || bootsIndex == _CompareBootsIndex2 || bootsIndex == _CompareBootsIndex3 )
	{
		return true;
	}

	return false;
}

void UBigtamin_GameInstance::SetCurSelectPlayerName( FString selectPlayerName )
{
	_CurSelectPlayerName = selectPlayerName;
}

FString UBigtamin_GameInstance::GetCurSelectPlayerName()
{
	return _CurSelectPlayerName;
}

void UBigtamin_GameInstance::InitComparePlayerName()
{
	_ComparePlayerName1.Empty();
	_ComparePlayerName2.Empty();
	_ComparePlayerName3.Empty();
}

bool UBigtamin_GameInstance::AddComparePlayerName( const FString PlayerName )
{
	if( IsAlReadyAddPlayerNameSlot( PlayerName ) )
	{
		return false;
	}

	if( _ComparePlayerName1.IsEmpty() )
	{
		_ComparePlayerName1 = PlayerName;
	}
	else if( _ComparePlayerName2.IsEmpty() )
	{
		_ComparePlayerName2 = PlayerName;
	}
	else if( _ComparePlayerName3.IsEmpty() )
	{
		_ComparePlayerName3 = PlayerName;
	}
	else
	{
		return false;
	}

	return true;
}

bool UBigtamin_GameInstance::RemoveComparePlayerNameSlot( const int32 slotIndex )
{
	switch( slotIndex )
	{
	case 1:
		_ComparePlayerName1 = _ComparePlayerName2;
		_ComparePlayerName2 = _ComparePlayerName3;
		_ComparePlayerName3.Empty();
		break;
	case 2:
		_ComparePlayerName2 = _ComparePlayerName3;
		_ComparePlayerName3.Empty();
		break;
	case 3:
		_ComparePlayerName3.Empty();
		break;
	default:
		break;
	}

	return true;
}

FString UBigtamin_GameInstance::GetComparePlayerName( const int32 slotIndex )
{
	if( slotIndex < 1 || slotIndex > 3 )
	{
		return FString();
	}

	return slotIndex == 1 ? _ComparePlayerName1 : slotIndex == 2 ? _ComparePlayerName2 : _ComparePlayerName3;
}

int32 UBigtamin_GameInstance::GetComparePlayerNameSlotCount()
{
	if( !_ComparePlayerName3.IsEmpty() )
	{
		return 3;
	}
	else if( !_ComparePlayerName2.IsEmpty() )
	{
		return 2;
	}
	else if( !_ComparePlayerName1.IsEmpty() )
	{
		return 1;
	}

	return 0;
}

bool UBigtamin_GameInstance::IsAlReadyAddPlayerNameSlot( const FString PlayerName )
{
	if( PlayerName == _ComparePlayerName1 || PlayerName == _ComparePlayerName2 || PlayerName == _ComparePlayerName3 )
	{
		return true;
	}

	return false;
}

bool UBigtamin_GameInstance::PlayWarningUI( const int32 warningIndex )
{
	if( _WarningUMG == nullptr )
	{
		_WarningUMG = B_HUD->CreateDynamicWidget<UBWidget_Warning>( EDynamicWidgetParts::Warning, true, 9999 );
	}

	if( _WarningUMG != nullptr )
	{
		return _WarningUMG->PlayWarning( warningIndex );
	}

	return false;
}

void UBigtamin_GameInstance::PlayLoadingUI( const bool isLoading )
{
	if( _LoadingUMG == nullptr )
	{
		_LoadingUMG = B_HUD->CreateDynamicWidget<UBWidget_Loading>( EDynamicWidgetParts::Loading, true, 9999 );
	}

	if( _LoadingUMG != nullptr )
	{
		/*
		if (isLoading)
		{
			FLoadingScreenAttributes LoadingScreen;
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
			LoadingScreen.WidgetLoadingScreen = _LoadingUMG->TakeWidget();
			//LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

			GetMoviePlayer()->SetupLoadingScreen( LoadingScreen );
			//GetMoviePlayer()->PlayMovie();	
		}
		*/
		_LoadingUMG->PlayLoading( isLoading );
	}
}

void UBigtamin_GameInstance::SetDownLoadBootsImage( FString bootsID, UTexture2DDynamic* downloadTextrure )
{
	bool isContain = _DownLoadBootsImage.Contains( bootsID );
	if( isContain == false )
	{
		_DownLoadBootsImage.Add( bootsID, downloadTextrure );
	}
}

UTexture2DDynamic* UBigtamin_GameInstance::GetDownLoadBootsImage( FString bootsID )
{
	bool isContain = _DownLoadBootsImage.Contains( bootsID );
	if( isContain )
	{
		return _DownLoadBootsImage[bootsID];
	}

	return nullptr;
}

void UBigtamin_GameInstance::SetDownLoadTeamLogoImage( FString teamName, UTexture2DDynamic* downloadTextrure )
{
	bool isContain = _DownLoadLogoImage.Contains( teamName );
	if( isContain == false )
	{
		_DownLoadLogoImage.Add( teamName, downloadTextrure );
	}
}

UTexture2DDynamic* UBigtamin_GameInstance::GetDownLoadTeamLogoImage( FString teamName )
{
	bool isContain = _DownLoadLogoImage.Contains( teamName );
	if( isContain )
	{
		return _DownLoadLogoImage[teamName];
	}

	return nullptr;
}

void UBigtamin_GameInstance::SetDownLoadPlayerImage( FString playerName, UTexture2DDynamic* downloadTextrure )
{
	bool isContain = _DownLoadPlayerImage.Contains( playerName );
	if( isContain == false )
	{
		_DownLoadPlayerImage.Add( playerName, downloadTextrure );
	}
}

UTexture2DDynamic* UBigtamin_GameInstance::GetDownLoadPlayerImage( FString playerName )
{
	bool isContain = _DownLoadPlayerImage.Contains( playerName );
	if( isContain )
	{
		return _DownLoadPlayerImage[playerName];
	}

	return nullptr;
}

void UBigtamin_GameInstance::BackInput()
{
	int32 index = _BackInputStack.Num();
	if( index > 0 )
	{
		E_MODE prevMode = _BackInputStack[index - 1]->GetPrevMode();
		GInst->SetCurMode( prevMode == E_MODE::E_MODE_SURVEY ? E_MODE::E_MODE_MAIN : prevMode );
		bool isRemove = _BackInputStack[index - 1]->_OnBackInput();
		
		if( isRemove == true && _BackInputStack.Num() == index )
		{
			_BackInputStack.RemoveAt( index - 1 );
		}
	}
	else
	{
		if ( GetCurMode() == E_MODE::E_MODE_MAIN)
		{
			UBWidget_NewMain* mainUMG = B_HUD->GetWidgetInViewport<UBWidget_NewMain>( EBUIName::Main );
			if( mainUMG != nullptr )
			{
				if( mainUMG->BP_MainCategory_UMG->IsVisible() )
				{
					mainUMG->PlayCategoryAni( false );
				}
				else
				{
					mainUMG->PlayQuit();
				}
			}
		}
	}
}

void UBigtamin_GameInstance::AddBackInput( UBWidget* widget )
{
	UBWidget* widgetData = GetBackInput( widget );
	if( widgetData != nullptr )
	{
		_BackInputStack.Remove( widget );
	}
	_BackInputStack.Add( widget );
}

UBWidget* UBigtamin_GameInstance::GetBackInput( UBWidget* widget )
{
	for( auto &It : _BackInputStack )
	{
		if( It == widget )
		{
			return It;
		}
	}
	return nullptr;
}

int32 UBigtamin_GameInstance::BackInputStackCount()
{
	return _BackInputStack.Num();
}

bool UBigtamin_GameInstance::IsPermissionSuccess() const
{
#if PLATFORM_ANDROID
	return true;
	//return bIsPermissionSuccess;
#endif

	return true;
}
