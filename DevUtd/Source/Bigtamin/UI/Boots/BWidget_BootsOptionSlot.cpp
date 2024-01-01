// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_BootsOptionSlot.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"


void UBWidget_BootsOptionSlot::Init()
{
	Super::Init();

	OnSuccessDownLoadOptionImage.BindUFunction( this, "_OnSuccessDownLoadOptionImage" );
	OnFailDownLoadOptionImage.BindUFunction( this, "_OnFailDownLoadOptionImage" );
	OnSuccessDownLoadOptionImage2.BindUFunction( this, "_OnSuccessDownLoadOptionImage2" );
	OnFailDownLoadOptionImage2.BindUFunction( this, "_OnFailDownLoadOptionImage2" );
	OnSuccessDownLoadOptionImage3.BindUFunction( this, "_OnSuccessDownLoadOptionImage3" );
	OnFailDownLoadOptionImage3.BindUFunction( this, "_OnFailDownLoadOptionImage3" );


	ButtonDelegate_Clicked( this, C_Btn_CompareAdd, &UBWidget_BootsOptionSlot::_OnClick_CompareAdd );
	ButtonDelegate_Clicked( this, C_Btn_UpDown, &UBWidget_BootsOptionSlot::_OnClick_UpDown );
	ButtonDelegate_Clicked( this, C_Btn_Cancel1, &UBWidget_BootsOptionSlot::_OnClick_Cancel1 );
	ButtonDelegate_Clicked( this, C_Btn_Cancel2, &UBWidget_BootsOptionSlot::_OnClick_Cancel2 );
	ButtonDelegate_Clicked( this, C_Btn_Cancel3, &UBWidget_BootsOptionSlot::_OnClick_Cancel3 );
	ButtonDelegate_Clicked( this, C_Btn_SelectCompare, &UBWidget_BootsOptionSlot::_OnClick_SelectCompare );

	_ProductID1.Empty();
	_ProductID2.Empty();
	_ProductID3.Empty();

	_Init_OverlaySelect();

#if DB_BOOTS_DATA
	_ResetCompareSlot_DB();
#else
	_ResetCompareSlot();
#endif
}

void UBWidget_BootsOptionSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_BootsOptionSlot::_Init_OverlaySelect()
{
	C_Overlay_Select->SetVisibility( ESlateVisibility::Collapsed );
	UTexture2D* textureDown = GetTexture( TEXT( "Icon/Down" ) );
	if( textureDown != nullptr )
	{
		C_Img_UpDown->SetBrushFromTexture( textureDown, false );
	}

	UTexture2D* textureBG = GetTexture( TEXT( "Icon/CompareAddRect1" ) );
	if( textureBG != nullptr )
	{
		C_Img_BG->SetBrushFromTexture( textureBG, true );
	}
}

void UBWidget_BootsOptionSlot::_OnClick_CompareAdd()
{
	bool isAdd = GInst->AddComparePlayerName( GInst->GetCurSelectPlayerName() );
	if( C_Overlay_Select->IsVisible() == false && isAdd )
	{
		C_Overlay_Select->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		UTexture2D* textureUp = GetTexture( TEXT( "Icon/Up" ) );
		if( textureUp != nullptr )
		{
			C_Img_UpDown->SetBrushFromTexture( textureUp, false );
		}

		UTexture2D* textureBG = GetTexture( TEXT( "Icon/CompareAddRect2" ) );
		if( textureBG != nullptr )
		{
			C_Img_BG->SetBrushFromTexture( textureBG, true );
		}
	}

	if( isAdd )
	{
	#if DB_BOOTS_DATA
		_ResetCompareSlot_DB();
	#else
		_ResetCompareSlot();
	#endif

		GInst->PlayWarningUI( 45 );
	}
	else
	{
		if (GInst->IsAlReadyAddPlayerNameSlot( GInst->GetCurSelectPlayerName() ))
		{
			GInst->PlayWarningUI( 46 );
		}
		else
		{
			GInst->PlayWarningUI( 48 );
		}
	}
}

