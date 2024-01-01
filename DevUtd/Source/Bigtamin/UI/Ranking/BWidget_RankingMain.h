#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_RankingMain.generated.h"

class UBWidget_Top;
class UBWidget_RankingSort;
class UBWidget_RankingFilter;
class UBWidget_EquipFilterItem;
class UBWidget_RankingTop3;

UCLASS()
class BIGTAMIN_API UBWidget_RankingMain : public UBWidget
{
	GENERATED_BODY()

private:
	static constexpr int32 MAX_MAIN_FILTER = 3;

	UPROPERTY( meta = (BindWidget) ) UBWidget_Top* BP_Top_RankingMain_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingSort* BP_RankingSort_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingFilter* BP_RankingFilter_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingTop3* BP_RankingTop3_Goal;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingTop3* BP_RankingTop3_Assist;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingTop3* BP_RankingTop3_Point;
	UPROPERTY( meta = (BindWidget) ) UBWidget_RankingTop3* BP_RankingTop3_Game;
	UPROPERTY( meta = (BindWidget) ) UScrollBox* C_SB_RankingType;

	UPROPERTY( meta = (BindWidget) ) UCheckBox* C_CB_ExceptionStadium;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_ExceptionStadium;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Filter;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort;
	UPROPERTY( meta = (BindWidget) ) UScrollBox* C_SB_Item;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Goal;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Assist;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Point;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Game;

	UPROPERTY( meta = (BindWidget) )   UBButton* C_Btn_Year_Prev;
	UPROPERTY( meta = (BindWidget) )   UBButton* C_Btn_Year_Next;
	UPROPERTY( meta = (BindWidget) )   UTextBlock* C_Txt_Year;

	UWidgetAnimation* _Ani_FilterOpen;
	FName _Ani_FilterOpenName = "Ani_FilterOpen";
	UWidgetAnimation* Ani_FilterClose;
	FName _Ani_FilterCloseName = "Ani_FilterClose";
	UWidgetAnimation* _Ani_RankingMainOpen;
	FName _Ani_RankingMainOpenName = "Ani_RankingMain_Open";
	UWidgetAnimation* _Ani_RankingMainClose;
	FName _Ani_RankingMainCloseName = "Ani_RankingMain_Close";

	FST_RANKING_FILTER_INFO _RankingFilterInfo;

	E_FILTER_ITEM_TYPE _MainFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	TArray<UBWidget_EquipFilterItem*, TFixedAllocator<MAX_MAIN_FILTER>> _MainFilterItems;
	E_SORT_TYPE _SortType = E_SORT_TYPE::E_SORT_TYPE_GOAL;

	TArray<FString> _YearData;
	FString _NowYear;
	bool bIsExceptionStadium = true;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitRankingMain();
	void UpdateTop3();
	void SetSubRankingItem( const E_FILTER_ITEM_TYPE mainFilterType );
	void PlayRankingMainOpenAni( const bool isOpen );
	void PlayFilterAni( bool isOpen );
	void ChangeSortType( const E_SORT_TYPE sortType );
	E_SORT_TYPE GetSortType()	{ return _SortType; }

	UFUNCTION()
		void OnClickRankingMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce = true );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()	void _OnExceptionStadiumCheckStateChanged( bool isChecked );
	UFUNCTION()	void _OnClick_ExceptionStadiumBtn();
	UFUNCTION()	void _OnClick_SortBtn();
	UFUNCTION()	void _OnClick_FilterBtn();
	UFUNCTION()	void _OnClickRankingSortEvent( const E_SORT_TYPE sortType );
	UFUNCTION()	void _OnClickRankingFilterApplyEvent( const FST_RANKING_FILTER_INFO curRankingFilterInfo );
	UFUNCTION()	void _OnClickRankingFilterCancelEvent();
	UFUNCTION() void _OnClick_YearPrevBtn();
	UFUNCTION() void _OnClick_YearNextBtn();

	void _SetSort( const E_SORT_TYPE sortType );
	void _UpdateYear();
	void _UpdateRankingFilter();
	
};
