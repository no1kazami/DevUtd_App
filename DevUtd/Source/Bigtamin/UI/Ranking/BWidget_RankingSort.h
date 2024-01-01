#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_RankingSort.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_RankingSort : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_RankingSort, FOnClickRankingSort, const E_SORT_TYPE )
	FOnClickRankingSort OnClickRankingSort;

private:
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Cancel;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Goal;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Assist;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Point;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Sort_Game;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Goal;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Assist;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Point;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Sort_Game;

	E_SORT_TYPE _SortType;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitRankingSort( const E_SORT_TYPE sortType );

private:
	UFUNCTION() void _OnClick_SortCancel();
	UFUNCTION() void _OnClick_SortGoal();
	UFUNCTION() void _OnClick_SortAssist();
	UFUNCTION() void _OnClick_SortPoint();
	UFUNCTION() void _OnClick_SortGame();

	void _ClickSortBtn( const E_SORT_TYPE sortType );
	void _UpdateSortTextColor();	
};
