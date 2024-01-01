// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_ReviewSlot.h"
#include "Bigtamin.h"

void UBWidget_ReviewSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_ReviewSlot, &UBWidget_ReviewSlot::_OnClick_ReviewSlot );

	OnSuccessDownLoadReviewImage.BindUFunction( this, "_OnSuccessDownLoadReviewImage" );
	OnFailDownLoadReviewImage.BindUFunction( this, "_OnFailDownLoadReviewImage" );
}

void UBWidget_ReviewSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_ReviewSlot::SetReviewSlotData( FST_REVIEW_DATA slotData )
{
	_ReviewData = slotData;

	DownLoadTexture_URL( _ReviewData.ImgURL, OnSuccessDownLoadReviewImage, OnFailDownLoadReviewImage );

	C_Txt_Title->SetText( FText::FromString( _ReviewData.Title ) );
	C_Txt_Source->SetText( FText::FromString( _ReviewData.Source ) );
}

void UBWidget_ReviewSlot::SetNotInfo( bool isNotInfo )
{
	C_OL_NotInfo->SetVisibility( isNotInfo ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed );
}

void UBWidget_ReviewSlot::_OnClick_ReviewSlot()
{
	if( _ReviewData.ReviewURL.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( _ReviewData.ReviewURL );
	}
}

void UBWidget_ReviewSlot::_OnSuccessDownLoadReviewImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		if( C_Img_Review != nullptr )
		{
			C_Img_Review->SetBrushFromTextureDynamic( texturl, true );
		}
	}
}

void UBWidget_ReviewSlot::_OnFailDownLoadReviewImage( UTexture2DDynamic* texturl )
{

}
