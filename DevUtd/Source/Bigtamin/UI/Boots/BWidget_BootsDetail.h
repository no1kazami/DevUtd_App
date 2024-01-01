// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "UI/Base/BWidget_SwipeScroll.h"
#include "BWidget_BootsDetail.generated.h"

#define MAIN_BOOTS_COLOR_SLOT 99

class UBWidget_Top;
class UBWidget_BootsOptionSlot;
class UBWidget_EquipFilterItem;
class UBWidget_CommonItemSlot2;

UCLASS()
class BIGTAMIN_API UBWidget_BootsDetail : public UBWidget //UBWidget_SwipeScroll
{
	GENERATED_BODY()

public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadDetailImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadDetailImage;

private:
	UPROPERTY( meta = (BindWidget) )
	UBWidget_Top* BP_Top_BootsDetail_UMG;
	UPROPERTY( meta = (BindWidget) )
	UBWidget_EquipFilterItem* BP_ProductInfo_UMG;
	UPROPERTY( meta = (BindWidget) )
	UBWidget_EquipFilterItem* BP_ShopInfo_UMG;
	UPROPERTY( meta = (BindWidget) )
	UBWidget_EquipFilterItem* BP_Review_UMG;
	UPROPERTY( meta = (BindWidget) )
	UBWidget_BootsOptionSlot* BP_Boots_Option_Slot_UMG;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UScrollBox>  C_ScrollBox_Detail;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UScrollBox>  C_ScrollBox_ShopInfo;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UScrollBox>  C_ScrollBox_ReviewInfo;
	UPROPERTY( meta = (BindWidget) )
		TWeakObjectPtr<UScrollBox> C_SB_OtherProduct;
	UPROPERTY( meta = (BindWidget) )
		UScaleBox* C_ScaleBox_ImgBoots;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Boots;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Logo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_ProductName;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Brand;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Studs;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Upper;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Silo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Ground;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Fit;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_BallOfFoot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_HeightOfFoot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Length;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Weight;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Price;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_ReleaseDate;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_ProductID;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_BookMark;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_BookMark;


	UWidgetAnimation* _Ani_ProductOpenByShop;
	FName _Ani_ProductOpen_ByShop_Name = "Ani_Detail_Open_By_Shop";
	UWidgetAnimation* _Ani_ProductOpenByReview;
	FName _Ani_ProductOpen_ByReview_Name = "Ani_Detail_Open_By_Review";

	UWidgetAnimation* _Ani_ShopOpenByDetail;
	FName _Ani_ShopOpen_ByDetail_Name = "Ani_Shop_Open_By_Detail";
	UWidgetAnimation* _Ani_ShopOpenByReview;
	FName _Ani_ShopOpen_ByReview_Name = "Ani_Shop_Open_By_Review";

	UWidgetAnimation* _Ani_ReviewOpenByDetail;
	FName _Ani_ReviewOpen_ByDetail_Name = "Ani_Review_Open_By_Detail";
	UWidgetAnimation* _Ani_ReviewOpenByShop;
	FName _Ani_ReviewOpen_ByShop_Name = "Ani_Review_Open_By_Shop";

	UWidgetAnimation* _Ani_DetailOpen;
	FName _Ani_DetailOpenName = "Ani_Detail_Open";
	UWidgetAnimation* _Ani_DetailClose;
	FName _Ani_DetailCloseName = "Ani_Detail_Close";

	int32 _BootsDetailIndex;
	FString _BootsProductID;
	E_FILTER_ITEM_TYPE _InfoFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;

	TArray<UBWidget_CommonItemSlot2*> _SubOtherProduct;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitBootsDetail();
	void InitBootsReview();
	void SetBootsDetailData( const int32 bootsIndex );
	void SetBootsDetailData_DB( const int32 bootsIndex );

	void PlayProductOpenAni( const E_FILTER_ITEM_TYPE prevFilterType );
	void PlayShopOpenAni( const E_FILTER_ITEM_TYPE prevFilterType );
	void PlayReviewOpenAni( const E_FILTER_ITEM_TYPE prevFilterType );
	void PlayDetailOpenAni( const bool isDetailOpen );

	UFUNCTION()
		void OnClickInfoFilter( const E_FILTER_ITEM_TYPE infoFilterType, bool isForce = true );
	UFUNCTION()
		void OnClickOtherItem( const int32 bootsIndex, const int32 bootsIDIndex );
	UFUNCTION()
		void OnClickOtherItem_DB( const int32 bootsIndex, const int32 bootsIDIndex );

protected:
	virtual bool _OnBackInput() override;

	UFUNCTION()
		void _OnClick_BookMark();
	UFUNCTION()
		void _RefreshBookMark();

private:
	void _SetShopInfo();
	void _TestShopInfo();

	UFUNCTION()
		void _OnSuccessDownLoadDetailImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadDetailImage( UTexture2DDynamic* texturl );
};
