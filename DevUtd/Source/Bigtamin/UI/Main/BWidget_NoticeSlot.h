// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_NoticeSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_NoticeSlot : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_NoticeSlot, FOnClickNoticeSlot, const FST_NOTICE_DATA )
	FOnClickNoticeSlot OnClickNoticeSlot;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_NoticeSlot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Date;

	FST_NOTICE_DATA _NoticeData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetNoticeSlotData( FST_NOTICE_DATA noticeSlotData );

private:
	UFUNCTION()
		void _OnClick_NoticeSlot();
};
