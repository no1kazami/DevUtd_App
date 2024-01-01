// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_CommonItemSlot.h"
#include "Bigtamin.h"


void UBWidget_CommonItemSlot::Init()
{
	Super::Init();

	_ProductID.Empty();

	OnSuccessDownLoadCommonImage.BindUFunction( this, "_OnSuccessDownLoadCommonImage" );
	OnFailDownLoadCommonImage.BindUFunction( this, "_OnFailDownLoadCommonImage" );

	ButtonDelegate_Clicked( this, C_Btn_CommonItem, &UBWidget_CommonItemSlot::_OnClick_CommonItem );
}

void UBWidget_CommonItemSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_CommonItemSlot::SetCommonItemSlotData( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex )
{
	_SlotType = slotType;
	_ContentIndex = itemIndex;

	if (_SlotType == E_COMMON_ITEM_SLOT_TYPE::BOOTS)
	{
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo(itemIndex, isSuccess);
		if (isSuccess)
		{
			// 슬롯 이미지 셋팅
			FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
			UTexture2D* textureBoots = GetTexture( iconPath.ToString());
			if( textureBoots == nullptr )
			{
				textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
			}
			if (textureBoots != nullptr)
			{
				C_Img_CommonItem->SetBrushFromTexture(textureBoots, false);
			}

			// 슬롯 이름 셋팅
			C_Txt_CommonItem->SetText( UFBMUtil::ProductNameText( itemIndex, true ) );
		}
	}
}

void UBWidget_CommonItemSlot::SetCommonItemSlotData_DB( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex )
{
	_ProductID.Empty();

	_SlotType = slotType;
	_ContentIndex = itemIndex;

	if( _SlotType == E_COMMON_ITEM_SLOT_TYPE::BOOTS )
	{
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( itemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			// 제일 최신 축구화 data 찾기
			FString newProductID;
			bool isOtherProductNew = bootsSlotInfo_DB->GetNewReleaseDateProductID( newProductID );

			// 슬롯 이미지 셋팅
			_ProductID = newProductID;
			UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( newProductID );
			if( downLoadImg != nullptr )
			{
				if( C_Img_CommonItem != nullptr )
				{
					C_Img_CommonItem->SetBrushFromTextureDynamic( downLoadImg, false );
				}
			}
			else
			{
				if( isOtherProductNew )
				{
					// 슬롯 이미지 셋팅
					if( bootsSlotInfo_DB->Other_ProductURL.Contains( newProductID ) )
					{
						DownLoadTexture_URL( bootsSlotInfo_DB->Other_ProductURL[newProductID], OnSuccessDownLoadCommonImage, OnFailDownLoadCommonImage );
					}
				}
				else
				{
					// 슬롯 이미지 셋팅
					DownLoadTexture_URL( bootsSlotInfo_DB->IconURL, OnSuccessDownLoadCommonImage, OnFailDownLoadCommonImage );
				}
			}

			// 슬롯 이름 셋팅
			C_Txt_CommonItem->SetText( UFBMUtil::ProductNameText_DB( itemIndex, true ) );
		}
	}
}

void UBWidget_CommonItemSlot::_OnClick_CommonItem()
{
	OnClickCommonItemSlot.Broadcast( _ContentIndex );
}

void UBWidget_CommonItemSlot::_OnSuccessDownLoadCommonImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID, texturl );

		if( C_Img_CommonItem != nullptr )
		{
			C_Img_CommonItem->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_CommonItemSlot::_OnFailDownLoadCommonImage( UTexture2DDynamic* texturl )
{

}
