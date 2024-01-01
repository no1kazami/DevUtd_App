// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_BootsCompare.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_BootsCompare : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage3;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage3;

private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_BootsCompare_UMG;

	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Name1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Name2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Name3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Brand1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Brand2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Brand3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Studs1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Studs2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Studs3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Upper1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Upper2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Upper3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Silo1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Silo2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Silo3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Ground1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Ground2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Ground3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Fit1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Fit2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Fit3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_BallOfFoot1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_BallOfFoot2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_BallOfFoot3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_HeightOfFoot1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_HeightOfFoot2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_HeightOfFoot3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Length1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Length2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Length3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Weight1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Weight2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Weight3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_CompareWeight2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_CompareWeight3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_WeightArrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_WeightArrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Price1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Price2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Price3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ComparePrice2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ComparePrice3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_PriceArrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_PriceArrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ReleaseDate1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ReleaseDate2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ReleaseDate3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ProductID1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ProductID2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_ProductID3;

	UWidgetAnimation* _Ani_CompareOpen;
	FName _Ani_CompareOpenName = "Ani_Compare_Open";
	UWidgetAnimation* _Ani_CompareClose;
	FName _Ani_CompareCloseName = "Ani_Compare_Close";

	int32 _WeightValue = 0;
	int32 _PriceValue = 0;

	FString _ProductID1;
	FString _ProductID2;
	FString _ProductID3;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void PlayCompareOpenAni( const bool isOpen );

protected:
	virtual bool _OnBackInput() override;
	void _InitBootsCompare();
	void _ClearBootsCompareUI();
	void _SetBootsCompareUI();
	void _SetBootsCompareUI_DB();

	UFUNCTION()
		void _OnSuccessDownLoadCompareImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadCompareImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadCompareImage3( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage3( UTexture2DDynamic* texturl );
};
