// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Notice.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Notice : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_Notice_UMG;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_ScrollBox_Notice;
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_OL_Contents;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Date;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Contents;


	UWidgetAnimation* _Ani_NotiSlotOpen;
	FName _Ani_NotiSlotOpenName = "Ani_NotiSlot_Open";
	UWidgetAnimation* _Ani_NotiSlotClose;
	FName _Ani_NotiSlotCloseName = "Ani_NotiSlot_Close";
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitNotice();
	void PlayNotiSlotOpenAni( const bool isNotiSlotOpen );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()
		void _OnClickNoticeSlotEvent( const FST_NOTICE_DATA noticeSlotData );
};
