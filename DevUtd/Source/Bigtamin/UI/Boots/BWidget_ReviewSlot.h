// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ReviewSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_ReviewSlot : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadReviewImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadReviewImage;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_ReviewSlot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Source;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Review;
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_OL_NotInfo;

	FST_REVIEW_DATA _ReviewData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetReviewSlotData( FST_REVIEW_DATA slotData );
	void SetNotInfo( bool isNotInfo );

private:
	UFUNCTION()
		void _OnClick_ReviewSlot();
	UFUNCTION()
		void _OnSuccessDownLoadReviewImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadReviewImage( UTexture2DDynamic* texturl );
	
};
