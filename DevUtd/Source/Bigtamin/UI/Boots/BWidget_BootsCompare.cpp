// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_BootsCompare.h"
#include "Bigtamin.h"
#include "UI/BWidget_Top.h"

void UBWidget_BootsCompare::Init()
{
	Super::Init();

	BP_Top_BootsCompare_UMG->Init();
	BP_Top_BootsCompare_UMG->ChangeTopMode( E_MODE::E_MODE_BOOTS_COMPARE );

	_Ani_CompareOpen = GetWidgetAnimation( _Ani_CompareOpenName );
	_Ani_CompareClose = GetWidgetAnimation( _Ani_CompareCloseName );

	GInst->AddBackInput( this );

	OnSuccessDownLoadCompareImage.BindUFunction( this, "_OnSuccessDownLoadCompareImage" );
	OnFailDownLoadCompareImage.BindUFunction( this, "_OnFailDownLoadCompareImage" );
	OnSuccessDownLoadCompareImage2.BindUFunction( this, "_OnSuccessDownLoadCompareImage2" );
	OnFailDownLoadCompareImage2.BindUFunction( this, "_OnFailDownLoadCompareImage2" );
	OnSuccessDownLoadCompareImage3.BindUFunction( this, "_OnSuccessDownLoadCompareImage3" );
	OnFailDownLoadCompareImage3.BindUFunction( this, "_OnFailDownLoadCompareImage3" );

	_InitBootsCompare();

	PlayCompareOpenAni( true );
}

void UBWidget_BootsCompare::OnClose()
{
	Super::OnClose();
}

void UBWidget_BootsCompare::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_CompareCloseName )
		{
			CloseUI();
		}
	}
}

void UBWidget_BootsCompare::PlayCompareOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_CompareOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_CompareOpen ) )
			{
				StopAnimation( _Ani_CompareOpen );
			}

			PlayAnimation( _Ani_CompareOpen );
		}
	}
	else
	{
		if( _Ani_CompareClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_CompareClose ) )
			{
				StopAnimation( _Ani_CompareClose );
			}

			PlayAnimation( _Ani_CompareClose );
		}
	}
}

bool UBWidget_BootsCompare::_OnBackInput()
{
	Super::_OnBackInput();
	
	PlayCompareOpenAni( false );

	return true;
}

void UBWidget_BootsCompare::_InitBootsCompare()
{
	_ClearBootsCompareUI();

#if DB_BOOTS_DATA
	_SetBootsCompareUI_DB();
#else
	_SetBootsCompareUI();
#endif
}

