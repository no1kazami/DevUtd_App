#include "BWidget_EquipSort.h"


void UBWidget_EquipSort::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Sort_Cancel, &UBWidget_EquipSort::_OnClick_SortCancel );
	ButtonDelegate_Clicked( this, C_Btn_Sort_New, &UBWidget_EquipSort::_OnClick_SortNew );
	ButtonDelegate_Clicked( this, C_Btn_Sort_PriceLow, &UBWidget_EquipSort::_OnClick_SortPriceLow );
	ButtonDelegate_Clicked( this, C_Btn_Sort_PriceHigh, &UBWidget_EquipSort::_OnClick_SortPriceHigh );
	ButtonDelegate_Clicked( this, C_Btn_Sort_WeightLow, &UBWidget_EquipSort::_OnClick_SortWeightLow );
	ButtonDelegate_Clicked( this, C_Btn_Sort_WeightHigh, &UBWidget_EquipSort::_OnClick_SortWeightHigh );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Abc, &UBWidget_EquipSort::_OnClick_SortAbc );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Abc_Reverse, &UBWidget_EquipSort::_OnClick_SortAbcReverse );
}

void UBWidget_EquipSort::OnClose()
{
	Super::OnClose();
}

void UBWidget_EquipSort::InitEquipSort( const E_SORT_TYPE sortType )
{
	_SortType = sortType;
	_UpdateSortTextColor();
}

void UBWidget_EquipSort::_OnClick_SortCancel()
{
	this->SetVisibility( ESlateVisibility::Collapsed );
}

void UBWidget_EquipSort::_OnClick_SortNew()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_NEW );
}

void UBWidget_EquipSort::_OnClick_SortPriceLow()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_PRICE_LOW );
}

void UBWidget_EquipSort::_OnClick_SortPriceHigh()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_PRICE_HIGH );
}

void UBWidget_EquipSort::_OnClick_SortWeightLow()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_WEIGHT_LOW );
}

void UBWidget_EquipSort::_OnClick_SortWeightHigh()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_WEIGHT_HIGH );
}

void UBWidget_EquipSort::_OnClick_SortAbc()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_ABC );
}

void UBWidget_EquipSort::_OnClick_SortAbcReverse()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_ABC_REVERS );
}

void UBWidget_EquipSort::_ClickSortBtn( const E_SORT_TYPE sortType )
{
	_SortType = sortType;
	OnClickEquipSort.Broadcast( _SortType );
}

void UBWidget_EquipSort::_UpdateSortTextColor()
{
	C_Txt_Sort_New->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_PriceLow->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_PriceHigh->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_WeightLow->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_WeightHigh->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_Abc->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_Abc_Reverse->SetColorAndOpacity( Color_GrayFont );

	switch( _SortType )
	{
	case E_SORT_TYPE::E_SORT_TYPE_NEW:
		C_Txt_Sort_New->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_PRICE_LOW:
		C_Txt_Sort_PriceLow->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_PRICE_HIGH:
		C_Txt_Sort_PriceHigh->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_LOW:
		C_Txt_Sort_WeightLow->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_WEIGHT_HIGH:
		C_Txt_Sort_WeightHigh->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ABC:
		C_Txt_Sort_Abc->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ABC_REVERS:
		C_Txt_Sort_Abc_Reverse->SetColorAndOpacity( Color_SortSelectFont );
		break;
	default:
		break;
	}
}
