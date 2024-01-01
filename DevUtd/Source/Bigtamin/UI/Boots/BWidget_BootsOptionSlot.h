// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_BootsOptionSlot.generated.h"

/**
 * 
 */
UCLASS()
class BIGTAMIN_API UBWidget_BootsOptionSlot : public UBWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void OnClose() override;	

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadOptionImage;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadOptionImage2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadOptionImage3;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadOptionImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadOptionImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadOptionImage3;

private:
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_CompareAdd;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_UpDown;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_UpDown;
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Overlay_Select;

	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Compare1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Compare2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Compare3;

	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Cancel1;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Cancel2;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Cancel3;

	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_SelectCompare;

	FString _ProductID1;
	FString _ProductID2;
	FString _ProductID3;

private:
	UFUNCTION()
		void _Init_OverlaySelect();
	UFUNCTION()
		void _OnClick_CompareAdd();
	UFUNCTION()
		void _OnClick_UpDown();
	UFUNCTION()
		void _OnClick_Cancel1();
	UFUNCTION()
		void _OnClick_Cancel2();
	UFUNCTION()
		void _OnClick_Cancel3();
	UFUNCTION()
		void _OnClick_SelectCompare();

	UFUNCTION()
		void _ResetCompareSlot();
	UFUNCTION()
		void _ResetCompareSlot_DB();	

	UFUNCTION()
		void _OnSuccessDownLoadOptionImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadOptionImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadOptionImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadOptionImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadOptionImage3( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadOptionImage3( UTexture2DDynamic* texturl );
};
