// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_BootsSlot.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"

void UBWidget_BootsSlot::Init()
{
	Super::Init();

	OnSuccessDownLoadBootsSlotImage.BindUFunction( this, "_OnSuccessDownLoadBootsSlotImage" );
	OnFailDownLoadBootsSlotImage.BindUFunction( this, "_OnFailDownLoadBootsSlotImage" );

	ButtonDelegate_Clicked( this, C_Btn_BootsSlot, &UBWidget_BootsSlot::_OnClick_BootsSlot );

	_SlotIndex = 0;
	_BootsIndex = 0;
	_BootsProductID.Empty();
}

void UBWidget_BootsSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_BootsSlot::SetBootSlotData( const int32 slotIndex, const int32 bootsIndex )
{
	if( bootsIndex <= 0 )
		return;

	_SlotIndex = slotIndex;
	_BootsIndex = bootsIndex;

	bool isSuccess = false;
	FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
	if( isSuccess )
	{
		// 배경색 셋팅
		//C_Img_BG->SetColorAndOpacity( (slotIndex % 2 == 0) ? Color_BootsSlot_Gray : Color_BootsSlot_White );
		//C_Img_BgBoots->SetColorAndOpacity( (slotIndex % 2 == 0) ? Color_BootsSlot_Gray : Color_BootsSlot_White );

		// 축구화 이미지 셋팅
		FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
		UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
		if( textureBoots == nullptr )
		{
			textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
		}
		if( textureBoots != nullptr )
		{
			C_Img_Boots->SetBrushFromTexture( textureBoots, true );
		}

		// 브랜드 이미지 셋팅
		UTexture2D* textureLogo = GetTexture( UFBMUtil::BrandLogoPath( bootsSlotInfo.eBrandType ) );
		if( textureLogo != nullptr )
		{
			C_Img_Logo->SetBrushFromTexture( textureLogo, true );
		}

		// 제품명
		C_Txt_ProductName->SetText( UFBMUtil::ProductNameText( bootsIndex, false ) );

		// 브랜드명
		C_Txt_Brand->SetText( UFBMUtil::BrandNameText( bootsSlotInfo.eBrandType ) );

		// 스터드 타입
		C_Txt_Studs->SetText( UFBMUtil::StudsNameText( bootsSlotInfo.eStudsType ) );

		// 어퍼(외피) 타입
		C_Txt_Upper->SetText( UFBMUtil::UpperNameText( bootsSlotInfo.eUpperType ) );

		// 가격
		C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo.nPrice ) ) );
		//C_Txt_Price->SetText( FText::Format( "{0}원", FText::AsNumber( bootsSlotInfo.nPrice ) ) );
	}
}

void UBWidget_BootsSlot::SetBootSlotData_DB( const int32 slotIndex, const int32 bootsIndex )
{
	if( bootsIndex <= 0 )
		return;

	_SlotIndex = slotIndex;
	_BootsIndex = bootsIndex;
	_BootsProductID.Empty();

	const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
	if( bootsSlotInfo_DB != nullptr )
	{
		FString iconURL;

		// 제일 최신 축구화 data 찾기
		FString newProductID;
		bool isOtherProductNew = bootsSlotInfo_DB->GetNewReleaseDateProductID( newProductID );
		_BootsProductID = newProductID;
		if( isOtherProductNew )
		{
			// 축구화 이미지 셋팅
			if( bootsSlotInfo_DB->Other_ProductURL.Contains( newProductID ) )
			{
				iconURL = bootsSlotInfo_DB->Other_ProductURL[newProductID];
			}

			// 가격
			if( bootsSlotInfo_DB->Other_Price.Contains( newProductID ) )
			{
				C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo_DB->Other_Price[newProductID] ) ) );
			}
		}
		else
		{
			iconURL = bootsSlotInfo_DB->IconURL;

			// 가격
			C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo_DB->Price ) ) );
		}

		// 축구화 이미지 셋팅
		UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( newProductID );
		if( downLoadImg != nullptr )
		{
			if( C_Img_Boots != nullptr )
			{
				C_Img_Boots->SetBrushFromTextureDynamic( downLoadImg, true );
			}
		}
		else
		{
			if( iconURL.IsEmpty() == false )
			{
				DownLoadTexture_URL( iconURL, OnSuccessDownLoadBootsSlotImage, OnFailDownLoadBootsSlotImage );
			}
		}

		// 브랜드 이미지 셋팅
		UTexture2D* textureLogo = GetTexture( UFBMUtil::BrandLogoPath( bootsSlotInfo_DB->BrandType ) );
		if( textureLogo != nullptr )
		{
			C_Img_Logo->SetBrushFromTexture( textureLogo, true );
		}

		// 제품명
		C_Txt_ProductName->SetText( UFBMUtil::ProductNameText_DB( bootsIndex, false ) );

		// 브랜드명
		C_Txt_Brand->SetText( UFBMUtil::BrandNameText( bootsSlotInfo_DB->BrandType ) );

		// 스터드 타입
		C_Txt_Studs->SetText( UFBMUtil::StudsNameText( bootsSlotInfo_DB->StudsType ) );

		// 어퍼(외피) 타입
		C_Txt_Upper->SetText( UFBMUtil::UpperNameText( bootsSlotInfo_DB->UpperType ) );
	}
}

void UBWidget_BootsSlot::_OnClick_BootsSlot()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		GInst->SetCurSelectBootsIndex( _BootsIndex );
		gameMode->ChangeMode( E_MODE::E_MODE_BOOTS_DETAIL );
	}
}

void UBWidget_BootsSlot::_OnSuccessDownLoadBootsSlotImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _BootsProductID, texturl );

		if( C_Img_Boots != nullptr )
		{
			C_Img_Boots->SetBrushFromTextureDynamic( texturl, true );
		}
	}
}

void UBWidget_BootsSlot::_OnFailDownLoadBootsSlotImage( UTexture2DDynamic* texturl )
{

}
