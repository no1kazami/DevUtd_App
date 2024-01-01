#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_EquipMain.generated.h"

class UBWidget_Top;
class UBWidget_EquipFilterItem;
class UBWidget_EquipSort;
class UBWidget_EquipBootsFilter;

UCLASS()
class BIGTAMIN_API UBWidget_EquipMain : public UBWidget
{
	GENERATED_BODY()
private:
	static constexpr int32 MAX_MAIN_FILTER = 2;

	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_EquipMain_UMG;
	UPROPERTY( meta = (BindWidget) )
		UBWidget_EquipSort* BP_EquipSort_UMG;
	UPROPERTY( meta = (BindWidget) )
		UBWidget_EquipBootsFilter* BP_EquipBootsFilter_UMG;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_SB_EquipType;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_SB_SubType;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_SB_Item;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Sort;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Sort;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Filter;

	E_FILTER_ITEM_TYPE _MainFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	E_FILTER_ITEM_TYPE _SubFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE ;
	E_BRAND_TYPE _BootsBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL;
	TArray<UBWidget_EquipFilterItem*, TFixedAllocator<MAX_MAIN_FILTER>> _MainFilterItems;
	TArray<UBWidget_EquipFilterItem*> _SubFilterItems;
	E_SORT_TYPE _SortType;

	UWidgetAnimation* _Ani_FilterOpen;
	FName _Ani_FilterOpenName = "Ani_FilterOpen";
	UWidgetAnimation* Ani_FilterClose;
	FName _Ani_FilterCloseName = "Ani_FilterClose";
	UWidgetAnimation* _Ani_EquipMainOpen;
	FName _Ani_EquipMainOpenName = "Ani_EquipMain_Open";
	UWidgetAnimation* _Ani_EquipMainClose;
	FName _Ani_EquipMainCloseName = "Ani_EquipMain_Close";

	FST_BOOTS_FILTER_INFO _BootsFilterInfo;

	TArray<int> _ArrayBootsIndexInfo;
	int32 _CurScrollInex = 0;
	int32 _MaxScrollInex = 0;
	float _UpdateScrollTime = 0.f;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitEquipMain();
	void SetSubEquipItem( const E_FILTER_ITEM_TYPE mainFilterType );
	void PlayFilterAni(bool isOpen);
	void PlayEquipMainOpenAni( const bool isOpen );
	E_SORT_TYPE GetSortType() { return _SortType; }
	E_BRAND_TYPE GetBrandType() { return _BootsBrandType; }

	UFUNCTION()
		void OnClickEquipMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce = true );

	UFUNCTION()
		void OnClickMainBrandViewAll( const E_BRAND_TYPE mainBrandType );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()
		void _OnClickEquipSubBootsBrandFilter( const E_FILTER_ITEM_TYPE subFilterType, const E_BRAND_TYPE bootsBrandType, bool isForce = true );
	UFUNCTION()
		void _OnClick_SortBtn();
	UFUNCTION()
		void _OnClick_FilterBtn();

	UFUNCTION()
		void _OnClickEquipSortEvent( const E_SORT_TYPE sortType );
	UFUNCTION()
		void _OnClickEquipFilterApplyEvent( const FST_BOOTS_FILTER_INFO curBootsFilterInfo );
	UFUNCTION()
		void _OnClickEquipFilterCancelEvent();

	void _SetEquipItem(const E_FILTER_ITEM_TYPE equipFilterType);
	void _SetEquipItemBoots();
	void _UpdateScrollItem();
	void _SetSort(const E_SORT_TYPE sortType);
	void _UpdateBootsFilter();
};
