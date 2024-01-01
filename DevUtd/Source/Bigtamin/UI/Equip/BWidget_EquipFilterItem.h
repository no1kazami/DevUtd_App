#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_EquipFilterItem.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_EquipFilterItem : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_TwoParams( UBWidget_EquipFilterItem, FOnClickEquipFilter, const E_FILTER_ITEM_TYPE, const bool )
	FOnClickEquipFilter OnClickEquipFilter;
	DECLARE_EVENT_ThreeParams( UBWidget_EquipFilterItem, FOnClickEquipSubBootsBrandFilter, const E_FILTER_ITEM_TYPE, const E_BRAND_TYPE, const bool )
	FOnClickEquipSubBootsBrandFilter OnClickEquipSubBootsBrandFilter;
	DECLARE_EVENT_TwoParams( UBWidget_EquipFilterItem, FOnClickDetailInfoFilter, const E_FILTER_ITEM_TYPE, const bool )
	FOnClickDetailInfoFilter OnClickDetailInfoFilter;
	DECLARE_EVENT_TwoParams( UBWidget_EquipFilterItem, FOnClickRankingFilter, const E_FILTER_ITEM_TYPE, const bool )
	FOnClickEquipFilter OnClickRankingFilter;

private:
	UPROPERTY( meta = (BindWidget) )
	UBButton* C_Btn_EquipFilter;
	UPROPERTY( meta = (BindWidget) )
	UTextBlock*	C_Txt_EquipFilter;
	UPROPERTY( meta = (BindWidget) )
	UImage* C_Img_SelectLine;

	E_FILTER_ITEM_TYPE _FilterType;
	E_BRAND_TYPE _FilterBootsBrandType;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;
	void SetEquipFilterItem( const E_FILTER_ITEM_TYPE filterType, const int32 stringIndex );
	void SetEquipFilterBootsBrandItem( const E_FILTER_ITEM_TYPE filterType, const E_BRAND_TYPE bootsBrandType );
	void SelectEquipFilterItem(const bool isSelect) const;
	void SetDetailInfoFilterItem( const E_FILTER_ITEM_TYPE filterType, const int32 stringIndex );
	void SelectDetailInfoFilterItem( const bool isSelect ) const;

private:
	UFUNCTION()
	void _OnClick_EquipFilter();
	
};