void UBWidget_BootsCompare::_ClearBootsCompareUI()
{
	C_Img_Product1->SetBrushFromTexture( nullptr, false );
	C_Img_Product2->SetBrushFromTexture( nullptr, false );
	C_Img_Product3->SetBrushFromTexture( nullptr, false );
	C_Txt_Name1->SetText( FText::FromString( "" ) );
	C_Txt_Name2->SetText( FText::FromString( "" ) );
	C_Txt_Name3->SetText( FText::FromString( "" ) );

	C_Txt_Brand1->SetText( FText::FromString( "" ) );
	C_Txt_Brand2->SetText( FText::FromString( "" ) );
	C_Txt_Brand3->SetText( FText::FromString( "" ) );

	C_Txt_Studs1->SetText( FText::FromString( "" ) );
	C_Txt_Studs2->SetText( FText::FromString( "" ) );
	C_Txt_Studs3->SetText( FText::FromString( "" ) );

	C_Txt_Upper1->SetText( FText::FromString( "" ) );
	C_Txt_Upper2->SetText( FText::FromString( "" ) );
	C_Txt_Upper3->SetText( FText::FromString( "" ) );

	C_Txt_Silo1->SetText( FText::FromString( "" ) );
	C_Txt_Silo2->SetText( FText::FromString( "" ) );
	C_Txt_Silo3->SetText( FText::FromString( "" ) );

	C_Txt_Ground1->SetText( FText::FromString( "" ) );
	C_Txt_Ground2->SetText( FText::FromString( "" ) );
	C_Txt_Ground3->SetText( FText::FromString( "" ) );

	C_Txt_Fit1->SetText( FText::FromString( "" ) );
	C_Txt_Fit2->SetText( FText::FromString( "" ) );
	C_Txt_Fit3->SetText( FText::FromString( "" ) );

	C_Txt_BallOfFoot1->SetText( FText::FromString( "" ) );
	C_Txt_BallOfFoot2->SetText( FText::FromString( "" ) );
	C_Txt_BallOfFoot3->SetText( FText::FromString( "" ) );

	C_Txt_HeightOfFoot1->SetText( FText::FromString( "" ) );
	C_Txt_HeightOfFoot2->SetText( FText::FromString( "" ) );
	C_Txt_HeightOfFoot3->SetText( FText::FromString( "" ) );

	C_Txt_Length1->SetText( FText::FromString( "" ) );
	C_Txt_Length2->SetText( FText::FromString( "" ) );
	C_Txt_Length3->SetText( FText::FromString( "" ) );

	C_Txt_Weight1->SetText( FText::FromString( "" ) );
	C_Txt_Weight2->SetText( FText::FromString( "" ) );
	C_Txt_Weight3->SetText( FText::FromString( "" ) );
	C_Txt_CompareWeight2->SetText( FText::FromString( "" ) );
	C_Txt_CompareWeight3->SetText( FText::FromString( "" ) );
	C_Img_WeightArrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_WeightArrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Price1->SetText( FText::FromString( "" ) );
	C_Txt_Price2->SetText( FText::FromString( "" ) );
	C_Txt_Price3->SetText( FText::FromString( "" ) );
	C_Txt_ComparePrice2->SetText( FText::FromString( "" ) );
	C_Txt_ComparePrice3->SetText( FText::FromString( "" ) );
	C_Img_PriceArrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_PriceArrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_ReleaseDate1->SetText( FText::FromString( "" ) );
	C_Txt_ReleaseDate2->SetText( FText::FromString( "" ) );
	C_Txt_ReleaseDate3->SetText( FText::FromString( "" ) );

	C_Txt_ProductID1->SetText( FText::FromString( "" ) );
	C_Txt_ProductID2->SetText( FText::FromString( "" ) );
	C_Txt_ProductID3->SetText( FText::FromString( "" ) );

	_ProductID1.Empty();
	_ProductID2.Empty();
	_ProductID3.Empty();
}

