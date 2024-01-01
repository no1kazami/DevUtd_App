// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ShopSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_ShopSlot : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_ShopSlot;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_ShopLogo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_ShopName;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Price;
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_OL_NotInfo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_TopInfo;

	FString _ShopUrl;
	E_CRAWLING_WEBPAGE _CrawlingShop = E_CRAWLING_WEBPAGE::NONE;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetShopSlotData( const E_CRAWLING_WEBPAGE shopInfo, FString urlData, int32 priceData );
	void SetNotInfo( bool isNotInfo );
	void SetTopNotInfo( bool isShow, bool isDomestic = true );

private:
	UFUNCTION()
		void _OnClick_ShopSlot();
	UFUNCTION()
		void _SetShopURL( FString urlData );
	UFUNCTION()
		void _SetShopPrice( const int32 priceData );
	
};
