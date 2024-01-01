// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_CommonItemSlot2.h"

void UBWidget_CommonItemSlot2::Init()
{
	Super::Init();

	_ProductID.Empty();

	OnSuccessDownLoadCommonImage2.BindUFunction( this, "_OnSuccessDownLoadCommonImage2" );
	OnFailDownLoadCommonImage2.BindUFunction( this, "_OnFailDownLoadCommonImage2" );

	ButtonDelegate_Clicked( this, C_Btn_CommonItem, &UBWidget_CommonItemSlot2::_OnClick_CommonItem );

	SetSelectLine( false );
}

void UBWidget_CommonItemSlot2::OnClose()
{
	Super::OnClose();
}

void UBWidget_CommonItemSlot2::SetCommonItemSlotData( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex, const int32 productIDIndex, const bool isSelect /*= false */ )
{
	_SlotType = slotType;
	_ContentIndex = itemIndex;
	_ProductIDIndex = productIDIndex;

	if( _SlotType == E_COMMON_ITEM_SLOT_TYPE::BOOTS )
	{
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( itemIndex, isSuccess );
		if( isSuccess )
		{
			FText iconPath;
			if( _ProductIDIndex == MAIN_BOOTS_COLOR_SLOT )
			{
				iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
			}
			else if( bootsSlotInfo.Other_ProductID.Num() > _ProductIDIndex )
			{
				iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.Other_ProductID[_ProductIDIndex] );
			}

			UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
			if( textureBoots == nullptr )
			{
				textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
			}
			if( textureBoots != nullptr )
			{
				C_Img_CommonItem->SetBrushFromTexture( textureBoots, false );
			}

			SetSelectLine( isSelect );
		}
	}
}

void UBWidget_CommonItemSlot2::SetCommonItemSlotData_DB( const E_COMMON_ITEM_SLOT_TYPE slotType, const int32 itemIndex, const int32 productIDIndex, const bool isSelect/* = false */ )
{
	_ProductID.Empty();

	_SlotType = slotType;
	_ContentIndex = itemIndex;
	_ProductIDIndex = productIDIndex;

	if( _SlotType == E_COMMON_ITEM_SLOT_TYPE::BOOTS )
	{
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( itemIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			FString iconURL;
			if( _ProductIDIndex == MAIN_BOOTS_COLOR_SLOT )
			{
				_ProductID = bootsSlotInfo_DB->ProductID;
				iconURL = bootsSlotInfo_DB->IconURL;
			}
			else if( bootsSlotInfo_DB->Other_ProductID.Num() > _ProductIDIndex )
			{
				_ProductID = bootsSlotInfo_DB->Other_ProductID[_ProductIDIndex];

				if( bootsSlotInfo_DB->Other_ProductURL.Contains( _ProductID ) )
				{
					iconURL = bootsSlotInfo_DB->Other_ProductURL[_ProductID];
				}
			}

			// 축구화 이미지 셋팅
			UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( _ProductID );
			if( downLoadImg != nullptr )
			{
				if( C_Img_CommonItem != nullptr )
				{
					C_Img_CommonItem->SetBrushFromTextureDynamic( downLoadImg, false );
				}
			}
			else
			{
				if( iconURL.IsEmpty() == false )
				{
					DownLoadTexture_URL( iconURL, OnSuccessDownLoadCommonImage2, OnFailDownLoadCommonImage2 );
				}
			}

			SetSelectLine( isSelect );
		}
	}
}

void UBWidget_CommonItemSlot2::SetSelectLine( bool isSelect )
{
	C_Img_SelectLine->SetVisibility( isSelect ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
}

void UBWidget_CommonItemSlot2::_OnClick_CommonItem()
{
	if( _SlotType == E_COMMON_ITEM_SLOT_TYPE::BOOTS && _ProductIDIndex != -1 )
	{
		OnClickItemColorSlot.Broadcast( _ContentIndex, _ProductIDIndex );
		SetSelectLine( true );
	}
}

void UBWidget_CommonItemSlot2::_OnSuccessDownLoadCommonImage2( UTexture2DDynamic* texturl )
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

void UBWidget_CommonItemSlot2::_OnFailDownLoadCommonImage2( UTexture2DDynamic* texturl )
{

}
