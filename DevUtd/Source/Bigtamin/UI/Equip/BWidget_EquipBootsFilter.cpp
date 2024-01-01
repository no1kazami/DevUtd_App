// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_EquipBootsFilter.h"
#include "BWidget_EquipBootsFilterItem.h"
#include "Bigtamin.h"


void UBWidget_EquipBootsFilter::Init( UBWidget* OwnerUI )
{
	Super::Init( OwnerUI );

	ButtonDelegate_Clicked( this, C_Btn_Filter_Cancel, &UBWidget_EquipBootsFilter::_OnClick_FilterCancel );
	ButtonDelegate_Clicked( this, C_Btn_Back, &UBWidget_EquipBootsFilter::_OnClick_Back );
	ButtonDelegate_Clicked( this, C_Btn_Apply, &UBWidget_EquipBootsFilter::_OnClick_Apply );
	ButtonDelegate_Clicked( this, C_Btn_Reset, &UBWidget_EquipBootsFilter::_OnClick_Reset );

	ButtonDelegate_Clicked( this, C_Btn_Brand, &UBWidget_EquipBootsFilter::_OnClick_Brand );
	ButtonDelegate_Clicked( this, C_Btn_Collection, &UBWidget_EquipBootsFilter::_OnClick_Collection );
	ButtonDelegate_Clicked( this, C_Btn_Model, &UBWidget_EquipBootsFilter::_OnClick_Model );
	ButtonDelegate_Clicked( this, C_Btn_Studs, &UBWidget_EquipBootsFilter::_OnClick_Studs );
	ButtonDelegate_Clicked( this, C_Btn_Silo, &UBWidget_EquipBootsFilter::_OnClick_Silo );

	C_CB_Brand->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilter::_OnBrandCheckStateChanged );
	C_CB_Brand->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilter::_OnBrandCheckStateChanged );
	C_CB_Collection->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilter::_OnCollectionCheckStateChanged );
	C_CB_Collection->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilter::_OnCollectionCheckStateChanged );
	C_CB_Model->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilter::_OnModelCheckStateChanged );
	C_CB_Model->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilter::_OnModelCheckStateChanged );
	C_CB_Studs->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilter::_OnStudsCheckStateChanged );
	C_CB_Studs->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilter::_OnStudsCheckStateChanged );
	C_CB_Silo->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilter::_OnSiloCheckStateChanged );
	C_CB_Silo->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilter::_OnSiloCheckStateChanged );

	_InitEquipBootsFilter();
}

