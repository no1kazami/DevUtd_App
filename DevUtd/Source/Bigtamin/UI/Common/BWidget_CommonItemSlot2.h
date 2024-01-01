// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_CommonItemSlot2.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_CommonItemSlot2 : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_TwoParams( UBWidget_CommonItemSlot, FOnClickItemColorSlot, const int32, const int32 )
	FOnClickItemColorSlot OnClickItemColorSlot;

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCommonImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCommonImage2;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_CommonItem;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_CommonItem;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_SelectLine;

	E_COMMON_ITEM_SLOT_TYPE _SlotType;
	int32 _ContentIndex = 0;
	int32 _ProductIDIndex = -1;
	FString _ProductID;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	UFUNCTION()
		void SetCommonItemSlotData( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex, const int32 productIDIndex, const bool isSelect = false );

	UFUNCTION()
		void SetCommonItemSlotData_DB( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex, const int32 productIDIndex, const bool isSelect = false );

	UFUNCTION()
		void SetSelectLine(bool isSelect);
	UFUNCTION()
		int32 GetProductIndex() { return _ProductIDIndex;	}
	
private:
	UFUNCTION()
		void _OnClick_CommonItem();

	UFUNCTION()
		void _OnSuccessDownLoadCommonImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCommonImage2( UTexture2DDynamic* texturl );
};
