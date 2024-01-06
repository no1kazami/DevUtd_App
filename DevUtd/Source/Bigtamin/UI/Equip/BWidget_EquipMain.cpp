#include "BWidget_EquipMain.h"
#include "Bigtamin.h"
#include "UI/Boots/BWidget_BootsSlot.h"
#include "BWidget_EquipSort.h"
#include "BWidget_EquipFilterItem.h"
#include "BWidget_EquipBootsFilter.h"
#include "../BWidget_Top.h"

#define SCROLL_ITEM_NUM 30

void UBWidget_EquipMain::Init()
{
	Super::Init();

	BP_Top_EquipMain_UMG->Init();
	BP_Top_EquipMain_UMG->ChangeTopMode( E_MODE::E_MODE_EQUIP_MAIN );

	BP_EquipSort_UMG->Init();
	BP_EquipSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
	if( BP_EquipSort_UMG->OnClickEquipSort.IsBoundToObject( this ) == false )
	{
		BP_EquipSort_UMG->OnClickEquipSort.AddUObject( this, &UBWidget_EquipMain::_OnClickEquipSortEvent );
	}

	BP_EquipBootsFilter_UMG->Init(this);
	BP_EquipBootsFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );
	if( BP_EquipBootsFilter_UMG->OnClickEquipFilterApply.IsBoundToObject( this ) == false )
	{
		BP_EquipBootsFilter_UMG->OnClickEquipFilterApply.AddUObject( this, &UBWidget_EquipMain::_OnClickEquipFilterApplyEvent );
	}
	if( BP_EquipBootsFilter_UMG->OnClickEquipFilterCancel.IsBoundToObject( this ) == false )
	{
		BP_EquipBootsFilter_UMG->OnClickEquipFilterCancel.AddUObject( this, &UBWidget_EquipMain::_OnClickEquipFilterCancelEvent );
	}

	ButtonDelegate_Clicked( this, C_Btn_Sort, &UBWidget_EquipMain::_OnClick_SortBtn );
	ButtonDelegate_Clicked( this, C_Btn_Filter, &UBWidget_EquipMain::_OnClick_FilterBtn );

	_BootsFilterInfo.InitFilterInfo();
	InitEquipMain();

	_Ani_FilterOpen = GetWidgetAnimation( _Ani_FilterOpenName );
	Ani_FilterClose = GetWidgetAnimation( _Ani_FilterCloseName );
	_Ani_EquipMainOpen = GetWidgetAnimation( _Ani_EquipMainOpenName );
	_Ani_EquipMainClose = GetWidgetAnimation( _Ani_EquipMainCloseName );

	GInst->AddBackInput( this );

	//GInst->PlayLoadingUI( false );

	PlayEquipMainOpenAni( true );
}

void UBWidget_EquipMain::OnClose()
{
	Super::OnClose();
}

void UBWidget_EquipMain::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
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

void UBWidget_EquipMain::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_EquipMainCloseName )
		{
			CloseUI();
		}
	}
}

bool UBWidget_EquipMain::_OnBackInput()
{
	if ( BP_EquipSort_UMG->IsVisible())
	{
		BP_EquipSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
		return false;
	}
	else if( BP_EquipBootsFilter_UMG->IsVisible() )
	{
		BP_EquipBootsFilter_UMG->HandleBackInput();
		return false;
	}
	else
	{
		Super::_OnBackInput();
		PlayEquipMainOpenAni( false );
		return true;
	}
}

void UBWidget_EquipMain::InitEquipMain()
{
	_SetSort( E_SORT_TYPE::E_SORT_TYPE_NEW );

	_MainFilterItems.Empty();
	C_SB_EquipType->ClearChildren();
	C_SB_EquipType->ScrollToStart();

	// 메인 타입 축구화 필터
	UBWidget_EquipFilterItem* equipTypeItemBoots = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( equipTypeItemBoots != nullptr )
	{
		equipTypeItemBoots->OwnerPannel = this;
		equipTypeItemBoots->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_BOOTS, 29 );
		if( equipTypeItemBoots->OnClickEquipFilter.IsBoundToObject( this ) == false )
		{
			equipTypeItemBoots->OnClickEquipFilter.AddUObject( this, &UBWidget_EquipMain::OnClickEquipMainFilter );
		}
		C_SB_EquipType->AddChild( equipTypeItemBoots );
		_MainFilterItems.Add( equipTypeItemBoots );
	}
	// 메인 타입 용품 필터
	/*
	UBWidget_EquipFilterItem* equipTypeItemEtc = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
	if( equipTypeItemEtc != nullptr )
	{
		equipTypeItemEtc->OwnerPannel = this;
		equipTypeItemEtc->SetEquipFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_EQUIP, 37 );
		if( equipTypeItemEtc->OnClickEquipFilter.IsBoundToObject( this ) == false )
		{
			equipTypeItemEtc->OnClickEquipFilter.AddUObject( this, &UBWidget_EquipMain::OnClickEquipMainFilter );
		}
		C_SB_EquipType->AddChild( equipTypeItemEtc );
		_MainFilterItems.Add( equipTypeItemEtc );
	}
	*/

	OnClickEquipMainFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_BOOTS, true );
}

