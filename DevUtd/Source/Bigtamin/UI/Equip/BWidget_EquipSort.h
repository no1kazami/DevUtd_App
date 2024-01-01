#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_EquipSort.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_EquipSort : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_EquipSort, FOnClickEquipSort, const E_SORT_TYPE )
	FOnClickEquipSort OnClickEquipSort;

private:
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Cancel;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_New;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_PriceLow;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_PriceHigh;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_WeightLow;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_WeightHigh;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Abc;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Abc_Reverse;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_New;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_PriceLow;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_PriceHigh;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_WeightLow;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_WeightHigh;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Abc;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Abc_Reverse;

	E_SORT_TYPE _SortType;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitEquipSort( const E_SORT_TYPE sortType );

private:
	UFUNCTION() void _OnClick_SortCancel();
	UFUNCTION() void _OnClick_SortNew();
	UFUNCTION() void _OnClick_SortPriceLow();
	UFUNCTION() void _OnClick_SortPriceHigh();
	UFUNCTION() void _OnClick_SortWeightLow();
	UFUNCTION() void _OnClick_SortWeightHigh();
	UFUNCTION() void _OnClick_SortAbc();
	UFUNCTION() void _OnClick_SortAbcReverse();

	void _ClickSortBtn( const E_SORT_TYPE sortType );
	void _UpdateSortTextColor();
};
