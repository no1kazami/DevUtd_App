#include "BWidget_EquipFilterItem.h"
#include "Bigtamin.h"


void UBWidget_EquipFilterItem::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_EquipFilter, &UBWidget_EquipFilterItem::_OnClick_EquipFilter );

	_FilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	_FilterBootsBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
}

void UBWidget_EquipFilterItem::OnClose()
{
	Super::OnClose();
}

void UBWidget_EquipFilterItem::SetEquipFilterItem( const E_FILTER_ITEM_TYPE filterType, const int32 stringIndex )
{
	_FilterType = filterType;

	C_Txt_EquipFilter->SetText( GET_BTEXT( stringIndex ) );
}

void UBWidget_EquipFilterItem::SetEquipFilterBootsBrandItem( const E_FILTER_ITEM_TYPE filterType, const E_BRAND_TYPE bootsBrandType )
{
	_FilterType = filterType;
	_FilterBootsBrandType = bootsBrandType;

	C_Txt_EquipFilter->SetText( UFBMUtil::BrandNameText( bootsBrandType ) );
}

void UBWidget_EquipFilterItem::SelectEquipFilterItem( const bool isSelect ) const
{
	C_Img_SelectLine->SetVisibility( isSelect ? ESlateVisibility::Visible : ESlateVisibility::Hidden );

	C_Txt_EquipFilter->SetColorAndOpacity( isSelect ? Color_StarBucksGrayFont : Color_GrayFont );
}

void UBWidget_EquipFilterItem::SetDetailInfoFilterItem( const E_FILTER_ITEM_TYPE filterType, const int32 stringIndex )
{
	_FilterType = filterType;
	C_Txt_EquipFilter->SetText( GET_BTEXT( stringIndex ) );
}

void UBWidget_EquipFilterItem::SelectDetailInfoFilterItem( const bool isSelect ) const
{
	C_Img_SelectLine->SetVisibility( isSelect ? ESlateVisibility::Visible : ESlateVisibility::Hidden );

	C_Txt_EquipFilter->SetColorAndOpacity( isSelect ? Color_StarBucksGrayFont : Color_GrayFont );
}

void UBWidget_EquipFilterItem::_OnClick_EquipFilter()
{
	switch( _FilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_FRONT:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_COACH:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_A:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PLAYER_TEAM_B:
		OnClickRankingFilter.Broadcast( _FilterType, false );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_BOOTS:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_MAIN_EQUIP:
		OnClickEquipFilter.Broadcast( _FilterType, false );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND:
		OnClickEquipSubBootsBrandFilter.Broadcast( _FilterType, _FilterBootsBrandType, false );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_DAY:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_WEEK:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_MONTH:
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO:
		OnClickDetailInfoFilter.Broadcast( _FilterType, false );
		break;
	default:
		break;
	}
}
