#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MainRankingSlot.generated.h"

UCLASS()
class BIGTAMIN_API UBWidget_MainRankingSlot : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage1;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage1;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage3;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage3;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage4;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage4;

private:
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_More;
	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Medal1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Value1;

	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Medal2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Value2;

	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Medal3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Value3;

	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Medal4;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person4;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name4;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team4;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Value4;

	UPROPERTY( meta = (BindWidget) )
		UGridPanel* C_Grid_Rank1;
	UPROPERTY( meta = (BindWidget) )
		UGridPanel* C_Grid_Rank2;
	UPROPERTY( meta = (BindWidget) )
		UGridPanel* C_Grid_Rank3;
	UPROPERTY( meta = (BindWidget) )
		UGridPanel* C_Grid_Rank4;

	FString _PlayerName1;
	FString _PlayerName2;
	FString _PlayerName3;
	FString _PlayerName4;

	E_RANKING_TYPE _RankType;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( const E_RANKING_TYPE rankingType);

private:
	UFUNCTION() void _OnSuccessDownLoadPlayerImage1( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage1( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnSuccessDownLoadPlayerImage2( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage2( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnSuccessDownLoadPlayerImage3( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage3( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnSuccessDownLoadPlayerImage4( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage4( UTexture2DDynamic* texturl );
	UFUNCTION()	void _OnClick_MoreBtn();

	void _SetDataAttendance();
	void _SetDataGoal();
	void _SetDataAssist();
	void _SetDataPoint();
	void _SetDataYearMvp();
	void _SetDataYearKing();
};