void UBWidget_BootsCompare::_SetBootsCompareUI()
{
	auto funcBootsCompareUISet = [this]( int32 slotIndex )
	{
		int32 bootsIndex = GInst->GetCompareBootsIndex( slotIndex );
		bool isSuccess = false;
		FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
		if( isSuccess )
		{
			FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
			UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
			if( textureBoots == nullptr )
			{
				textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
			}
			if( textureBoots != nullptr )
			{
				FString strGroundType;
				for( int32 i = 0; i < bootsSlotInfo.arGroundType.Num(); ++i )
				{
					strGroundType += UFBMUtil::GroundNameText( bootsSlotInfo.arGroundType[i] ).ToString();
					if( i < bootsSlotInfo.arGroundType.Num() - 1 )
					{
						strGroundType += TEXT( " / " );
					}
				}

				UTexture2D* textureUp = GetTexture( TEXT( "Icon/Up" ) );
				UTexture2D* textureDown = GetTexture( TEXT( "Icon/Down" ) );

				FString strReleaseDate = FString::FromInt( bootsSlotInfo.nReleaseDate );
				FString strYear = strReleaseDate.Left( 4 );
				FString strMonth = strReleaseDate.Mid( 4, 2 );
				FString strDay = strReleaseDate.Right( 2 );
				FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth;
				//FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth + TEXT( "." ) + strDay;
				int32 weightInterval = 0;
				int32 priceInterval = 0;
				if( slotIndex == 1 )
				{
					C_Img_Product1->SetBrushFromTexture( textureBoots, false );
					C_Txt_Name1->SetText( UFBMUtil::ProductNameText( bootsIndex, true ) );
					C_Txt_Brand1->SetText( UFBMUtil::BrandNameText( bootsSlotInfo.eBrandType ) );
					C_Txt_Studs1->SetText( UFBMUtil::StudsNameText( bootsSlotInfo.eStudsType ) );
					C_Txt_Upper1->SetText( UFBMUtil::UpperNameText( bootsSlotInfo.eUpperType ) );
					C_Txt_Silo1->SetText( UFBMUtil::SiloNameText( bootsSlotInfo.eSiloType ) );
					C_Txt_Ground1->SetText( FText::FromString( strGroundType ) );
					C_Txt_Fit1->SetText( UFBMUtil::SizeText( bootsSlotInfo.nWeightSize ) );
					C_Txt_BallOfFoot1->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo.nWeightBallOfFoot ) );
					C_Txt_HeightOfFoot1->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo.nWeightHeightOfFoot ) );
					C_Txt_Length1->SetText( UFBMUtil::LengthText( bootsSlotInfo.nWeightLength ) );
					C_Txt_Weight1->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo.nWeight ) ) );
					if( bootsSlotInfo.nPrice <= 0 )
					{
						C_Txt_Price1->SetText( GET_BTEXT( 86 ) );
					}
					else
					{
						C_Txt_Price1->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo.nPrice ) ) );
					}
					C_Txt_ReleaseDate1->SetText( FText::FromString( strReleaseDateFinal ) );
					C_Txt_ProductID1->SetText( bootsSlotInfo.ProductID );
					_WeightValue = bootsSlotInfo.nWeight;
					_PriceValue = bootsSlotInfo.nPrice;
				}
				else if( slotIndex == 2 )
				{
					C_Img_Product2->SetBrushFromTexture( textureBoots, false );
					C_Txt_Name2->SetText( UFBMUtil::ProductNameText( bootsIndex, true ) );
					C_Txt_Brand2->SetText( UFBMUtil::BrandNameText( bootsSlotInfo.eBrandType ) );
					C_Txt_Studs2->SetText( UFBMUtil::StudsNameText( bootsSlotInfo.eStudsType ) );
					C_Txt_Upper2->SetText( UFBMUtil::UpperNameText( bootsSlotInfo.eUpperType ) );
					C_Txt_Silo2->SetText( UFBMUtil::SiloNameText( bootsSlotInfo.eSiloType ) );
					C_Txt_Ground2->SetText( FText::FromString( strGroundType ) );
					C_Txt_Fit2->SetText( UFBMUtil::SizeText( bootsSlotInfo.nWeightSize ) );
					C_Txt_BallOfFoot2->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo.nWeightBallOfFoot ) );
					C_Txt_HeightOfFoot2->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo.nWeightHeightOfFoot ) );
					C_Txt_Length2->SetText( UFBMUtil::LengthText( bootsSlotInfo.nWeightLength ) );
					C_Txt_Weight2->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo.nWeight ) ) );
					if( bootsSlotInfo.nPrice <= 0 )
					{
						C_Txt_Price2->SetText( GET_BTEXT( 86 ) );
					}
					else
					{
						C_Txt_Price2->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo.nPrice ) ) );
					}
					C_Txt_ReleaseDate2->SetText( FText::FromString( strReleaseDateFinal ) );
					C_Txt_ProductID2->SetText( bootsSlotInfo.ProductID );

					weightInterval = bootsSlotInfo.nWeight - _WeightValue;
					C_Txt_CompareWeight2->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( abs( weightInterval ) ) ) );
					C_Txt_CompareWeight2->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Txt_CompareWeight2->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					C_Img_WeightArrow2->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Img_WeightArrow2->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					if( weightInterval == 0 )
					{
						C_Txt_CompareWeight2->SetVisibility( ESlateVisibility::Collapsed );
						C_Img_WeightArrow2->SetVisibility( ESlateVisibility::Collapsed );
					}

					priceInterval = bootsSlotInfo.nPrice - _PriceValue;
					C_Txt_ComparePrice2->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( abs( priceInterval ) ) ) );
					C_Txt_ComparePrice2->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Txt_ComparePrice2->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					C_Img_PriceArrow2->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Img_PriceArrow2->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					if( priceInterval == 0 || bootsSlotInfo.nPrice == 0 || _PriceValue == 0 )
					{
						C_Txt_ComparePrice2->SetVisibility( ESlateVisibility::Collapsed );
						C_Img_PriceArrow2->SetVisibility( ESlateVisibility::Collapsed );
					}

					if( textureUp != nullptr && textureDown != nullptr )
					{
						C_Img_WeightArrow2->SetBrushFromTexture( weightInterval < 0 ? textureDown : textureUp, false );
						C_Img_PriceArrow2->SetBrushFromTexture( priceInterval < 0 ? textureDown : textureUp, false );
					}
				}
				else if( slotIndex == 3 )
				{
					C_Img_Product3->SetBrushFromTexture( textureBoots, false );
					C_Txt_Name3->SetText( UFBMUtil::ProductNameText( bootsIndex, true ) );
					C_Txt_Brand3->SetText( UFBMUtil::BrandNameText( bootsSlotInfo.eBrandType ) );
					C_Txt_Studs3->SetText( UFBMUtil::StudsNameText( bootsSlotInfo.eStudsType ) );
					C_Txt_Upper3->SetText( UFBMUtil::UpperNameText( bootsSlotInfo.eUpperType ) );
					C_Txt_Silo3->SetText( UFBMUtil::SiloNameText( bootsSlotInfo.eSiloType ) );
					C_Txt_Ground3->SetText( FText::FromString( strGroundType ) );
					C_Txt_Fit3->SetText( UFBMUtil::SizeText( bootsSlotInfo.nWeightSize ) );
					C_Txt_BallOfFoot3->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo.nWeightBallOfFoot ) );
					C_Txt_HeightOfFoot3->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo.nWeightHeightOfFoot ) );
					C_Txt_Length3->SetText( UFBMUtil::LengthText( bootsSlotInfo.nWeightLength ) );
					C_Txt_Weight3->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo.nWeight ) ) );
					if( bootsSlotInfo.nPrice <= 0 )
					{
						C_Txt_Price3->SetText( GET_BTEXT( 86 ) );
					}
					else
					{
						C_Txt_Price3->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo.nPrice ) ) );
					}
					C_Txt_ReleaseDate3->SetText( FText::FromString( strReleaseDateFinal ) );
					C_Txt_ProductID3->SetText( bootsSlotInfo.ProductID );

					weightInterval = bootsSlotInfo.nWeight - _WeightValue;
					C_Txt_CompareWeight3->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( abs( weightInterval ) ) ) );
					C_Txt_CompareWeight3->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Txt_CompareWeight3->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					C_Img_WeightArrow3->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Img_WeightArrow3->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					if( weightInterval == 0 )
					{
						C_Txt_CompareWeight3->SetVisibility( ESlateVisibility::Collapsed );
						C_Img_WeightArrow3->SetVisibility( ESlateVisibility::Collapsed );
					}

					priceInterval = bootsSlotInfo.nPrice - _PriceValue;
					C_Txt_ComparePrice3->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( abs( priceInterval ) ) ) );
					C_Txt_ComparePrice3->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Txt_ComparePrice3->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					C_Img_PriceArrow3->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
					C_Img_PriceArrow3->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
					if( priceInterval == 0 || bootsSlotInfo.nPrice == 0 || _PriceValue == 0 )
					{
						C_Txt_ComparePrice3->SetVisibility( ESlateVisibility::Collapsed );
						C_Img_PriceArrow3->SetVisibility( ESlateVisibility::Collapsed );
					}

					if( textureUp != nullptr && textureDown != nullptr )
					{
						C_Img_WeightArrow3->SetBrushFromTexture( weightInterval < 0 ? textureDown : textureUp, false );
						C_Img_PriceArrow3->SetBrushFromTexture( priceInterval < 0 ? textureDown : textureUp, false );
					}
				}
			}			
		}
	};

	funcBootsCompareUISet( 1 );
	funcBootsCompareUISet( 2 );
	funcBootsCompareUISet( 3 );
}

