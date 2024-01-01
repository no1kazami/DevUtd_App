#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MainResult.generated.h"

class UBWidget_Top;
class UBWidget_EquipFilterItem;

UCLASS()
class BIGTAMIN_API UBWidget_MainResult : public UBWidget
{
	GENERATED_BODY()
private:
	static constexpr int32 MAX_MAIN_FILTER = 3;

	UPROPERTY( meta = (BindWidget) )   UBWidget_Top* BP_Top_ResultMain_UMG;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_ResultType;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_Item;
	UPROPERTY( meta = (BindWidget) )   UBButton* C_Btn_Year_Prev;
	UPROPERTY( meta = (BindWidget) )   UBButton* C_Btn_Year_Next;
	UPROPERTY( meta = (BindWidget) )   UTextBlock* C_Txt_Year;

	UWidgetAnimation* _Ani_ResultMainOpen;
	FName _Ani_ResultMainOpenName = "Ani_ResultMain_Open";
	UWidgetAnimation* _Ani_ResultMainClose;
	FName _Ani_ResultMainCloseName = "Ani_ResultMain_Close";

	E_FILTER_ITEM_TYPE _MainFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	TArray<UBWidget_EquipFilterItem*, TFixedAllocator<MAX_MAIN_FILTER>> _MainFilterItems;

	TArray<FString> _YearData;
	FString _NowYear;
	TArray<FST_MATCH_DATA> _ArrayMatchData;
	int32 _CurScrollInex = 0;
	int32 _MaxScrollInex = 0;
	float _UpdateScrollTime = 0.f;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitResultMain();
	void SetSubResultItem( const E_FILTER_ITEM_TYPE mainFilterType );
	void PlayResultMainOpenAni( const bool isOpen );

	UFUNCTION() void OnClickResultMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce = true );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION() void _OnClick_YearPrevBtn();
	UFUNCTION() void _OnClick_YearNextBtn();
	void _UpdateScrollItem();
	void _UpdateYear();

};