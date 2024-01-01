#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_PlayerMain.generated.h"

class UBWidget_Top;
class UBWidget_EquipFilterItem;

UCLASS()
class BIGTAMIN_API UBWidget_PlayerMain : public UBWidget
{
	GENERATED_BODY()
private:
	static constexpr int32 MAX_MAIN_FILTER = 4;

	UPROPERTY( meta = (BindWidget) )   UBWidget_Top* BP_Top_PlayerMain_UMG;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_PlayerType;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_Item;

	UWidgetAnimation* _Ani_ResultMainOpen;
	FName _Ani_ResultMainOpenName = "Ani_ResultMain_Open";
	UWidgetAnimation* _Ani_ResultMainClose;
	FName _Ani_ResultMainCloseName = "Ani_ResultMain_Close";

	E_FILTER_ITEM_TYPE _MainFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;
	TArray<UBWidget_EquipFilterItem*, TFixedAllocator<MAX_MAIN_FILTER>> _MainFilterItems;

	TArray<FString> _PlaterNameData;
	
	int32 _CurScrollInex = 0;
	int32 _MaxScrollInex = 0;
	float _UpdateScrollTime = 0.f;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitPlayerMain();
	void SetSubResultItem( const E_FILTER_ITEM_TYPE mainFilterType );
	void PlayResultMainOpenAni( const bool isOpen );

	UFUNCTION() void OnClickPlayerMainTab( const E_FILTER_ITEM_TYPE mainTabType, bool isForce = true );

protected:
	virtual bool _OnBackInput() override;

private:
	void _UpdateScrollItem();
	
};
