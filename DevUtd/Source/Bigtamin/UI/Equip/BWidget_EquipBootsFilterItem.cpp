// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_EquipBootsFilterItem.h"
#include "Bigtamin.h"


void UBWidget_EquipBootsFilterItem::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_BootsFilterItem, &UBWidget_EquipBootsFilterItem::_OnClick_BootsFilterItem );

	C_CB_BootsFilterItem->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_EquipBootsFilterItem::_OnBootsFilterCheckStateChanged );
	C_CB_BootsFilterItem->OnCheckStateChanged.AddDynamic( this, &UBWidget_EquipBootsFilterItem::_OnBootsFilterCheckStateChanged );
}

void UBWidget_EquipBootsFilterItem::OnClose()
{
	Super::OnClose();
}

void UBWidget_EquipBootsFilterItem::_OnClick_BootsFilterItem()
{
	C_CB_BootsFilterItem->SetCheckedState( C_CB_BootsFilterItem->GetCheckedState() == ECheckBoxState::Checked ? ECheckBoxState::Unchecked : ECheckBoxState::Checked );
	_OnBootsFilterCheckStateChanged( C_CB_BootsFilterItem->GetCheckedState() == ECheckBoxState::Checked );
}

void UBWidget_EquipBootsFilterItem::_OnBootsFilterCheckStateChanged( bool isChecked )
{
	_UpdateCheckBox();

	switch( _FilterType )
	{
	case E_BOOTS_FILTER_TYPE::BRAND:
		OnClickFilterBrand.Broadcast( _BrandType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::COLLECTION:
		OnClickFilterCollection.Broadcast( _CollectionType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::MODEL:
		OnClickFilterModel.Broadcast( _ModelType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::STUDS:
		OnClickFilterStuds.Broadcast( _StudsType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::SILO:
		OnClickFilterSilo.Broadcast( _SiloType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::STADIUM:
		OnClickFilterStadium.Broadcast( _StadiumType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::AWAY_TEAM:
		OnClickFilterTeam.Broadcast( _TeamType, isChecked );
		break;
	case E_BOOTS_FILTER_TYPE::MONTH:
		OnClickFilterMonth.Broadcast( _MonthType, isChecked );
		break;
	default:
		break;
	}
}

void UBWidget_EquipBootsFilterItem::_UpdateCheckBox()
{
	// 색상 셋팅
	ECheckBoxState checkState = C_CB_BootsFilterItem->GetCheckedState();
	C_Img_BG->SetColorAndOpacity( (checkState == ECheckBoxState::Unchecked) ? Color_FilterGray : Color_Black );
	C_Txt_BootsFilterItem->SetColorAndOpacity( (checkState == ECheckBoxState::Unchecked) ? Color_GrayFont : Color_White );
	C_Txt_Count->SetColorAndOpacity( (checkState == ECheckBoxState::Unchecked) ? Color_SoftGrayFont : Color_White );
}

void UBWidget_EquipBootsFilterItem::SetBootsFilterData_Brand( E_BRAND_TYPE brandType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::BRAND;
	_BrandType = brandType;
	C_Txt_BootsFilterItem->SetText( UFBMUtil::BrandNameText( brandType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 136 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );

	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetBootsFilterData_Collection( E_COLLECTION_TYPE collectionType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::COLLECTION;
	_CollectionType = collectionType;
	C_Txt_BootsFilterItem->SetText( UFBMUtil::CollectionText( _CollectionType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 136 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetBootsFilterData_Model( E_MODEL_TYPE modelType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::MODEL;
	_ModelType = modelType;
	C_Txt_BootsFilterItem->SetText( UFBMUtil::ModelText( _ModelType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 136 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetBootsFilterData_Studs( E_STUDS_TYPE studsType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::STUDS;
	_StudsType = studsType;
	C_Txt_BootsFilterItem->SetText( UFBMUtil::StudsNameText( _StudsType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 136 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetBootsFilterData_Silo( E_SILO_TYPE siloType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::SILO;
	_SiloType = siloType;
	C_Txt_BootsFilterItem->SetText( UFBMUtil::SiloNameText( _SiloType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 136 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetRankingFilterData_Stadium( FString stadiumType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::STADIUM;
	_StadiumType = stadiumType;
	C_Txt_BootsFilterItem->SetText( FText::FromString( _StadiumType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 57 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetRankingFilterData_Team( FString teamType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::AWAY_TEAM;
	_TeamType = teamType;
	C_Txt_BootsFilterItem->SetText( FText::FromString( _TeamType ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 57 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::SetRankingFilterData_Month( int32 monthType, bool isChecked, int32 itemCount )
{
	_FilterType = E_BOOTS_FILTER_TYPE::MONTH;
	_MonthType = monthType;
	C_Txt_BootsFilterItem->SetText( FText::Format( GET_BTEXT( 62 ), FText::AsNumber( _MonthType ) ) );
	C_Txt_Count->SetText( FText::Format( GET_BTEXT( 57 ), FText::AsNumber( itemCount ) ) );

	C_CB_BootsFilterItem->SetCheckedState( isChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked );
	_UpdateCheckBox();
}

void UBWidget_EquipBootsFilterItem::ResetFilterItem()
{
	if( C_CB_BootsFilterItem->GetCheckedState() != ECheckBoxState::Unchecked )
	{
		C_CB_BootsFilterItem->SetCheckedState( ECheckBoxState::Unchecked );
		_UpdateCheckBox();
	}
}

ECheckBoxState UBWidget_EquipBootsFilterItem::GetFilterCheckState() const
{
	return C_CB_BootsFilterItem->GetCheckedState();
}
