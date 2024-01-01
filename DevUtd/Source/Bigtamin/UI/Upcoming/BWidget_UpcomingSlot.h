// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_UpcomingSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_UpcomingSlot : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadUpcomingImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadUpcomingImage;

private:
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Date;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Year;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Month;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Contents;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_UpcomingSlot;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Logo;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product;

	FST_UPCOMING_DATA _UpcomingData;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetUpcomingSlotData( FST_UPCOMING_DATA slotData, bool isHidden );

private:
	UFUNCTION()
		void _OnSuccessDownLoadUpcomingImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadUpcomingImage( UTexture2DDynamic* texturl );
};
