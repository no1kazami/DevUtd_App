// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_CommonItemSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_CommonItemSlot : public UBWidget
{
	GENERATED_BODY()	
public:
	DECLARE_EVENT_OneParam(UBWidget_CommonItemSlot, FOnClickCommonItemSlot, const int32)
	FOnClickCommonItemSlot OnClickCommonItemSlot;

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCommonImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCommonImage;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_CommonItem;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_ItemBG;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_CommonItem;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_CommonItem;
	UPROPERTY( meta = (BindWidget) )
		UScaleBox* C_ScaleBox_Txt;

	E_COMMON_ITEM_SLOT_TYPE _SlotType;
	int32 _ContentIndex = 0;
	int32 _ProductIDIndex = -1;
	FString _ProductID;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	UFUNCTION()
		void SetCommonItemSlotData( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex );
	UFUNCTION()
		void SetCommonItemSlotData_DB( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex );
	
private:
	UFUNCTION()
		void _OnClick_CommonItem();
	UFUNCTION()
		void _OnSuccessDownLoadCommonImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCommonImage( UTexture2DDynamic* texturl );
	
};