void UBWidget_EquipBootsFilter::ResetFilter()
{
	// 브랜드 Reset
	for( int i = 0; i < C_VB_Filter_Brand->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Brand->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Brand->SetCheckedState( ECheckBoxState::Unchecked );
	_OnBrandCheckStateChanged( false );

	// Collection Reset
	for( int i = 0; i < C_VB_Filter_Collection->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Collection->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Collection->SetCheckedState( ECheckBoxState::Unchecked );
	_OnCollectionCheckStateChanged( false );

	// Model Reset
	for( int i = 0; i < C_VB_Filter_Model->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Model->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Model->SetCheckedState( ECheckBoxState::Unchecked );
	_OnModelCheckStateChanged( false );

	// 스터드 Reset
	for( int i = 0; i < C_VB_Filter_Studs->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Studs->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Studs->SetCheckedState( ECheckBoxState::Unchecked );
	_OnStudsCheckStateChanged( false );

	// 사일로 Reset
	for( int i = 0; i < C_VB_Filter_Silo->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_VB_Filter_Silo->GetChildAt( i ) );
		if( It != nullptr )
		{
			It->ResetFilterItem();
		}
	}

	C_CB_Silo->SetCheckedState( ECheckBoxState::Unchecked );
	_OnSiloCheckStateChanged( false );


	// 필터 Reset
	_FilterInfo.InitFilterInfo();
	_PrevFilterInfo.InitFilterInfo();

	_InitEquipBootsFilter();
}

void UBWidget_EquipBootsFilter::ResetFilter( E_BRAND_TYPE brandType )
{
	ResetFilter();

	C_Ol_Brand->SetVisibility( (brandType == E_BRAND_TYPE::E_BRAND_TYPE_ALL) ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed );
}

void UBWidget_EquipBootsFilter::HandleBackInput()
{
	_OnClick_Back();
}

void UBWidget_EquipBootsFilter::OnClose()
{
	Super::OnClose();
}

void UBWidget_EquipBootsFilter::OnShow()
{
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::MAX );

	C_CB_Brand->SetCheckedState( ECheckBoxState::Unchecked );
	_OnBrandCheckStateChanged( false );
	C_CB_Collection->SetCheckedState( ECheckBoxState::Unchecked );
	_OnCollectionCheckStateChanged( false );
	C_CB_Model->SetCheckedState( ECheckBoxState::Unchecked );
	_OnModelCheckStateChanged( false );
	C_CB_Studs->SetCheckedState( ECheckBoxState::Unchecked );
	_OnStudsCheckStateChanged( false );
	C_CB_Silo->SetCheckedState( ECheckBoxState::Unchecked );
	_OnSiloCheckStateChanged( false );
}

void UBWidget_EquipBootsFilter::_OnClick_FilterCancel()
{
	OnClickEquipFilterCancel.Broadcast();
}

void UBWidget_EquipBootsFilter::_OnClick_Back()
{
	_FilterInfo = _PrevFilterInfo;
	OnClickEquipFilterCancel.Broadcast();
}

void UBWidget_EquipBootsFilter::_OnClick_Apply()
{
	_PrevFilterInfo = _FilterInfo;
	OnClickEquipFilterApply.Broadcast( _FilterInfo );
}

void UBWidget_EquipBootsFilter::_OnClick_Reset()
{
	ResetFilter();
	_OnClick_Apply();
}

void UBWidget_EquipBootsFilter::_ResetClick( E_BOOTS_FILTER_TYPE clickFilterType )
{
	C_SB_Filter->ScrollToStart();

	if ( clickFilterType != E_BOOTS_FILTER_TYPE::BRAND)
	{
		C_CB_Brand->SetCheckedState( ECheckBoxState::Unchecked );
		_OnBrandCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::COLLECTION )
	{
		C_CB_Collection->SetCheckedState( ECheckBoxState::Unchecked );
		_OnCollectionCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::MODEL )
	{
		C_CB_Model->SetCheckedState( ECheckBoxState::Unchecked );
		_OnModelCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::STUDS )
	{
		C_CB_Studs->SetCheckedState( ECheckBoxState::Unchecked );
		_OnStudsCheckStateChanged( false );
	}
	if( clickFilterType != E_BOOTS_FILTER_TYPE::SILO )
	{
		C_CB_Silo->SetCheckedState( ECheckBoxState::Unchecked );
		_OnSiloCheckStateChanged( false );
	}
}

void UBWidget_EquipBootsFilter::_OnClick_Brand()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::BRAND );

	C_CB_Brand->SetCheckedState( C_CB_Brand->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnBrandCheckStateChanged( C_CB_Brand->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilter::_OnClick_Collection()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::COLLECTION );

	C_CB_Collection->SetCheckedState( C_CB_Collection->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnCollectionCheckStateChanged( C_CB_Collection->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilter::_OnClick_Model()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::MODEL );

	C_CB_Model->SetCheckedState( C_CB_Model->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnModelCheckStateChanged( C_CB_Model->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilter::_OnClick_Studs()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::STUDS );

	C_CB_Studs->SetCheckedState( C_CB_Studs->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnStudsCheckStateChanged( C_CB_Studs->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilter::_OnClick_Silo()
{
	_ResetClick( E_BOOTS_FILTER_TYPE::SILO );

	C_CB_Silo->SetCheckedState( C_CB_Silo->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnSiloCheckStateChanged( C_CB_Silo->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilter::_OnBrandCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Brand->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineBrand->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_EquipBootsFilter::_OnCollectionCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Collection->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineCollection->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_EquipBootsFilter::_OnModelCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Model->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineModel->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_EquipBootsFilter::_OnStudsCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Studs->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineStuds->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_EquipBootsFilter::_OnSiloCheckStateChanged( bool isChecked )
{
	C_VB_Filter_Silo->SetVisibility( isChecked ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
	C_Img_LineSilo->SetVisibility( isChecked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
}

void UBWidget_EquipBootsFilter::_HandleBrandFilter( const E_BRAND_TYPE bootsBrandType, const bool isCheck )
{
	_FilterInfo.CheckBrandType(bootsBrandType, isCheck);
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::BRAND );
}

void UBWidget_EquipBootsFilter::_HandleCollectionFilter( const E_COLLECTION_TYPE bootsCollectionType, const bool isCheck )
{
	_FilterInfo.CheckCollectionType( bootsCollectionType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::COLLECTION );
}

void UBWidget_EquipBootsFilter::_HandleModelFilter( const E_MODEL_TYPE bootsModelType, const bool isCheck )
{
	_FilterInfo.CheckModelType( bootsModelType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::MODEL );
}

void UBWidget_EquipBootsFilter::_HandleStudsFilter( const E_STUDS_TYPE bootsStudsType, const bool isCheck )
{
	_FilterInfo.CheckStudsType( bootsStudsType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::STUDS );
}

void UBWidget_EquipBootsFilter::_HandleSiloFilter( const E_SILO_TYPE bootsSiloType, const bool isCheck )
{
	_FilterInfo.CheckSiloType( bootsSiloType, isCheck );
	_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE::SILO );
}

void UBWidget_EquipBootsFilter::_InitEquipBootsFilter()
{
	TArray<E_BRAND_TYPE> brandInfo;
	TArray<E_COLLECTION_TYPE> collectionInfo;
	TArray<E_MODEL_TYPE> modelInfo;
	TArray<E_SILO_TYPE> siloInfo;
	TArray<E_STUDS_TYPE> studsInfo;
	_GetFilteringCategoryData( brandInfo, collectionInfo, modelInfo, siloInfo, studsInfo );

	// 브랜드 초기화
	_ResetFilter_Brand( brandInfo );

	// Collection 초기화
	_ResetFilter_Collection( collectionInfo );

	// Model 초기화
	_ResetFilter_Model( modelInfo );

	// 스터드 초기화
	_ResetFilter_Studs( studsInfo );

	// 사일로 초기화
	_ResetFilter_Silo( siloInfo );
}

void UBWidget_EquipBootsFilter::_UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE filterType )
{
	TArray<E_BRAND_TYPE> brandInfo;
	TArray<E_COLLECTION_TYPE> collectionInfo;
	TArray<E_MODEL_TYPE> modelInfo;
	TArray<E_SILO_TYPE> siloInfo;
	TArray<E_STUDS_TYPE> studsInfo;
	_GetFilteringCategoryData( brandInfo, collectionInfo, modelInfo, siloInfo, studsInfo );

	// 브랜드 필터 업데이트
	_ResetFilter_Brand( brandInfo );

	// Collection(모델) 필터 업데이트
	_ResetFilter_Collection( collectionInfo );

	// 등급 필터 업데이트
	_ResetFilter_Model( modelInfo );

	// 스터드 필터 업데이트
	_ResetFilter_Studs( studsInfo );

	// 사일로 필터 업데이트
	_ResetFilter_Silo( siloInfo );
}

void UBWidget_EquipBootsFilter::_GetFilteringCategoryData( TArray<E_BRAND_TYPE>& Out_BrandInfo, 
														   TArray<E_COLLECTION_TYPE>& Out_CollectionInfo,
														   TArray<E_MODEL_TYPE>& Out_ModelInfo ,
														   TArray<E_SILO_TYPE>& Out_SiloInfo,
														   TArray<E_STUDS_TYPE>& Out_StudsInfo )
{
	// 필터링된 데이터 가져오기
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );

	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	TArray<int> filteringBootsIndexInfo;

	// 브랜드 카테고리
	tempFilterInfo.BrandType.Empty();
	filteringBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( filteringBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& filterItemIndex : filteringBootsIndexInfo )
	{
#if DB_BOOTS_DATA
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( filterItemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			Out_BrandInfo.AddUnique( bootsSlotInfo_DB->BrandType );
		}
#else
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( filterItemIndex, isSuccess );
		if( isSuccess )
		{
			Out_BrandInfo.AddUnique( bootsSlotInfo.eBrandType );
		}
#endif
	}

	// Collection 카테고리
	tempFilterInfo = _FilterInfo;
	tempFilterInfo.CollectionType.Empty();
	filteringBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( filteringBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& filterItemIndex : filteringBootsIndexInfo )
	{
#if DB_BOOTS_DATA
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( filterItemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			Out_CollectionInfo.AddUnique( bootsSlotInfo_DB->CollectionType );
		}
#else
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( filterItemIndex, isSuccess );
		if( isSuccess )
		{
			Out_CollectionInfo.AddUnique( bootsSlotInfo.eCollectionType );
		}
#endif
	}

	// Model 카테고리
	tempFilterInfo = _FilterInfo;
	tempFilterInfo.ModelType.Empty();
	filteringBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( filteringBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& filterItemIndex : filteringBootsIndexInfo )
	{
#if DB_BOOTS_DATA
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( filterItemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			Out_ModelInfo.AddUnique( bootsSlotInfo_DB->ModelType );
		}
#else
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( filterItemIndex, isSuccess );
		if( isSuccess )
		{
			Out_ModelInfo.AddUnique( bootsSlotInfo.eModelType );
		}
#endif
	}

	// 스터드 카테고리
	tempFilterInfo = _FilterInfo;
	tempFilterInfo.StudsTYpe.Empty();
	filteringBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( filteringBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& filterItemIndex : filteringBootsIndexInfo )
	{
#if DB_BOOTS_DATA
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( filterItemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			Out_StudsInfo.AddUnique( bootsSlotInfo_DB->StudsType );
		}
#else
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( filterItemIndex, isSuccess );
		if( isSuccess && bootsSlotInfo.eStudsType != E_STUDS_TYPE::E_STUDS_AS)
		{
			Out_StudsInfo.AddUnique( bootsSlotInfo.eStudsType );
		}
#endif
	}

	// 사일로 카테고리
	tempFilterInfo = _FilterInfo;
	tempFilterInfo.SiloType.Empty();
	filteringBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( filteringBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& filterItemIndex : filteringBootsIndexInfo )
	{
#if DB_BOOTS_DATA
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( filterItemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			Out_SiloInfo.AddUnique( bootsSlotInfo_DB->SiloType );
		}
#else
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( filterItemIndex, isSuccess );
		if( isSuccess )
		{
			Out_SiloInfo.AddUnique( bootsSlotInfo.eSiloType );
		}
#endif
	}
}

void UBWidget_EquipBootsFilter::_GetFilterType( E_SORT_TYPE& Out_SortType, E_BRAND_TYPE& Out_BrandType )
{
	Out_SortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	Out_BrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	if( this->OwnerPannel != nullptr )
	{
		if( UBWidget_EquipMain* ownerEquipMain = Cast<UBWidget_EquipMain>( this->OwnerPannel ) )
		{
			Out_SortType = ownerEquipMain->GetSortType();
			Out_BrandType = ownerEquipMain->GetBrandType();
		}
	}
}

void UBWidget_EquipBootsFilter::_ResetFilter_Brand( const TArray<E_BRAND_TYPE>& brandInfo )
{
	// 체크된 항목 따로 빼놓기
	/*
	TArray< E_BRAND_TYPE> checkedBrandType;
	for( int i = 0; i < C_SB_Filter_Brand->GetChildrenCount(); i++ )
	{
		UBWidget_EquipBootsFilterItem* It = Cast<UBWidget_EquipBootsFilterItem>( C_SB_Filter_Brand->GetChildAt( i ) );
		if( It != nullptr )
		{
			if( It->GetFilterCheckState() == ECheckBoxState::Checked )
			{
				if (_FilterInfo.IsCheckBrand( It->GetBrandType() ))
				{
					checkedBrandType.AddUnique( It->GetBrandType() );
				}
			}
		}
	}
	*/

	C_Txt_Count_Brand->SetVisibility( _FilterInfo.BrandType.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.BrandType.Num() > 0 )
	{
		FText mainBrandText = UFBMUtil::BrandNameText( _FilterInfo.BrandType[0] );
		if ( _FilterInfo.BrandType.Num() == 1)
		{
			C_Txt_Count_Brand->SetText( mainBrandText );
		}
		else
		{
			C_Txt_Count_Brand->SetText( FText::Format( GET_BTEXT( 137 ), mainBrandText, FText::AsNumber( _FilterInfo.BrandType.Num() - 1 ) ) );
		}
	}

	TMap< E_BRAND_TYPE, FiterDataInfo> mapBrand;
	for( auto& brand : brandInfo )
	{
		mapBrand.Add(brand, FiterDataInfo(false));
	}
	for (auto& checkBrand : _FilterInfo.BrandType )
	{
		mapBrand.Add(checkBrand, FiterDataInfo(true));
	}

	mapBrand.KeySort( []( E_BRAND_TYPE A, E_BRAND_TYPE B )
					  {
						  return A < B; 
					  } );

	// 필터링된 데이터에서 해당 브랜드 갯수 계산
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );
	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	tempFilterInfo.BrandType.Empty();
	TArray<int> arrayBootsIndexInfo;
	GInst->GetBootsIndexInfoByFiltering( arrayBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& brand : mapBrand )
	{
		int32 brandCount = 0;
		for( auto& bootsIndex : arrayBootsIndexInfo )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
			if( bootsSlotInfo_DB != nullptr && brand.Key == bootsSlotInfo_DB->BrandType )
			{
				brandCount++;
			}
#else
			bool isSuccess;
			FST_FootBallBootsData bootsInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
			if( isSuccess && brand.Key == bootsInfo.eBrandType )
			{
				brandCount++;
			}
#endif
		}

		brand.Value.dataCount = brandCount;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	C_VB_Filter_Brand->ClearChildren();

	for( auto& brand : mapBrand )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetBootsFilterData_Brand( brand.Key, brand.Value.isChecked, brand.Value.dataCount );
			if( bootsFilterItem->OnClickFilterBrand.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterBrand.AddUObject( this, &UBWidget_EquipBootsFilter::_HandleBrandFilter );
			}

			C_VB_Filter_Brand->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_EquipBootsFilter::_ResetFilter_Collection( const TArray<E_COLLECTION_TYPE>& collectionInfo )
{
	C_Txt_Count_Collection->SetVisibility( _FilterInfo.CollectionType.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.CollectionType.Num() > 0 )
	{
		FText mainCollectionText = UFBMUtil::CollectionText( _FilterInfo.CollectionType[0] );
		if( _FilterInfo.CollectionType.Num() == 1 )
		{
			C_Txt_Count_Collection->SetText( mainCollectionText );
		}
		else
		{
			C_Txt_Count_Collection->SetText( FText::Format( GET_BTEXT( 137 ), mainCollectionText, FText::AsNumber( _FilterInfo.CollectionType.Num() - 1 ) ) );
		}
	}

	TMap< E_COLLECTION_TYPE, FiterDataInfo> mapCollection;
	for( auto& collection : collectionInfo )
	{
		mapCollection.Add( collection, FiterDataInfo( false ) );
	}
	for( auto& checkCollection : _FilterInfo.CollectionType )
	{
		mapCollection.Add( checkCollection, FiterDataInfo( true ) );
	}

	mapCollection.KeySort( []( E_COLLECTION_TYPE A, E_COLLECTION_TYPE B )
						   {
							   return A < B;
						   } );

	// 필터링된 데이터에서 해당 브랜드 갯수 계산
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );
	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	tempFilterInfo.CollectionType.Empty();
	TArray<int> arrayBootsIndexInfo;
	GInst->GetBootsIndexInfoByFiltering( arrayBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& collection : mapCollection )
	{
		int32 collectionCount = 0;
		for( auto& bootsIndex : arrayBootsIndexInfo )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
			if( bootsSlotInfo_DB != nullptr && collection.Key == bootsSlotInfo_DB->CollectionType )
			{
				collectionCount++;
			}
#else
			bool isSuccess;
			FST_FootBallBootsData bootsInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
			if( isSuccess && collection.Key == bootsInfo.eCollectionType )
			{
				collectionCount++;
			}
#endif
		}

		collection.Value.dataCount = collectionCount;
	}

	C_VB_Filter_Collection->ClearChildren();
	//C_VB_Filter_Collection->ScrollToStart();
	for( auto& collection : mapCollection )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetBootsFilterData_Collection( collection.Key, collection.Value.isChecked, collection.Value.dataCount );
			if( bootsFilterItem->OnClickFilterCollection.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterCollection.AddUObject( this, &UBWidget_EquipBootsFilter::_HandleCollectionFilter );
			}

			C_VB_Filter_Collection->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_EquipBootsFilter::_ResetFilter_Model( const TArray<E_MODEL_TYPE>& modelInfo )
{
	C_Txt_Count_Model->SetVisibility( _FilterInfo.ModelType.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.ModelType.Num() > 0 )
	{
		FText mainModelText = UFBMUtil::ModelText( _FilterInfo.ModelType[0] );
		if( _FilterInfo.ModelType.Num() == 1 )
		{
			C_Txt_Count_Model->SetText( mainModelText );
		}
		else
		{
			C_Txt_Count_Model->SetText( FText::Format( GET_BTEXT( 137 ), mainModelText, FText::AsNumber( _FilterInfo.ModelType.Num() - 1 ) ) );
		}
	}

	TMap< E_MODEL_TYPE, FiterDataInfo> mapModel;
	for( auto& model : modelInfo )
	{
		mapModel.Add( model, FiterDataInfo( false ) );
	}
	for( auto& checkModel : _FilterInfo.ModelType )
	{
		mapModel.Add( checkModel, FiterDataInfo( true ) );
	}

	mapModel.KeySort( []( E_MODEL_TYPE A, E_MODEL_TYPE B )
						   {
							   return A < B;
						   } );

	// 필터링된 데이터에서 해당 브랜드 갯수 계산
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );
	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	tempFilterInfo.ModelType.Empty();
	TArray<int> arrayBootsIndexInfo;
	GInst->GetBootsIndexInfoByFiltering( arrayBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& model : mapModel )
	{
		int32 modelCount = 0;
		for( auto& bootsIndex : arrayBootsIndexInfo )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
			if( bootsSlotInfo_DB != nullptr && model.Key == bootsSlotInfo_DB->ModelType )
			{
				modelCount++;
			}
#else
			bool isSuccess;
			FST_FootBallBootsData bootsInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
			if( isSuccess && model.Key == bootsInfo.eModelType )
			{
				modelCount++;
			}
#endif
		}

		model.Value.dataCount = modelCount;
	}


	C_VB_Filter_Model->ClearChildren();
	for( auto& model : mapModel )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetBootsFilterData_Model( model.Key, model.Value.isChecked, model.Value.dataCount );
			if( bootsFilterItem->OnClickFilterModel.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterModel.AddUObject( this, &UBWidget_EquipBootsFilter::_HandleModelFilter );
			}

			C_VB_Filter_Model->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_EquipBootsFilter::_ResetFilter_Studs( const TArray<E_STUDS_TYPE>& studsInfo )
{
	C_Txt_Count_Studs->SetVisibility( _FilterInfo.StudsTYpe.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.StudsTYpe.Num() > 0 )
	{
		FText mainStudslText = UFBMUtil::StudsNameText( _FilterInfo.StudsTYpe[0] );
		if( _FilterInfo.StudsTYpe.Num() == 1 )
		{
			C_Txt_Count_Studs->SetText( mainStudslText );
		}
		else
		{
			C_Txt_Count_Studs->SetText( FText::Format( GET_BTEXT( 137 ), mainStudslText, FText::AsNumber( _FilterInfo.StudsTYpe.Num() - 1 ) ) );
		}
	}

	TMap< E_STUDS_TYPE, FiterDataInfo> mapStuds;
	for( auto& studs : studsInfo )
	{
		mapStuds.Add( studs, FiterDataInfo( false ) );
	}
	for( auto& checkStuds : _FilterInfo.StudsTYpe )
	{
		mapStuds.Add( checkStuds, FiterDataInfo( true ) );
	}

	mapStuds.KeySort( []( E_STUDS_TYPE A, E_STUDS_TYPE B )
						   {
							   return A < B;
						   } );

	// 필터링된 데이터에서 해당 브랜드 갯수 계산
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );
	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	tempFilterInfo.StudsTYpe.Empty();
	TArray<int> arrayBootsIndexInfo;
	GInst->GetBootsIndexInfoByFiltering( arrayBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& studs : mapStuds )
	{
		int32 studsCount = 0;
		for( auto& bootsIndex : arrayBootsIndexInfo )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
			if( bootsSlotInfo_DB != nullptr )
			{
				if( studs.Key == bootsSlotInfo_DB->StudsType
					|| (studs.Key == E_STUDS_TYPE::E_STUDS_TF && bootsSlotInfo_DB->StudsType == E_STUDS_TYPE::E_STUDS_AS) )
				{
					studsCount++;
				}
			}
#else
			bool isSuccess;
			FST_FootBallBootsData bootsInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
			if( isSuccess )
			{
				if (studs.Key == bootsInfo.eStudsType 
					 || (studs.Key == E_STUDS_TYPE::E_STUDS_TF && bootsInfo.eStudsType == E_STUDS_TYPE::E_STUDS_AS) )
				{
					studsCount++;
				}
			}
#endif
		}

		studs.Value.dataCount = studsCount;
	}

	C_VB_Filter_Studs->ClearChildren();
	for( auto& studs : mapStuds )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetBootsFilterData_Studs( studs.Key, studs.Value.isChecked, studs.Value.dataCount );
			if( bootsFilterItem->OnClickFilterStuds.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterStuds.AddUObject( this, &UBWidget_EquipBootsFilter::_HandleStudsFilter );
			}

			C_VB_Filter_Studs->AddChild( bootsFilterItem );
		}
	}
}

void UBWidget_EquipBootsFilter::_ResetFilter_Silo( const TArray<E_SILO_TYPE>& siloInfo )
{
	C_Txt_Count_Silo->SetVisibility( _FilterInfo.SiloType.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	if( _FilterInfo.SiloType.Num() > 0 )
	{
		FText mainSiloText = UFBMUtil::SiloNameText( _FilterInfo.SiloType[0] );
		if( _FilterInfo.SiloType.Num() == 1 )
		{
			C_Txt_Count_Silo->SetText( mainSiloText );
		}
		else
		{
			C_Txt_Count_Silo->SetText( FText::Format( GET_BTEXT( 137 ), mainSiloText, FText::AsNumber( _FilterInfo.SiloType.Num() - 1 ) ) );
		}
	}

	TMap< E_SILO_TYPE, FiterDataInfo> mapSilo;
	for( auto& silo : siloInfo )
	{
		mapSilo.Add( silo, FiterDataInfo( false ) );
	}
	for( auto& checkSilo : _FilterInfo.SiloType )
	{
		mapSilo.Add( checkSilo, FiterDataInfo( true ) );
	}

	mapSilo.KeySort( []( E_SILO_TYPE A, E_SILO_TYPE B )
						   {
							   return A < B;
						   } );

	// 필터링된 데이터에서 해당 브랜드 갯수 계산
	E_SORT_TYPE curSortType = E_SORT_TYPE::E_SORT_TYPE_NONE;
	E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	_GetFilterType( curSortType, curBrandType );
	FST_BOOTS_FILTER_INFO tempFilterInfo = _FilterInfo;
	tempFilterInfo.SiloType.Empty();
	TArray<int> arrayBootsIndexInfo;
	GInst->GetBootsIndexInfoByFiltering( arrayBootsIndexInfo, tempFilterInfo, curSortType, curBrandType );
	for( auto& silo : mapSilo )
	{
		int32 siloCount = 0;
		for( auto& bootsIndex : arrayBootsIndexInfo )
		{
#if DB_BOOTS_DATA
			const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
			if( bootsSlotInfo_DB != nullptr && silo.Key == bootsSlotInfo_DB->SiloType )
			{
				siloCount++;
			}
#else
			bool isSuccess;
			FST_FootBallBootsData bootsInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
			if( isSuccess && silo.Key == bootsInfo.eSiloType )
			{
				siloCount++;
			}
#endif
		}

		silo.Value.dataCount = siloCount;
	}

	C_VB_Filter_Silo->ClearChildren();
	for( auto& silo : mapSilo )
	{
		UBWidget_EquipBootsFilterItem* bootsFilterItem = B_HUD->CreateDynamicWidget<UBWidget_EquipBootsFilterItem>( EDynamicWidgetParts::EquipBootsFilterItem );
		if( bootsFilterItem != nullptr )
		{
			bootsFilterItem->OwnerPannel = this;
			bootsFilterItem->SetBootsFilterData_Silo( silo.Key, silo.Value.isChecked, silo.Value.dataCount);
			if( bootsFilterItem->OnClickFilterSilo.IsBoundToObject( this ) == false )
			{
				bootsFilterItem->OnClickFilterSilo.AddUObject( this, &UBWidget_EquipBootsFilter::_HandleSiloFilter );
			}

			C_VB_Filter_Silo->AddChild( bootsFilterItem );
		}
	}
}

