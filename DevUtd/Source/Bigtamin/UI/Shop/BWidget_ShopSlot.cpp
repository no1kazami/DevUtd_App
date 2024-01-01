// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_ShopSlot.h"
#include "Bigtamin.h"
#include "Kismet/KismetStringLibrary.h"
#include "GenericPlatform/GenericPlatformHttp.h"

void UBWidget_ShopSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_ShopSlot, &UBWidget_ShopSlot::_OnClick_ShopSlot );

	SetTopNotInfo(false);
}

void UBWidget_ShopSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_ShopSlot::SetShopSlotData( const E_CRAWLING_WEBPAGE shopInfo, FString urlData, int32 priceData )
{
	_CrawlingShop = shopInfo;

	// Url º¬∆√
	_SetShopURL( urlData );

	// ∞°∞Ω º¬∆√
	_SetShopPrice( priceData );

	// Shop ¿ÃπÃ¡ˆ º¬∆√
	UTexture2D* textureLogo = GetTexture( UFBMUtil::ShopLogoPath( shopInfo ) );
	if( textureLogo != nullptr )
	{
		C_Img_ShopLogo->SetBrushFromTexture( textureLogo, true );
	}

	// Shop ¿Ã∏ß
	C_Txt_ShopName->SetText( UFBMUtil::ShopNameText( shopInfo ) );

	SetNotInfo( false );
}

void UBWidget_ShopSlot::SetNotInfo( bool isNotInfo )
{
	C_OL_NotInfo->SetVisibility( isNotInfo ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed );
}

void UBWidget_ShopSlot::SetTopNotInfo( bool isShow, bool isDomestic /*= true */ )
{
	if ( isShow )
	{
		C_Txt_TopInfo->SetVisibility(ESlateVisibility::Visible);
		C_Txt_TopInfo->SetText( GET_BTEXT( isDomestic ? 75 : 76 ) );
	}
	else
	{
		C_Txt_TopInfo->SetVisibility( ESlateVisibility::Collapsed );
	}
}

void UBWidget_ShopSlot::_OnClick_ShopSlot()
{
	UKismetSystemLibrary::LaunchURL( _ShopUrl );
}

void UBWidget_ShopSlot::_SetShopURL( FString urlData )
{
	// ±π≥ª ºÓ«Œ∏Ù
	if ( _CrawlingShop < E_CRAWLING_WEBPAGE::PDS)
	{
		_ShopUrl = urlData;
	}
	// «ÿø‹ ºÓ«Œ∏Ù
	else
	{
		_ShopUrl = urlData;
		/*
		FString vigLinkKey = "da001c42c1c02b7644e742d30c0fbd9e";
		FString encodeURL = FGenericPlatformHttp::UrlEncode(urlData);
		//_ShopUrl = "http://redirect.viglink.com?u=" + encodeURL + "&key=" + vigLinkKey + "&opt=true";
		_ShopUrl = "https://viglink.io/uri/anywhere/generate?u=" + encodeURL + "&key=" + vigLinkKey + "&opt=true";
		*/
	}
}

void UBWidget_ShopSlot::_SetShopPrice( const int32 priceData )
{
	// ±π≥ª ºÓ«Œ∏Ù
	if( _CrawlingShop < E_CRAWLING_WEBPAGE::PDS )
	{
		C_Txt_Price->SetText( FText::Format( GET_BTEXT( 21 ), FText::AsNumber( priceData ) ) );
	}
	// «ÿø‹ ºÓ«Œ∏Ù
	else
	{
		// 77:∆ƒøÓµÂ, 78:¿Ø∑Œ, 79:¥ﬁ∑Ø
		int32 priceStringIndex = 79;
		switch(_CrawlingShop)
		{
		case E_CRAWLING_WEBPAGE::PDS:
			priceStringIndex = 77; // ∆ƒøÓµÂ
			break;
		case E_CRAWLING_WEBPAGE::UNI:
			priceStringIndex = 78; // ¿Ø∑Œ
			break;
		default:
			priceStringIndex = 79; // ¥ﬁ∑Ø
			break;
		}

		FString strPrice = FString::FromInt( priceData );
		FString firstPrice = strPrice.LeftChop( 2 );
		FString secondPrice = strPrice.Right( 2 );
		FString finalPrice = firstPrice + "." + secondPrice;

		C_Txt_Price->SetText( FText::Format( GET_BTEXT( priceStringIndex ), FText::FromString( finalPrice ) ) );
	}
}
