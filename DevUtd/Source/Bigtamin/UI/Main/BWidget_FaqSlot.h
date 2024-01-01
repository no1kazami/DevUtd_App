// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_FaqSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_FaqSlot : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_FaqSlot, FOnClickFaqSlot, const FST_FAQ_DATA )
	FOnClickFaqSlot OnClickFaqSlot;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_FaqSlot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;

	FST_FAQ_DATA _FaqData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetFaqSlotData( FST_FAQ_DATA faqSlotData );

private:
	UFUNCTION()
		void _OnClick_FaqSlot();
};
