#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MainSchedule.generated.h"

class UBWidget_Top;
class UBWidget_EquipFilterItem;

UCLASS()
class BIGTAMIN_API UBWidget_MainSchedule : public UBWidget
{
	GENERATED_BODY()
private:
	static constexpr int32 MAX_MAIN_FILTER = 3;

	UPROPERTY( meta = (BindWidget) )   UBWidget_Top* BP_Top_ScheduleMain_UMG;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_ScheduleType;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_Item;

	UWidgetAnimation* _Ani_ScheduleMainOpen;
	FName _Ani_ScheduleMainOpenName = "Ani_ScheduleMain_Open";
	UWidgetAnimation* _Ani_ScheduleMainClose;
	FName _Ani_ScheduleMainCloseName = "Ani_ScheduleMain_Close";

	E_FILTER_ITEM_TYPE _MainFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	TArray<UBWidget_EquipFilterItem*, TFixedAllocator<MAX_MAIN_FILTER>> _MainFilterItems;

	TArray<FST_MATCH_DATA> _ArrayMatchData;
	int32 _CurScrollInex = 0;
	int32 _MaxScrollInex = 0;
	float _UpdateScrollTime = 0.f;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitScheduleMain();
	void SetSubScheduleItem( const E_FILTER_ITEM_TYPE mainFilterType );
	void PlayScheduleMainOpenAni( const bool isOpen );

	UFUNCTION() void OnClickScheduleMainFilter( const E_FILTER_ITEM_TYPE mainFilterType, bool isForce = true );

protected:
	virtual bool _OnBackInput() override;

private:
	void _UpdateScrollItem();
	
};