void UBWidget_BootsOptionSlot::_OnClick_UpDown()
{
	if (C_Overlay_Select->IsVisible())
	{
		C_Overlay_Select->SetVisibility( ESlateVisibility::Collapsed );

		UTexture2D* textureDown = GetTexture( TEXT( "Icon/Down" ) );
		if( textureDown != nullptr )
		{
			C_Img_UpDown->SetBrushFromTexture( textureDown, false );
		}

		UTexture2D* textureBG = GetTexture( TEXT( "Icon/CompareAddRect1" ) );
		if( textureBG != nullptr )
		{
			C_Img_BG->SetBrushFromTexture( textureBG, true );
		}
	}
	else
	{
		C_Overlay_Select->SetVisibility( ESlateVisibility::SelfHitTestInvisible );

		UTexture2D* textureUp = GetTexture( TEXT( "Icon/Up" ) );
		if( textureUp != nullptr )
		{
			C_Img_UpDown->SetBrushFromTexture( textureUp, false );
		}

		UTexture2D* textureBG = GetTexture( TEXT( "Icon/CompareAddRect2" ) );
		if( textureBG != nullptr )
		{
			C_Img_BG->SetBrushFromTexture( textureBG, true );
		}
	}
}

void UBWidget_BootsOptionSlot::_OnClick_Cancel1()
{
	GInst->RemoveComparePlayerNameSlot( 1 );

#if DB_BOOTS_DATA
	_ResetCompareSlot_DB();
#else
	_ResetCompareSlot();
#endif

	FString playerName1 = GInst->GetComparePlayerName( 1 );
	if ( playerName1.IsEmpty() )
	{
		_Init_OverlaySelect();
	}
}

void UBWidget_BootsOptionSlot::_OnClick_Cancel2()
{
	GInst->RemoveComparePlayerNameSlot( 2 );
	
#if DB_BOOTS_DATA
	_ResetCompareSlot_DB();
#else
	_ResetCompareSlot();
#endif
}

void UBWidget_BootsOptionSlot::_OnClick_Cancel3()
{
	GInst->RemoveComparePlayerNameSlot( 3 );
	
#if DB_BOOTS_DATA
	_ResetCompareSlot_DB();
#else
	_ResetCompareSlot();
#endif
}

void UBWidget_BootsOptionSlot::_OnClick_SelectCompare()
{
	FString playerName2 = GInst->GetComparePlayerName( 2 );
	if( !playerName2.IsEmpty() )
	{
		ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
		if( gameMode != nullptr )
		{
			gameMode->ChangeMode( E_MODE::E_MODE_PLAYER_COMPARE);
		}
	}
	else
	{
		GInst->PlayWarningUI( 47 );
	}
}

void UBWidget_BootsOptionSlot::_ResetCompareSlot()
{
	auto funcCompareSlotSet = [this]( int32 slotIndex )
	{
		int32 bootsIndex = GInst->GetCompareBootsIndex( slotIndex );
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
		if( isSuccess )
		{
			// 축구화 이미지 셋팅
			FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
			UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
			if( textureBoots == nullptr )
			{
				textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
			}
			if( textureBoots != nullptr )
			{
				if ( slotIndex == 1)
				{
					C_Img_Compare1->SetBrushFromTexture( textureBoots, false );
					C_Btn_Cancel1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
				}
				else if( slotIndex == 2 )
				{
					C_Img_Compare2->SetBrushFromTexture( textureBoots, false );
					C_Btn_Cancel2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
				}
				else if( slotIndex == 3 )
				{
					C_Img_Compare3->SetBrushFromTexture( textureBoots, false );
					C_Btn_Cancel3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
				}
			}
		}
	};

	C_Img_Compare1->SetBrushFromTexture( nullptr, false );
	C_Img_Compare2->SetBrushFromTexture( nullptr, false );
	C_Img_Compare3->SetBrushFromTexture( nullptr, false );
	C_Btn_Cancel1->SetVisibility( ESlateVisibility::Hidden );
	C_Btn_Cancel2->SetVisibility( ESlateVisibility::Hidden );
	C_Btn_Cancel3->SetVisibility( ESlateVisibility::Hidden );

	funcCompareSlotSet( 1 );
	funcCompareSlotSet( 2 );
	funcCompareSlotSet( 3 );
}