void UBWidget_BootsCompare::_SetBootsCompareUI_DB()
{
	auto funcBootsCompareUISet = [this]( int32 slotIndex )
	{
		int32 bootsIndex = GInst->GetCompareBootsIndex( slotIndex );
		const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
		if( bootsSlotInfo_DB != nullptr )
		{
			FString iconURL = bootsSlotInfo_DB->IconURL;
			int32 releaseDate = bootsSlotInfo_DB->ReleaseDate;
			int32 price = bootsSlotInfo_DB->Price;

			// 제일 최신 축구화 data 찾기
			FString newProductID;
			bool isOtherProductNew = bootsSlotInfo_DB->GetNewReleaseDateProductID( newProductID );
			if( isOtherProductNew )
			{
				if( bootsSlotInfo_DB->Other_ProductURL.Contains( newProductID ) )
				{
					iconURL = bootsSlotInfo_DB->Other_ProductURL[newProductID];
				}
				if( bootsSlotInfo_DB->Other_ReleaseDate.Contains( newProductID ) )
				{
					releaseDate = bootsSlotInfo_DB->Other_ReleaseDate[newProductID];
				}
				if( bootsSlotInfo_DB->Other_Price.Contains( newProductID ) )
				{
					price = bootsSlotInfo_DB->Other_Price[newProductID];
				}
			}

			// 슬롯 이미지 셋팅
			UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( newProductID );
			if( downLoadImg != nullptr )
			{
				switch( slotIndex )
				{
				case 1:
					_ProductID1 = newProductID;
					if( C_Img_Product1 != nullptr )
					{
						C_Img_Product1->SetBrushFromTextureDynamic( downLoadImg, false );
					}
					break;
				case 2:
					_ProductID2 = newProductID;
					if( C_Img_Product2 != nullptr )
					{
						C_Img_Product2->SetBrushFromTextureDynamic( downLoadImg, false );
					}
					break;
				case 3:
					_ProductID3 = newProductID;
					if( C_Img_Product3 != nullptr )
					{
						C_Img_Product3->SetBrushFromTextureDynamic( downLoadImg, false );
					}
					break;
				default:
					break;
				}
			}
			else
			{
				switch( slotIndex )
				{
				case 1:
					_ProductID1 = newProductID;
					DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage, OnFailDownLoadCompareImage );
					break;
				case 2:
					_ProductID2 = newProductID;
					DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage2, OnFailDownLoadCompareImage2 );
					break;
				case 3:
					_ProductID3 = newProductID;
					DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage3, OnFailDownLoadCompareImage3 );
					break;
				default:
					break;
				}
			}

			FString strGroundType;
			for( int32 i = 0; i < bootsSlotInfo_DB->GroundTypes.Num(); ++i )
			{
				strGroundType += UFBMUtil::GroundNameText( bootsSlotInfo_DB->GroundTypes[i] ).ToString();
				if( i < bootsSlotInfo_DB->GroundTypes.Num() - 1 )
				{
					strGroundType += TEXT( " / " );
				}
			}

			UTexture2D* textureUp = GetTexture( TEXT( "Icon/Up" ) );
			UTexture2D* textureDown = GetTexture( TEXT( "Icon/Down" ) );

			FString strReleaseDate = FString::FromInt( releaseDate );
			FString strYear = strReleaseDate.Left( 4 );
			FString strMonth = strReleaseDate.Mid( 4, 2 );
			FString strDay = strReleaseDate.Right( 2 );
			FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth;
			//FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth + TEXT( "." ) + strDay;
			int32 weightInterval = 0;
			int32 priceInterval = 0;
			if( slotIndex == 1 )
			{
				C_Txt_Name1->SetText( UFBMUtil::ProductNameText_DB( bootsIndex, true ) );
				C_Txt_Brand1->SetText( UFBMUtil::BrandNameText( bootsSlotInfo_DB->BrandType ) );
				C_Txt_Studs1->SetText( UFBMUtil::StudsNameText( bootsSlotInfo_DB->StudsType ) );
				C_Txt_Upper1->SetText( UFBMUtil::UpperNameText( bootsSlotInfo_DB->UpperType ) );
				C_Txt_Silo1->SetText( UFBMUtil::SiloNameText( bootsSlotInfo_DB->SiloType ) );
				C_Txt_Ground1->SetText( FText::FromString( strGroundType ) );
				//C_Txt_Fit1->SetText( UFBMUtil::SizeText( bootsSlotInfo_DB->nWeightSize ) );
				//C_Txt_BallOfFoot1->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo_DB->nWeightBallOfFoot ) );
				//C_Txt_HeightOfFoot1->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo_DB->nWeightHeightOfFoot ) );
				//C_Txt_Length1->SetText( UFBMUtil::LengthText( bootsSlotInfo_DB->nWeightLength ) );
				C_Txt_Weight1->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo_DB->Weight ) ) );
				if( price <= 0 )
				{
					C_Txt_Price1->SetText( GET_BTEXT( 86 ) );
				}
				else
				{
					C_Txt_Price1->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( price ) ) );
				}
				C_Txt_ReleaseDate1->SetText( FText::FromString( strReleaseDateFinal ) );
				C_Txt_ProductID1->SetText( FText::FromString( newProductID ) );
				_WeightValue = bootsSlotInfo_DB->Weight;
				_PriceValue = price;
			}
			else if( slotIndex == 2 )
			{
				C_Txt_Name2->SetText( UFBMUtil::ProductNameText_DB( bootsIndex, true ) );
				C_Txt_Brand2->SetText( UFBMUtil::BrandNameText( bootsSlotInfo_DB->BrandType ) );
				C_Txt_Studs2->SetText( UFBMUtil::StudsNameText( bootsSlotInfo_DB->StudsType ) );
				C_Txt_Upper2->SetText( UFBMUtil::UpperNameText( bootsSlotInfo_DB->UpperType ) );
				C_Txt_Silo2->SetText( UFBMUtil::SiloNameText( bootsSlotInfo_DB->SiloType ) );
				C_Txt_Ground2->SetText( FText::FromString( strGroundType ) );
				//C_Txt_Fit2->SetText( UFBMUtil::SizeText( bootsSlotInfo_DB->nWeightSize ) );
				//C_Txt_BallOfFoot2->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo_DB->nWeightBallOfFoot ) );
				//C_Txt_HeightOfFoot2->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo_DB->nWeightHeightOfFoot ) );
				//C_Txt_Length2->SetText( UFBMUtil::LengthText( bootsSlotInfo_DB->nWeightLength ) );
				C_Txt_Weight2->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo_DB->Weight ) ) );
				if( price <= 0 )
				{
					C_Txt_Price2->SetText( GET_BTEXT( 86 ) );
				}
				else
				{
					C_Txt_Price2->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( price ) ) );
				}
				C_Txt_ReleaseDate2->SetText( FText::FromString( strReleaseDateFinal ) );
				C_Txt_ProductID2->SetText( FText::FromString( newProductID ) );

				weightInterval = bootsSlotInfo_DB->Weight - _WeightValue;
				C_Txt_CompareWeight2->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( abs( weightInterval ) ) ) );
				C_Txt_CompareWeight2->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareWeight2->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_WeightArrow2->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_WeightArrow2->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( weightInterval == 0 )
				{
					C_Txt_CompareWeight2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_WeightArrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				priceInterval = price - _PriceValue;
				C_Txt_ComparePrice2->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( abs( priceInterval ) ) ) );
				C_Txt_ComparePrice2->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_ComparePrice2->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_PriceArrow2->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_PriceArrow2->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( priceInterval == 0 || price == 0 || _PriceValue == 0 )
				{
					C_Txt_ComparePrice2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_PriceArrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				if( textureUp != nullptr && textureDown != nullptr )
				{
					C_Img_WeightArrow2->SetBrushFromTexture( weightInterval < 0 ? textureDown : textureUp, false );
					C_Img_PriceArrow2->SetBrushFromTexture( priceInterval < 0 ? textureDown : textureUp, false );
				}
			}
			else if( slotIndex == 3 )
			{
				C_Txt_Name3->SetText( UFBMUtil::ProductNameText_DB( bootsIndex, true ) );
				C_Txt_Brand3->SetText( UFBMUtil::BrandNameText( bootsSlotInfo_DB->BrandType ) );
				C_Txt_Studs3->SetText( UFBMUtil::StudsNameText( bootsSlotInfo_DB->StudsType ) );
				C_Txt_Upper3->SetText( UFBMUtil::UpperNameText( bootsSlotInfo_DB->UpperType ) );
				C_Txt_Silo3->SetText( UFBMUtil::SiloNameText( bootsSlotInfo_DB->SiloType ) );
				C_Txt_Ground3->SetText( FText::FromString( strGroundType ) );
				//C_Txt_Fit3->SetText( UFBMUtil::SizeText( bootsSlotInfo_DB->nWeightSize ) );
				//C_Txt_BallOfFoot3->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo_DB->nWeightBallOfFoot ) );
				//C_Txt_HeightOfFoot3->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo_DB->nWeightHeightOfFoot ) );
				//C_Txt_Length3->SetText( UFBMUtil::LengthText( bootsSlotInfo_DB->nWeightLength ) );
				C_Txt_Weight3->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo_DB->Weight ) ) );
				if( price <= 0 )
				{
					C_Txt_Price3->SetText( GET_BTEXT( 86 ) );
				}
				else
				{
					C_Txt_Price3->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( price ) ) );
				}
				C_Txt_ReleaseDate3->SetText( FText::FromString( strReleaseDateFinal ) );
				C_Txt_ProductID3->SetText( FText::FromString( newProductID ) );

				weightInterval = bootsSlotInfo_DB->Weight - _WeightValue;
				C_Txt_CompareWeight3->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( abs( weightInterval ) ) ) );
				C_Txt_CompareWeight3->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareWeight3->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_WeightArrow3->SetVisibility( weightInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_WeightArrow3->SetColorAndOpacity( (weightInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( weightInterval == 0 )
				{
					C_Txt_CompareWeight3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_WeightArrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				priceInterval = price - _PriceValue;
				C_Txt_ComparePrice3->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( abs( priceInterval ) ) ) );
				C_Txt_ComparePrice3->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_ComparePrice3->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_PriceArrow3->SetVisibility( priceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_PriceArrow3->SetColorAndOpacity( (priceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( priceInterval == 0 || price == 0 || _PriceValue == 0 )
				{
					C_Txt_ComparePrice3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_PriceArrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				if( textureUp != nullptr && textureDown != nullptr )
				{
					C_Img_WeightArrow3->SetBrushFromTexture( weightInterval < 0 ? textureDown : textureUp, false );
					C_Img_PriceArrow3->SetBrushFromTexture( priceInterval < 0 ? textureDown : textureUp, false );
				}
			}
		}
	};

	funcBootsCompareUISet( 1 );
	funcBootsCompareUISet( 2 );
	funcBootsCompareUISet( 3 );
}

void UBWidget_BootsCompare::_OnSuccessDownLoadCompareImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID1, texturl );

		if( C_Img_Product1 != nullptr )
		{
			C_Img_Product1->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_BootsCompare::_OnFailDownLoadCompareImage( UTexture2DDynamic* texturl )
{
	
}

void UBWidget_BootsCompare::_OnSuccessDownLoadCompareImage2( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID2, texturl );

		if( C_Img_Product2 != nullptr )
		{
			C_Img_Product2->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_BootsCompare::_OnFailDownLoadCompareImage2( UTexture2DDynamic* texturl )
{

}

void UBWidget_BootsCompare::_OnSuccessDownLoadCompareImage3( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _ProductID3, texturl );

		if( C_Img_Product3 != nullptr )
		{
			C_Img_Product3->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_BootsCompare::_OnFailDownLoadCompareImage3( UTexture2DDynamic* texturl )
{

}