void UBWidget_EquipMain::SetSubEquipItem( const E_FILTER_ITEM_TYPE mainFilterType )
{
	_SubFilterItems.Empty();
	C_SB_SubType->ClearChildren();
	C_SB_SubType->ScrollToStart();
	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();

	if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_BOOTS )
	{
		for( uint8 type = static_cast<uint8>(E_BRAND_TYPE::E_BRAND_TYPE_ALL); type < static_cast<uint8>(E_BRAND_TYPE::E_BRAND_TYPE_MAX); ++type )
		{
			UBWidget_EquipFilterItem* equipTypeBrand = B_HUD->CreateDynamicWidget<UBWidget_EquipFilterItem>( EDynamicWidgetParts::EquipFilterItem );
			if( equipTypeBrand != nullptr )
			{
				equipTypeBrand->OwnerPannel = this;
				equipTypeBrand->SetEquipFilterBootsBrandItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND, static_cast<E_BRAND_TYPE>(type));
				if( equipTypeBrand->OnClickEquipSubBootsBrandFilter.IsBoundToObject( this ) == false )
				{
					equipTypeBrand->OnClickEquipSubBootsBrandFilter.AddUObject( this, &UBWidget_EquipMain::_OnClickEquipSubBootsBrandFilter );
				}

				C_SB_SubType->AddChild( equipTypeBrand );
				_SubFilterItems.Add( equipTypeBrand );
			}
		}

		_OnClickEquipSubBootsBrandFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND, E_BRAND_TYPE::E_BRAND_TYPE_ALL, true);
	}
	else if( mainFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_EQUIP )
	{
	}
}

void UBWidget_EquipMain::PlayFilterAni( bool isOpen )
{
	if ( isOpen )
	{
		if( _Ani_FilterOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_FilterOpen ) )
			{
				StopAnimation( _Ani_FilterOpen );
			}

			PlayAnimation( _Ani_FilterOpen );
		}
	}
	else
	{
		if( Ani_FilterClose != nullptr )
		{
			if( IsAnimationPlaying( Ani_FilterClose ) )
			{
				StopAnimation( Ani_FilterClose );
			}

			PlayAnimation( Ani_FilterClose );
		}
	}
}

void UBWidget_EquipMain::PlayEquipMainOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_EquipMainOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_EquipMainOpen ) )
			{
				StopAnimation( _Ani_EquipMainOpen );
			}

			PlayAnimation( _Ani_EquipMainOpen );
		}
	}
	else
	{
		if( _Ani_EquipMainClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_EquipMainClose ) )
			{
				StopAnimation( _Ani_EquipMainClose );
			}

			PlayAnimation( _Ani_EquipMainClose );
		}
	}
}

void UBWidget_EquipMain::OnClickEquipMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce /*= false*/ )
{
	if ( isForce == false && _MainFilterType == mainFilterType)
	{
		return;
	}

	_MainFilterType = mainFilterType;

	switch( mainFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_BOOTS:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( true );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( false );
		}
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_EQUIP:
		if( _MainFilterItems.IsValidIndex( 0 ) )
		{
			_MainFilterItems[0]->SelectEquipFilterItem( false );
		}
		if( _MainFilterItems.IsValidIndex( 1 ) )
		{
			_MainFilterItems[1]->SelectEquipFilterItem( true );
		}
		break;
	}

	SetSubEquipItem( mainFilterType );
}

void UBWidget_EquipMain::OnClickMainBrandViewAll( const E_BRAND_TYPE mainBrandType )
{
	_OnClickEquipSubBootsBrandFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND, mainBrandType, true);
}

void UBWidget_EquipMain::_OnClickEquipSubBootsBrandFilter( const E_FILTER_ITEM_TYPE subFilterType, const E_BRAND_TYPE bootsBrandType, bool isForce /*= false*/ )
{
	if ( isForce == false && _SubFilterType == subFilterType && _BootsBrandType  == bootsBrandType )
	{
		return;
	}

	_SubFilterType = subFilterType;
	_BootsBrandType = bootsBrandType;

	for( uint8 typeIndex = static_cast<uint8>(E_BRAND_TYPE::E_BRAND_TYPE_ALL); typeIndex < static_cast<uint8>(E_BRAND_TYPE::E_BRAND_TYPE_MAX); ++typeIndex )
	{
		if( _SubFilterItems.IsValidIndex( typeIndex ) )
		{
			_SubFilterItems[typeIndex]->SelectEquipFilterItem( false );
		}
	}

	if( _SubFilterItems.IsValidIndex( static_cast<uint8>(bootsBrandType) ) )
	{
		_SubFilterItems[static_cast<uint8>(bootsBrandType)]->SelectEquipFilterItem( true );
	}

	BP_EquipBootsFilter_UMG->ResetFilter( _BootsBrandType );
	_BootsFilterInfo.InitFilterInfo();

	_SetEquipItem( subFilterType );
}

