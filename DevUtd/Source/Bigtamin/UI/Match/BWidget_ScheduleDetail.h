#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ScheduleDetail.generated.h"

class UBWidget_Top;
class UBWidget_MatchItem;

UCLASS()
class BIGTAMIN_API UBWidget_ScheduleDetail : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_Top* BP_Top_MainScheduleDetail_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MatchItem* BP_MatchItem_UMG;

	UWidgetAnimation* _Ani_ResultDetailOpen;
	FName _Ani_ResultDetailOpenName = "Ani_ResultDetail_Open";
	UWidgetAnimation* _Ani_ResultDetailClose;
	FName _Ani_ResultDetailCloseName = "Ani_ResultDetail_Close";
	FST_MATCH_DATA _MatchData;

	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_TMap;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_KakaoNavi;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_NaverMap;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Address;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( FST_MATCH_DATA matchData );
	void PlayResultDetailOpenAni( const bool isOpen );

protected:
	virtual bool _OnBackInput() override;	

	UFUNCTION()	void _OnClick_TMap();
	UFUNCTION()	void _OnClick_KakaoNavi();
	UFUNCTION()	void _OnClick_NaverMap();
};
