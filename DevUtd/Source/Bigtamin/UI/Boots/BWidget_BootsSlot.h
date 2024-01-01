// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_BootsSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_BootsSlot : public UBWidget
{
	GENERATED_BODY()

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadBootsSlotImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadBootsSlotImage;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_BootsSlot;

	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Boots;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BgBoots;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Logo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ProductName;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Brand;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Studs;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Upper;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Price;

	int32 _SlotIndex;
	int32 _BootsIndex;
	FString _BootsProductID;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetBootSlotData( const int32 slotIndex, const int32 bootsIndex );
	void SetBootSlotData_DB( const int32 slotIndex, const int32 bootsIndex );

private:
	UFUNCTION()
	void _OnClick_BootsSlot();

	UFUNCTION()
		void _OnSuccessDownLoadBootsSlotImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadBootsSlotImage( UTexture2DDynamic* texturl );

};
