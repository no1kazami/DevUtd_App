// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_UpcomingSlot.h"
#include "Bigtamin.h"

void UBWidget_UpcomingSlot::Init()
{
	Super::Init();

	OnSuccessDownLoadUpcomingImage.BindUFunction( this, "_OnSuccessDownLoadUpcomingImage" );
	OnFailDownLoadUpcomingImage.BindUFunction( this, "_OnFailDownLoadUpcomingImage" );
}

void UBWidget_UpcomingSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_UpcomingSlot::SetUpcomingSlotData( FST_UPCOMING_DATA slotData, bool isHidden )
{
	_UpcomingData = slotData;

	// 상세 이미지 셋팅
	DownLoadTexture_URL( _UpcomingData.UpcomingURL, OnSuccessDownLoadUpcomingImage, OnFailDownLoadUpcomingImage );

	// 브랜드 이미지 셋팅
	UTexture2D* textureLogo = GetTexture( UFBMUtil::BrandLogoPath( _UpcomingData.UpcomingBrandType ) );
	if( textureLogo != nullptr )
	{
		C_Img_Logo->SetBrushFromTexture( textureLogo, true );
	}

	// 텍스트 설정
	FString strUpcomingDate = _UpcomingData.UpcomingDate;
	FString strYear = strUpcomingDate.Left( 4 );
	FString strMonth = strUpcomingDate.Right( 2 );
	C_Txt_Year->SetText( FText::Format( GET_BTEXT( 81 ), FText::FromString( strYear ) ) );
	C_Txt_Month->SetText( FText::FromString( strMonth ) );
	C_Txt_Contents->SetText( FText::FromString( _UpcomingData.UpcomingBootsName ) );

	C_VB_Date->SetVisibility( isHidden ? ESlateVisibility::Hidden : ESlateVisibility::Visible );
}

void UBWidget_UpcomingSlot::_OnSuccessDownLoadUpcomingImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		if( C_Img_Product != nullptr )
		{
			C_Img_Product->SetBrushFromTextureDynamic( texturl, true );
		}
	}
}

void UBWidget_UpcomingSlot::_OnFailDownLoadUpcomingImage( UTexture2DDynamic* texturl )
{

}