void UBWidget_EquipMain::_OnClick_SortBtn()
{
	BP_EquipSort_UMG->SetVisibility( ESlateVisibility::Visible );
	BP_EquipSort_UMG->InitEquipSort( _SortType );
}

void UBWidget_EquipMain::_OnClick_FilterBtn()
{
	BP_EquipBootsFilter_UMG->SetVisibility( ESlateVisibility::Visible );
	BP_EquipBootsFilter_UMG->OnShow();
	PlayFilterAni( true );
}

void UBWidget_EquipMain::_OnClickEquipSortEvent( const E_SORT_TYPE sortType )
{
	if ( sortType != _SortType )
	{
		_SetSort( sortType );
		_SetEquipItem( _SubFilterType );
	}
	
	BP_EquipSort_UMG->SetVisibility( ESlateVisibility::Collapsed );
}

void UBWidget_EquipMain::_OnClickEquipFilterApplyEvent( const FST_BOOTS_FILTER_INFO curBootsFilterInfo )
{
	PlayFilterAni( false );
	BP_EquipBootsFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );

	_BootsFilterInfo = curBootsFilterInfo;

	_UpdateBootsFilter();
}

void UBWidget_EquipMain::_OnClickEquipFilterCancelEvent()
{
	PlayFilterAni(false);
	BP_EquipBootsFilter_UMG->SetVisibility( ESlateVisibility::Collapsed );;
}

void UBWidget_EquipMain::_SetEquipItem( const E_FILTER_ITEM_TYPE equipFilterType )
{
	if ( equipFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND )
	{
		_SetEquipItemBoots();
	}
}

void UBWidget_EquipMain::_SetEquipItemBoots()
{
	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();

	_ArrayBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( _ArrayBootsIndexInfo, _BootsFilterInfo, _SortType, _BootsBrandType );
	_CurScrollInex = 0;
	_MaxScrollInex = _ArrayBootsIndexInfo.Num();
	_UpdateScrollItem();
}

void UBWidget_EquipMain::_UpdateScrollItem()
{
	int32 startIndex = _CurScrollInex;
	int32 endIndex = FMath::Min( _MaxScrollInex , startIndex + SCROLL_ITEM_NUM );
	for( int32 bootsIndex = startIndex; bootsIndex < endIndex; ++bootsIndex )
	{
		UBWidget_BootsSlot* bootsSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_BootsSlot>( EDynamicWidgetParts::BootsSlot );
		if( bootsSlotWidget != nullptr )
		{
			bootsSlotWidget->OwnerPannel = this;			

#if DB_BOOTS_DATA
			bootsSlotWidget->SetBootSlotData_DB( bootsIndex, _ArrayBootsIndexInfo[bootsIndex] );
#else
			bootsSlotWidget->SetBootSlotData( bootsIndex, _ArrayBootsIndexInfo[bootsIndex] );
#endif

			C_SB_Item->AddChild( bootsSlotWidget );
			_CurScrollInex++;
		}
	}
}

void UBWidget_EquipMain::_SetSort( const E_SORT_TYPE sortType )
{
	_SortType = sortType;

	switch( _SortType )
	{
	case E_SORT_TYPE::E_SORT_TYPE_NEW:
		C_Txt_Sort->SetText( GET_BTEXT( 39 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_PRICE_LOW:
		C_Txt_Sort->SetText( GET_BTEXT( 40 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_PRICE_HIGH:
		C_Txt_Sort->SetText( GET_BTEXT( 41 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_LOW:
		C_Txt_Sort->SetText( GET_BTEXT( 42 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_HIGH:
		C_Txt_Sort->SetText( GET_BTEXT( 43 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ABC:
		C_Txt_Sort->SetText( GET_BTEXT( 83 ) );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ABC_REVERS:
		C_Txt_Sort->SetText( GET_BTEXT( 84 ) );
		break;
	default:
		break;
	}
}

void UBWidget_EquipMain::_UpdateBootsFilter()
{
	if( _BootsFilterInfo.IsNotFilter() )
	{
		_OnClickEquipSubBootsBrandFilter( _SubFilterType, _BootsBrandType, true);
		return;
	}

	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();

	_ArrayBootsIndexInfo.Empty();
	GInst->GetBootsIndexInfoByFiltering( _ArrayBootsIndexInfo, _BootsFilterInfo, _SortType, _BootsBrandType );
	_CurScrollInex = 0;
	_MaxScrollInex = _ArrayBootsIndexInfo.Num();
	_UpdateScrollItem();
}
