// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_EquipBootsFilterItem.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_EquipBootsFilterItem : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterBrand, const E_BRAND_TYPE, const bool )
	FOnClickFilterBrand OnClickFilterBrand;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterCollection, const E_COLLECTION_TYPE, const bool )
	FOnClickFilterCollection OnClickFilterCollection;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterModel, const E_MODEL_TYPE, const bool )
	FOnClickFilterModel OnClickFilterModel;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterStuds, const E_STUDS_TYPE, const bool )
	FOnClickFilterStuds OnClickFilterStuds;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterSilo, const E_SILO_TYPE, const bool )
	FOnClickFilterSilo OnClickFilterSilo;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterStadium, const FString, const bool )
	FOnClickFilterStadium OnClickFilterStadium;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterTeam, const FString, const bool )
	FOnClickFilterTeam OnClickFilterTeam;
	DECLARE_EVENT_TwoParams( UBWidget_EquipBootsFilterItem, FOnClickFilterMonth, const int32, const bool )
	FOnClickFilterMonth OnClickFilterMonth;


private:
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_BootsFilterItem;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_BootsFilterItem;
	UPROPERTY( meta = (BindWidget) ) 
		UTextBlock* C_Txt_BootsFilterItem;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count;

	E_BRAND_TYPE _BrandType = E_BRAND_TYPE::E_BRAND_TYPE_MAX;
	E_BOOTS_FILTER_TYPE _FilterType = E_BOOTS_FILTER_TYPE::NONE;
	E_COLLECTION_TYPE _CollectionType = E_COLLECTION_TYPE::NONE;
	E_MODEL_TYPE _ModelType = E_MODEL_TYPE::NONE;
	E_STUDS_TYPE _StudsType = E_STUDS_TYPE::E_STUDS_NONE;
	E_SILO_TYPE _SiloType = E_SILO_TYPE::E_SILO_TYPE_NONE;
	FString _StadiumType;
	FString _TeamType;
	int32 _MonthType;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetBootsFilterData_Brand( E_BRAND_TYPE brandType, bool isChecked, int32 itemCount );
	void SetBootsFilterData_Collection( E_COLLECTION_TYPE collectionType, bool isChecked, int32 itemCount );
	void SetBootsFilterData_Model( E_MODEL_TYPE modelType, bool isChecked, int32 itemCount );
	void SetBootsFilterData_Studs( E_STUDS_TYPE studsType, bool isChecked, int32 itemCount );
	void SetBootsFilterData_Silo( E_SILO_TYPE siloType, bool isChecked, int32 itemCount );

	void SetRankingFilterData_Stadium( FString stadiumType, bool isChecked, int32 itemCount );
	void SetRankingFilterData_Team( FString teamType, bool isChecked, int32 itemCount );
	void SetRankingFilterData_Month( int32 monthType, bool isChecked, int32 itemCount );

	void ResetFilterItem();
	ECheckBoxState GetFilterCheckState() const;
	E_BRAND_TYPE GetBrandType() const { return _BrandType; }
	E_COLLECTION_TYPE GetCollectionType() const { return _CollectionType; }
	E_MODEL_TYPE GetModelType() const {	return _ModelType;	}
	E_STUDS_TYPE GetStudsType() const {	return _StudsType;	}
	E_SILO_TYPE GetSiloType() const { return _SiloType; }

private:
	UFUNCTION()
		void _OnClick_BootsFilterItem();
	UFUNCTION()
		void _OnBootsFilterCheckStateChanged( bool isChecked );

	void _UpdateCheckBox();
};
