// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Faq.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Faq : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_Faq_UMG;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_ScrollBox_Faq;
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_OL_Contents;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Contents;


	UWidgetAnimation* _Ani_FaqSlotOpen;
	FName _Ani_FaqSlotOpenName = "Ani_FaqSlot_Open";
	UWidgetAnimation* _Ani_FaqSlotClose;
	FName _Ani_FaqSlotCloseName = "Ani_FaqSlot_Close";

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitFaq();
	void PlayFaqSlotOpenAni( const bool isFaqSlotOpen );

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION()
		void _OnClickFaqSlotEvent( const FST_FAQ_DATA faqSlotData );
};
