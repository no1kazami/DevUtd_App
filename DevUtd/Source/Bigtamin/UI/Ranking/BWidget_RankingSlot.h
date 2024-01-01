#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_RankingSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_RankingSlot : public UBWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_RankingSlot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Num;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Goal;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Assist;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Point;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Game;

	UPROPERTY() FString PlayerName;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( E_FILTER_ITEM_TYPE matchType, E_SORT_TYPE sortType, int32 rankNum, FST_PLAYER_DATA playerData, FString nowYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, bool isExceptionStadium );

private:
	UFUNCTION()
		void _OnClick_RankingSlot();
};
