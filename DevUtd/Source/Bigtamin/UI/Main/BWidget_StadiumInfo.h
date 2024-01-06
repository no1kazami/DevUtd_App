#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_StadiumInfo.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_StadiumInfo : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_Top* BP_Top_StadiumInfo_UMG;
	UPROPERTY( meta = (BindWidget) ) UScrollBox* C_ScrollBox_StadiumInfo;
	UPROPERTY( meta = (BindWidget) ) UOverlay* C_OL_Contents;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_TMap;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_KakaoNavi;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_NaverMap;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Address;

	UWidgetAnimation* _Ani_StadiumInfoSlotOpen;
	FName _Ani_StadiumInfoSlotOpenName = "Ani_StadiumInfoSlot_Open";
	UWidgetAnimation* _Ani_StadiumInfoSlotClose;
	FName _Ani_StadiumInfoSlotCloseName = "Ani_StadiumInfoSlot_Close";

	FST_STADIUM_INFO_DATA _StadiumInfoData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitStadiumInfo();
	void PlayStadiumInfoSlotOpenAni( const bool isStadiumInfoSlotOpen );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()	void _OnClickStadiumInfoSlotEvent( const FST_STADIUM_INFO_DATA stadiumInfoData );
	UFUNCTION()	void _OnClick_TMap();
	UFUNCTION()	void _OnClick_KakaoNavi();
	UFUNCTION()	void _OnClick_NaverMap();
};