void UBWidget_BootsOptionSlot::_ResetCompareSlot_DB()
{
	auto funcCompareSlotSet = [this]( int32 slotIndex )
	{
		FString playerName = GInst->GetComparePlayerName( slotIndex );
		const FST_PLAYER_DATA* playerData = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( playerName );
		if( playerData )
		{
			// 선수 이미지 셋팅
			FString iconURL = playerData->PictureURL;
			UTexture2DDynamic* downLoadImg = GInst->GetDownLoadPlayerImage( playerName );
			if( downLoadImg != nullptr )
			{
				switch( slotIndex )
				{
				case 1:
					_ProductID1 = playerName;
					if( C_Img_Compare1 != nullptr )
					{
						C_Img_Compare1->SetBrushFromTextureDynamic( downLoadImg, false );
						C_Btn_Cancel1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
					}
					break;
				case 2:
					_ProductID2 = playerName;
					if( C_Img_Compare2 != nullptr )
					{
						C_Img_Compare2->SetBrushFromTextureDynamic( downLoadImg, false );
						C_Btn_Cancel2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
					}
					break;
				case 3:
					_ProductID3 = playerName;
					if( C_Img_Compare3 != nullptr )
					{
						C_Img_Compare3->SetBrushFromTextureDynamic( downLoadImg, false );
						C_Btn_Cancel3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
					}
					break;
				default:
					break;
				}
			}
			else
			{
				if( iconURL.IsEmpty() || iconURL == TEXT( "nan" ) )
				{
					UTexture2D* texturePlayer = GetTexture( TEXT( "Etc/DefaultPerson_256" ) );
					if( texturePlayer != nullptr )
					{
						switch( slotIndex )
						{
						case 1:
							C_Img_Compare1->SetBrushFromTexture( texturePlayer, false );
							C_Btn_Cancel1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
							break;
						case 2:
							C_Img_Compare2->SetBrushFromTexture( texturePlayer, false );
							C_Btn_Cancel2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
							break;
						case 3:
							C_Img_Compare3->SetBrushFromTexture( texturePlayer, false );
							C_Btn_Cancel3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
							break;
						default:
							break;
						}
					}
				}
				else
				{				
					switch( slotIndex )
					{
					case 1:
						_ProductID1 = playerName;
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadOptionImage, OnFailDownLoadOptionImage );
						break;
					case 2:
						_ProductID2 = playerName;
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadOptionImage2, OnFailDownLoadOptionImage2 );
						break;
					case 3:
						_ProductID3 = playerName;
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadOptionImage3, OnFailDownLoadOptionImage3 );
						break;
					default:
						break;
					}
				}				
			}
		}
	};

	_ProductID1.Empty();
	_ProductID2.Empty();
	_ProductID3.Empty();

	C_Img_Compare1->SetBrushFromTexture( nullptr, false );
	C_Img_Compare2->SetBrushFromTexture( nullptr, false );
	C_Img_Compare3->SetBrushFromTexture( nullptr, false );
	C_Btn_Cancel1->SetVisibility( ESlateVisibility::Hidden );
	C_Btn_Cancel2->SetVisibility( ESlateVisibility::Hidden );
	C_Btn_Cancel3->SetVisibility( ESlateVisibility::Hidden );

	funcCompareSlotSet( 1 );
	funcCompareSlotSet( 2 );
	funcCompareSlotSet( 3 );
}

void UBWidget_BootsOptionSlot::_OnSuccessDownLoadOptionImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID1, texturl );

		if( C_Img_Compare1 != nullptr )
		{
			C_Img_Compare1->SetBrushFromTextureDynamic( texturl, false );
			C_Btn_Cancel1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		}
	}
}

void UBWidget_BootsOptionSlot::_OnFailDownLoadOptionImage( UTexture2DDynamic* texturl )
{

}

void UBWidget_BootsOptionSlot::_OnSuccessDownLoadOptionImage2( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID2, texturl );

		if( C_Img_Compare2 != nullptr )
		{
			C_Img_Compare2->SetBrushFromTextureDynamic( texturl, false );
			C_Btn_Cancel2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		}
	}
}

void UBWidget_BootsOptionSlot::_OnFailDownLoadOptionImage2( UTexture2DDynamic* texturl )
{

}

void UBWidget_BootsOptionSlot::_OnSuccessDownLoadOptionImage3( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID3, texturl );

		if( C_Img_Compare3 != nullptr )
		{
			C_Img_Compare3->SetBrushFromTextureDynamic( texturl, false );
			C_Btn_Cancel3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		}
	}
}

void UBWidget_BootsOptionSlot::_OnFailDownLoadOptionImage3( UTexture2DDynamic* texturl )
{

}
