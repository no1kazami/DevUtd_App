#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_PlayerDetail.generated.h"

class UBWidget_Top;
class UBWidget_BootsOptionSlot;
class UBWidget_PlayerChart;

UCLASS()
class BIGTAMIN_API UBWidget_PlayerDetail : public UBWidget
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void PlayDetailOpenAni( const bool isDetailOpen );
	void SetPlayerData(FString playerName);

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()
		void _OnSuccessDownLoadPlayerDetailImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadPlayerDetailImage( UTexture2DDynamic* texturl );

	void _SetChartInfo();

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerDetailImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerDetailImage;

private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_PlayerDetail_UMG;
	UPROPERTY( meta = (BindWidget) )
		UBWidget_BootsOptionSlot* BP_Player_Option_Slot_UMG;
	UPROPERTY( meta = (BindWidget) )
		UBWidget_PlayerChart* BP_Player_Chart_Goal_UMG;
	UPROPERTY( meta = (BindWidget) )
		UBWidget_PlayerChart* BP_Player_Chart_Assist_UMG;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Player;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_PlayerName;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Goal;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Assist;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_TotalPoint;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Attendance;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Mvp;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Goal;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Assist;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Attendance;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_TotalPoint;
	UPROPERTY( meta = (BindWidget) )
		TWeakObjectPtr<UScrollBox>  C_ScrollBox_Detail;

	UWidgetAnimation* _Ani_DetailOpen;
	FName _Ani_DetailOpenName = "Ani_Detail_Open";
	UWidgetAnimation* _Ani_DetailClose;
	FName _Ani_DetailCloseName = "Ani_Detail_Close";

	FString _PlayerName;
	
};
