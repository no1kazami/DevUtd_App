#include "BWidget_BootsDetail.h"
#include "UI/BWidget_Top.h"
#include "UI/Boots/BWidget_BootsOptionSlot.h"
#include "UI/Equip/BWidget_EquipFilterItem.h"
#include "UI/Common/BWidget_CommonItemSlot2.h"
#include "UI/MyInfo/BWidget_BookMark.h"
#include "UI/Shop/BWidget_ShopSlot.h"
#include "UI/Shop/BWidget_ShopChart.h"
#include "../../FBM_SaveGame.h"
#include "BWidget_ReviewSlot.h"
#include "Bigtamin.h"

#define BOOTS_DETAIL_IMAGE_SIZE FVector2D( 1024.f, 512.f )

void UBWidget_BootsDetail::Init()
{
	Super::Init();

	_BootsDetailIndex = 0;

	//SetContentsSizeX( 1024.f );

	ButtonDelegate_Clicked( this, C_Btn_BookMark, &UBWidget_BootsDetail::_OnClick_BookMark );

	BP_Top_BootsDetail_UMG->Init();
	BP_Top_BootsDetail_UMG->ChangeTopMode( E_MODE::E_MODE_BOOTS_DETAIL );

	BP_ProductInfo_UMG->Init();
	BP_ProductInfo_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO, 61 );
	if( BP_ProductInfo_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_ProductInfo_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_BootsDetail::OnClickInfoFilter );
	}

	BP_ShopInfo_UMG->Init();
	BP_ShopInfo_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO, 62 );
	if( BP_ShopInfo_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_ShopInfo_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_BootsDetail::OnClickInfoFilter );
	}

	BP_Review_UMG->Init();
	BP_Review_UMG->SetDetailInfoFilterItem( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO, 82 );
	if( BP_Review_UMG->OnClickDetailInfoFilter.IsBoundToObject( this ) == false )
	{
		BP_Review_UMG->OnClickDetailInfoFilter.AddUObject( this, &UBWidget_BootsDetail::OnClickInfoFilter );
	}

	int32 showBootsDetail = UFBM_SaveGame::Get().GetShowBootsDetail();
	if (showBootsDetail == 1)
	{
		BP_ProductInfo_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		BP_Review_UMG->SetVisibility( ESlateVisibility::Collapsed );
		BP_ShopInfo_UMG->SetVisibility( ESlateVisibility::Collapsed );
	}
	else if( showBootsDetail == 2 )
	{
		BP_ProductInfo_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		BP_Review_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		BP_ShopInfo_UMG->SetVisibility( ESlateVisibility::Collapsed );
	}
	else if( showBootsDetail == 3 )
	{
		BP_ProductInfo_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		BP_Review_UMG->SetVisibility( ESlateVisibility::Collapsed );
		BP_ShopInfo_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	}
	else
	{
		BP_ProductInfo_UMG->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		BP_ShopInfo_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		BP_Review_UMG->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	}

	BP_Boots_Option_Slot_UMG->Init();

	_Ani_ProductOpenByShop = GetWidgetAnimation( _Ani_ProductOpen_ByShop_Name );
	_Ani_ProductOpenByReview = GetWidgetAnimation( _Ani_ProductOpen_ByReview_Name );

	_Ani_ShopOpenByDetail = GetWidgetAnimation( _Ani_ShopOpen_ByDetail_Name );
	_Ani_ShopOpenByReview = GetWidgetAnimation( _Ani_ShopOpen_ByReview_Name );

	_Ani_ReviewOpenByDetail = GetWidgetAnimation( _Ani_ReviewOpen_ByDetail_Name );
	_Ani_ReviewOpenByShop = GetWidgetAnimation( _Ani_ReviewOpen_ByShop_Name );

	_Ani_DetailOpen = GetWidgetAnimation( _Ani_DetailOpenName );
	_Ani_DetailClose = GetWidgetAnimation( _Ani_DetailCloseName );

	C_ScrollBox_Detail->SetRenderTranslation( FVector2D( 0.f, 0.f ) );
	C_ScrollBox_ShopInfo->SetRenderTranslation( FVector2D( 3000.f, 0.f ) );
	C_ScrollBox_ReviewInfo->SetRenderTranslation( FVector2D( 3000.f, 0.f ) );
	C_ScaleBox_ImgBoots->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	OnSuccessDownLoadDetailImage.BindUFunction( this, "_OnSuccessDownLoadDetailImage" );
	OnFailDownLoadDetailImage.BindUFunction( this, "_OnFailDownLoadDetailImage" );

	InitBootsDetail();
	InitBootsReview();

	OnClickInfoFilter( E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO, true );

	GInst->AddBackInput( this );

	PlayDetailOpenAni( true );
}

void UBWidget_BootsDetail::OnClose()
{
	Super::OnClose();
}

void UBWidget_BootsDetail::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_DetailCloseName )
		{
			CloseUI();
		}
	}
}

bool UBWidget_BootsDetail::_OnBackInput()
{
	UBWidget_BookMark* bookMarkUMG = B_HUD->GetWidgetInViewport<UBWidget_BookMark>( EBUIName::BookMark );
	if( bookMarkUMG != nullptr )
	{
		bookMarkUMG->HandleBackInput();
	}

	Super::_OnBackInput();

	PlayDetailOpenAni( false );

	return true;
}

void UBWidget_BootsDetail::_OnClick_BookMark()
{
	if ( _BootsDetailIndex > 0)
	{
		if ( UFBM_SaveGame::Get().IsBookMarkBoots( _BootsDetailIndex ) )
		{
			UFBM_SaveGame::Get().RemoveBookMarkBoots( _BootsDetailIndex );
		}
		else
		{
			UFBM_SaveGame::Get().AddBookMarkBoots( _BootsDetailIndex );
		}

		_RefreshBookMark();
	}
}

void UBWidget_BootsDetail::_RefreshBookMark()
{
	if( UFBM_SaveGame::Get().IsBookMarkBoots( _BootsDetailIndex ) )
	{
		UTexture2D* textureBookMarkOn = GetTexture( TEXT( "Icon/BookMark_On" ) );
		if( textureBookMarkOn != nullptr )
		{
			C_Img_BookMark->SetBrushFromTexture( textureBookMarkOn, false );
		}
	}
	else
	{
		UTexture2D* textureBookMark = GetTexture( TEXT( "Icon/BookMark" ) );
		if( textureBookMark != nullptr )
		{
			C_Img_BookMark->SetBrushFromTexture( textureBookMark, false );
		}
	}
}

void UBWidget_BootsDetail::InitBootsDetail()
{
	if( C_Img_Boots != nullptr )
	{
		C_Img_Boots->SetBrushFromTexture(nullptr, false);
	}

#if DB_BOOTS_DATA
	SetBootsDetailData_DB( GInst->GetCurSelectBootsIndex() );
#else
	SetBootsDetailData( GInst->GetCurSelectBootsIndex() );
#endif
}

void UBWidget_BootsDetail::InitBootsReview()
{
	C_ScrollBox_ReviewInfo->ClearChildren();
	C_ScrollBox_ReviewInfo->ScrollToStart();

#if PLATFORM_ANDROID
	int32 curSelectBootsIndex = GInst->GetCurSelectBootsIndex();
	const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( curSelectBootsIndex );
	if( bootsSlotInfo_DB != nullptr )
	{
		if ( bootsSlotInfo_DB->ReviewData.Num() == 0)
		{
			UBWidget_ReviewSlot* notSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ReviewSlot>( EDynamicWidgetParts::ReviewSlot );
			if( notSlotWidget != nullptr )
			{
				notSlotWidget->OwnerPannel = this;
				notSlotWidget->SetNotInfo( true );
				C_ScrollBox_ReviewInfo->AddChild( notSlotWidget );
			}
		}
		else
		{
			for( auto& reviewSlot : bootsSlotInfo_DB->ReviewData )
			{
				UBWidget_ReviewSlot* reviewSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ReviewSlot>( EDynamicWidgetParts::ReviewSlot );
				if( reviewSlotWidget != nullptr )
				{
					reviewSlotWidget->OwnerPannel = this;
					reviewSlotWidget->SetReviewSlotData( reviewSlot );
					C_ScrollBox_ReviewInfo->AddChild( reviewSlotWidget );
				}
			}
		}
	}
#else
	TArray<FST_REVIEW_DATA> reviewList;
	FST_REVIEW_DATA tempData1( TEXT( "코파 문디알 FG SIZE REVIEW" ), TEXT( "Youtube - 크레이지11" ), TEXT( "https://i.ytimg.com/vi/XSTOzeevlrI/hq720.jpg?sqp=-oaymwEZCOgCEMoBSFXyq4qpAwsIARUAAIhCGAFwAQ==&amp;rs=AOn4CLAmUwEvG5BYFrUo7x6vd70y8Z4LbA" ), TEXT( "https://youtu.be/XSTOzeevlrI" ) );
	FST_REVIEW_DATA tempData2( TEXT( "아디다스 코파 문디알 Classic Of The Classic" ), TEXT( "Youtube - 레플리카룸TV" ), TEXT( "https://i.ytimg.com/vi/4mfw-xfxXI8/hq720.jpg?sqp=-oaymwEZCOgCEMoBSFXyq4qpAwsIARUAAIhCGAFwAQ==&amp;rs=AOn4CLCBqwNjfXMjl0wRQU29rWFS-ByoKQ" ), TEXT( "https://youtu.be/4mfw-xfxXI8" ) );
	
	reviewList.Add( tempData1 );
	reviewList.Add( tempData2 );

	for( auto& reviewSlot : reviewList )
	{
		UBWidget_ReviewSlot* reviewSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ReviewSlot>( EDynamicWidgetParts::ReviewSlot );
		if( reviewSlotWidget != nullptr )
		{
			reviewSlotWidget->OwnerPannel = this;
			reviewSlotWidget->SetReviewSlotData( reviewSlot );
			C_ScrollBox_ReviewInfo->AddChild( reviewSlotWidget );
		}
	}
#endif
}

void UBWidget_BootsDetail::SetBootsDetailData( const int32 bootsIndex )
{
	if( bootsIndex <= 0 )
		return;

	_BootsProductID.Empty();
	_BootsDetailIndex = bootsIndex;

	//InitSwipeScrollComponent();

	bool isSuccess = false;
	FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
	if( isSuccess )
	{
		/*
		// 축구화 이미지 셋팅
		auto funcBootsImageSet = [this]( FString strImage, bool isLast )
		{
			UTexture2D* textureBoots = GetTexture( strImage );
			if( textureBoots != nullptr )
			{
				UImage* bootsImage = NewObject<UImage>( UImage::StaticClass() );
				if( bootsImage != nullptr )
				{
					bootsImage->SetBrushFromTexture( textureBoots, true );
					bootsImage->SetBrushSize( BOOTS_DETAIL_IMAGE_SIZE );
					bootsImage->SetVisibility( ESlateVisibility::Visible );
					AddSwipeScrollChild( bootsImage, isLast);
				}
			}
		};

		funcBootsImageSet( bootsSlotInfo.IconPath.ToString(), false );
		funcBootsImageSet( bootsSlotInfo.IconPath2.ToString(), false );
		funcBootsImageSet( bootsSlotInfo.IconPath3.ToString(), false );
		funcBootsImageSet( bootsSlotInfo.IconPath4.ToString(), false );
		funcBootsImageSet( bootsSlotInfo.IconPath5.ToString(), true);
		*/

		// 축구화 이미지 셋팅
		FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsSlotInfo.ProductID );
		UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
		if( textureBoots == nullptr )
		{
			textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
		}
		if( textureBoots != nullptr )
		{
			C_Img_Boots->SetBrushFromTexture( textureBoots, false );
		}

		// 브랜드 이미지 셋팅
		UTexture2D* textureLogo = GetTexture( UFBMUtil::BrandLogoPath( bootsSlotInfo.eBrandType ) );
		if( textureLogo != nullptr )
		{
			C_Img_Logo->SetBrushFromTexture( textureLogo, true );
		}

		// 여러 색상 셋팅
		_SubOtherProduct.Empty();
		C_SB_OtherProduct->ClearChildren();
		C_SB_OtherProduct->ScrollToStart();
		UBWidget_CommonItemSlot2* mainCommmonSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_CommonItemSlot2>( EDynamicWidgetParts::CommonItemSlot2 );
		if( mainCommmonSlotWidget != nullptr )
		{
			mainCommmonSlotWidget->SetCommonItemSlotData( E_COMMON_ITEM_SLOT_TYPE::BOOTS, bootsIndex, MAIN_BOOTS_COLOR_SLOT, true );
			if( mainCommmonSlotWidget->OnClickItemColorSlot.IsBoundToObject( this ) == false )
			{
				mainCommmonSlotWidget->OnClickItemColorSlot.AddUObject( this, &UBWidget_BootsDetail::OnClickOtherItem );
			}
			C_SB_OtherProduct->AddChild( mainCommmonSlotWidget );
			_SubOtherProduct.Add( mainCommmonSlotWidget );
		}

		int showNum = bootsSlotInfo.Other_ProductID.Num();
		for( int32 productIDIndex = 0; productIDIndex < showNum; ++productIDIndex )
		{
			UBWidget_CommonItemSlot2* commmonSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_CommonItemSlot2>( EDynamicWidgetParts::CommonItemSlot2 );
			if( commmonSlotWidget != nullptr )
			{
				commmonSlotWidget->SetCommonItemSlotData( E_COMMON_ITEM_SLOT_TYPE::BOOTS, bootsIndex, productIDIndex, false );
				if( commmonSlotWidget->OnClickItemColorSlot.IsBoundToObject( this ) == false )
				{
					commmonSlotWidget->OnClickItemColorSlot.AddUObject( this, &UBWidget_BootsDetail::OnClickOtherItem );
				}
				C_SB_OtherProduct->AddChild( commmonSlotWidget );
				_SubOtherProduct.Add( commmonSlotWidget );
			}
		}

		// 제품명
		C_Txt_ProductName->SetText( UFBMUtil::ProductNameText( bootsIndex, false ) );
		// 브랜드명
		C_Txt_Brand->SetText( UFBMUtil::BrandNameText( bootsSlotInfo.eBrandType ) );
		// 스터드 타입
		C_Txt_Studs->SetText( UFBMUtil::StudsNameText( bootsSlotInfo.eStudsType ) );
		// 어퍼(외피) 타입
		C_Txt_Upper->SetText( UFBMUtil::UpperNameText( bootsSlotInfo.eUpperType ) );
		// 사일로 타입
		C_Txt_Silo->SetText( UFBMUtil::SiloNameText( bootsSlotInfo.eSiloType ) );
		// 그라운드 타입
		FString strGroundType;
		for( int32 i = 0; i < bootsSlotInfo.arGroundType.Num(); ++i )
		{
			strGroundType += UFBMUtil::GroundNameText( bootsSlotInfo.arGroundType[i] ).ToString();
			if( i < bootsSlotInfo.arGroundType.Num() - 1 )
			{
				strGroundType += TEXT( " / " );
			}
		}
		C_Txt_Ground->SetText( FText::FromString( strGroundType ) );
		// Fit(사이즈)
		C_Txt_Fit->SetText( UFBMUtil::SizeText( bootsSlotInfo.nWeightSize ) );
		// 발볼
		C_Txt_BallOfFoot->SetText( UFBMUtil::BallOfFootText( bootsSlotInfo.nWeightBallOfFoot ) );
		// 발등
		C_Txt_HeightOfFoot->SetText( UFBMUtil::HeightOfFootText( bootsSlotInfo.nWeightHeightOfFoot ) );
		// 길이
		C_Txt_Length->SetText( UFBMUtil::LengthText( bootsSlotInfo.nWeightLength ) );
		// 무게
		C_Txt_Weight->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo.nWeight ) ) );
		// 가격
		if ( bootsSlotInfo.nPrice <= 0 )
		{
			C_Txt_Price->SetText( GET_BTEXT( 86 ) );
		}
		else
		{
			C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo.nPrice ) ) );
		}

		// 출시일
		if( bootsSlotInfo.nReleaseDate <= 0 )
		{
			C_Txt_ReleaseDate->SetText( GET_BTEXT( 86 ) );
		}
		else
		{
			FString strReleaseDate = FString::FromInt( bootsSlotInfo.nReleaseDate );
			FString strYear = strReleaseDate.Left( 4 );
			FString strMonth = strReleaseDate.Mid( 4, 2 );
			FString strDay = strReleaseDate.Right( 2 );
			FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth;
			//FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth + TEXT( "." ) + strDay;
			C_Txt_ReleaseDate->SetText( FText::FromString( strReleaseDateFinal ) );
		}

		// 제품코드
		C_Txt_ProductID->SetText( bootsSlotInfo.ProductID );
		_BootsProductID = bootsSlotInfo.ProductID.ToString();
		// 북마크 셋팅
		_RefreshBookMark();
	}
}

void UBWidget_BootsDetail::SetBootsDetailData_DB( const int32 bootsIndex )
{
	if( bootsIndex <= 0 )
		return;

	_BootsProductID.Empty();
	_BootsDetailIndex = bootsIndex;

	//InitSwipeScrollComponent();

	const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
	if( bootsSlotInfo_DB != nullptr )
	{
		//************************ 공통 Data ***************************************************************************
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
		// 사일로 타입
		C_Txt_Silo->SetText( UFBMUtil::SiloNameText( bootsSlotInfo_DB->SiloType ) );
		// 그라운드 타입
		FString strGroundType;
		for( int32 i = 0; i < bootsSlotInfo_DB->GroundTypes.Num(); ++i )
		{
			strGroundType += UFBMUtil::GroundNameText( bootsSlotInfo_DB->GroundTypes[i] ).ToString();
			if( i < bootsSlotInfo_DB->GroundTypes.Num() - 1 )
			{
				strGroundType += TEXT( " / " );
			}
		}
		C_Txt_Ground->SetText( FText::FromString( strGroundType ) );
		// 무게
		C_Txt_Weight->SetText( FText::Format( GET_BTEXT( 36 ), FText::AsNumber( bootsSlotInfo_DB->Weight ) ) );
		//*************************************************************************************************************

		//************************* 개별 Data ***********************************************************************
		// 제일 최신 축구화 data 찾기
		FString newProductID;
		bool isOtherProductNew = bootsSlotInfo_DB->GetNewReleaseDateProductID( newProductID );

		// 제품코드
		C_Txt_ProductID->SetText( FText::FromString( newProductID ) );
		_BootsProductID = newProductID;

		FString bootsURL;
		if ( isOtherProductNew )
		{
			// 가격
			if( bootsSlotInfo_DB->Other_Price.Contains( newProductID ) )
			{
				if( bootsSlotInfo_DB->Other_Price[newProductID] <= 0 )
				{
					C_Txt_Price->SetText( GET_BTEXT( 86 ) );
				}
				else
				{
					C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo_DB->Other_Price[newProductID] ) ) );
				}
			}
			
			// 출시일
			if( bootsSlotInfo_DB->Other_ReleaseDate.Contains( newProductID ) )
			{
				if( bootsSlotInfo_DB->Other_ReleaseDate[newProductID] <= 0 )
				{
					C_Txt_ReleaseDate->SetText( GET_BTEXT( 86 ) );
				}
				else
				{
					FString strReleaseDate = FString::FromInt( bootsSlotInfo_DB->Other_ReleaseDate[newProductID] );
					FString strYear = strReleaseDate.Left( 4 );
					FString strMonth = strReleaseDate.Mid( 4, 2 );
					FString strDay = strReleaseDate.Right( 2 );
					FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth; //+ TEXT( "." ) + strDay;
					C_Txt_ReleaseDate->SetText( FText::FromString( strReleaseDateFinal ) );
				}
			}

			if( bootsSlotInfo_DB->Other_ProductURL.Contains( newProductID ) )
			{
				bootsURL = bootsSlotInfo_DB->Other_ProductURL[newProductID];
			}
		}
		else
		{
			// 가격
			if( bootsSlotInfo_DB->Price <= 0 )
			{
				C_Txt_Price->SetText( GET_BTEXT( 86 ) );
			}
			else
			{
				C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( bootsSlotInfo_DB->Price ) ) );
			}

			// 출시일
			if( bootsSlotInfo_DB->ReleaseDate <= 0 )
			{
				C_Txt_ReleaseDate->SetText( GET_BTEXT( 86 ) );
			}
			else
			{
				FString strReleaseDate = FString::FromInt( bootsSlotInfo_DB->ReleaseDate );
				FString strYear = strReleaseDate.Left( 4 );
				FString strMonth = strReleaseDate.Mid( 4, 2 );
				FString strDay = strReleaseDate.Right( 2 );
				FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth; //+ TEXT( "." ) + strDay;
				C_Txt_ReleaseDate->SetText( FText::FromString( strReleaseDateFinal ) );
			}

			bootsURL = bootsSlotInfo_DB->IconURL;
		}

		// 축구화 이미지 셋팅
		UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( newProductID );
		if( downLoadImg != nullptr )
		{
			if( C_Img_Boots != nullptr )
			{
				C_Img_Boots->SetBrushFromTextureDynamic( downLoadImg, false );
			}
		}
		else
		{
			if( bootsURL.IsEmpty() == false )
			{
				DownLoadTexture_URL( bootsURL, OnSuccessDownLoadDetailImage, OnFailDownLoadDetailImage );
			}
		}

		// 여러 색상 셋팅
		_SubOtherProduct.Empty();
		C_SB_OtherProduct->ClearChildren();
		C_SB_OtherProduct->ScrollToStart();

		auto addBootsSlot = [this]( int32 productBootsIndex, int32 productSlotIndex, bool isSelect )
		{
			UBWidget_CommonItemSlot2* mainCommmonSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_CommonItemSlot2>( EDynamicWidgetParts::CommonItemSlot2 );
			if( mainCommmonSlotWidget != nullptr )
			{
				mainCommmonSlotWidget->SetCommonItemSlotData_DB( E_COMMON_ITEM_SLOT_TYPE::BOOTS, productBootsIndex, productSlotIndex, isSelect );
				if( mainCommmonSlotWidget->OnClickItemColorSlot.IsBoundToObject( this ) == false )
				{
					mainCommmonSlotWidget->OnClickItemColorSlot.AddUObject( this, &UBWidget_BootsDetail::OnClickOtherItem_DB );
				}
				C_SB_OtherProduct->AddChild( mainCommmonSlotWidget );
				_SubOtherProduct.Add( mainCommmonSlotWidget );
			}
		};

		if (isOtherProductNew)
		{
			int32 mainIndex = bootsSlotInfo_DB->Other_ProductID.Find( newProductID );
			if (mainIndex != INDEX_NONE)
			{
				addBootsSlot( bootsIndex, mainIndex, true );

				bool isCsvFirstItemAdd = false;
				int32 csvFirstItemIndex = bootsSlotInfo_DB->GetCsvReleasedateIndex();
				int showNum = bootsSlotInfo_DB->Other_ProductID.Num();
				for( int32 productIDIndex = 0; productIDIndex < showNum; ++productIDIndex )
				{
					if( productIDIndex == csvFirstItemIndex )
					{
						addBootsSlot( bootsIndex, MAIN_BOOTS_COLOR_SLOT, false );
						isCsvFirstItemAdd = true;
					}

					if ( productIDIndex != mainIndex)
					{
						addBootsSlot( bootsIndex, productIDIndex, false );
					}
				}
				if( isCsvFirstItemAdd == false )
				{
					addBootsSlot( bootsIndex, MAIN_BOOTS_COLOR_SLOT, false );
				}
			}
		}
		else
		{
			addBootsSlot( bootsIndex, MAIN_BOOTS_COLOR_SLOT, true );
			int showNum = bootsSlotInfo_DB->Other_ProductID.Num();
			for( int32 productIDIndex = 0; productIDIndex < showNum; ++productIDIndex )
			{
				addBootsSlot( bootsIndex, productIDIndex, false );
			}
		}
		//*************************************************************************************************************

		// 북마크 셋팅
		_RefreshBookMark();
	}
}

void UBWidget_BootsDetail::PlayProductOpenAni( const E_FILTER_ITEM_TYPE prevFilterType )
{
	if( IsAnimationPlaying( _Ani_ShopOpenByDetail ) )
	{
		StopAnimation( _Ani_ShopOpenByDetail );
	}
	if( IsAnimationPlaying( _Ani_ShopOpenByReview ) )
	{
		StopAnimation( _Ani_ShopOpenByReview );
	}
	if( IsAnimationPlaying( _Ani_ReviewOpenByDetail ) )
	{
		StopAnimation( _Ani_ReviewOpenByDetail );
	}
	if( IsAnimationPlaying( _Ani_ReviewOpenByShop ) )
	{
		StopAnimation( _Ani_ReviewOpenByShop );
	}

	if( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO )
	{
		if( IsAnimationPlaying( _Ani_ProductOpenByShop ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ProductOpenByReview ) )
		{
			StopAnimation( _Ani_ProductOpenByReview );
		}

		PlayAnimation( _Ani_ProductOpenByShop );
	}
	else if( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO )
	{
		if( IsAnimationPlaying( _Ani_ProductOpenByReview ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ProductOpenByShop ) )
		{
			StopAnimation( _Ani_ProductOpenByShop );
		}

		PlayAnimation( _Ani_ProductOpenByReview );
	}
}

void UBWidget_BootsDetail::PlayShopOpenAni( const E_FILTER_ITEM_TYPE prevFilterType )
{
	if( IsAnimationPlaying( _Ani_ProductOpenByShop ) )
	{
		StopAnimation( _Ani_ProductOpenByShop );
	}
	if( IsAnimationPlaying( _Ani_ProductOpenByReview ) )
	{
		StopAnimation( _Ani_ProductOpenByReview );
	}
	if( IsAnimationPlaying( _Ani_ReviewOpenByDetail ) )
	{
		StopAnimation( _Ani_ReviewOpenByDetail );
	}
	if( IsAnimationPlaying( _Ani_ReviewOpenByShop ) )
	{
		StopAnimation( _Ani_ReviewOpenByShop );
	}

	if( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO )
	{
		if( IsAnimationPlaying( _Ani_ShopOpenByDetail ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ShopOpenByReview ) )
		{
			StopAnimation( _Ani_ShopOpenByReview );
		}

		PlayAnimation( _Ani_ShopOpenByDetail );
	}
	else if( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO )
	{
		if( IsAnimationPlaying( _Ani_ShopOpenByReview ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ShopOpenByDetail ) )
		{
			StopAnimation( _Ani_ShopOpenByDetail );
		}

		PlayAnimation( _Ani_ShopOpenByReview );
	}
}

void UBWidget_BootsDetail::PlayReviewOpenAni( const E_FILTER_ITEM_TYPE prevFilterType )
{
	if( IsAnimationPlaying( _Ani_ProductOpenByShop ) )
	{
		StopAnimation( _Ani_ProductOpenByShop );
	}
	if( IsAnimationPlaying( _Ani_ProductOpenByReview ) )
	{
		StopAnimation( _Ani_ProductOpenByReview );
	}
	if( IsAnimationPlaying( _Ani_ShopOpenByDetail ) )
	{
		StopAnimation( _Ani_ShopOpenByDetail );
	}
	if( IsAnimationPlaying( _Ani_ShopOpenByReview ) )
	{
		StopAnimation( _Ani_ShopOpenByReview );
	}

	if ( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO )
	{
		if( IsAnimationPlaying( _Ani_ReviewOpenByDetail ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ReviewOpenByShop ) )
		{
			StopAnimation( _Ani_ReviewOpenByShop );
		}

		PlayAnimation( _Ani_ReviewOpenByDetail );
	}
	else if ( prevFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO )
	{
		if( IsAnimationPlaying( _Ani_ReviewOpenByShop ) )
		{
			return;
		}
		if( IsAnimationPlaying( _Ani_ReviewOpenByDetail ) )
		{
			StopAnimation( _Ani_ReviewOpenByDetail );
		}

		PlayAnimation( _Ani_ReviewOpenByShop );
	}
}

void UBWidget_BootsDetail::PlayDetailOpenAni( const bool isDetailOpen )
{
	if( isDetailOpen )
	{
		if( _Ani_DetailOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_DetailOpen ) )
			{
				StopAnimation( _Ani_DetailOpen );
			}

			PlayAnimation( _Ani_DetailOpen );
		}
	}
	else
	{
		if( _Ani_DetailClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_DetailClose ) )
			{
				StopAnimation( _Ani_DetailClose );
			}

			PlayAnimation( _Ani_DetailClose );
		}
	}
}

void UBWidget_BootsDetail::OnClickInfoFilter( const E_FILTER_ITEM_TYPE infoFilterType, bool isForce /*= true */ )
{
	if( isForce == false && _InfoFilterType == infoFilterType )
	{
		return;
	}

	E_FILTER_ITEM_TYPE prevFilterType = _InfoFilterType;
	_InfoFilterType = infoFilterType;

	switch( infoFilterType )
	{
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO:
		BP_ProductInfo_UMG->SelectDetailInfoFilterItem( true );
		BP_ShopInfo_UMG->SelectDetailInfoFilterItem( false );
		BP_Review_UMG->SelectDetailInfoFilterItem( false );
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO:
		BP_ProductInfo_UMG->SelectDetailInfoFilterItem( false );
		BP_ShopInfo_UMG->SelectDetailInfoFilterItem( true );
		BP_Review_UMG->SelectDetailInfoFilterItem( false );
		_SetShopInfo();
		break;
	case E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO:
		BP_ProductInfo_UMG->SelectDetailInfoFilterItem( false );
		BP_ShopInfo_UMG->SelectDetailInfoFilterItem( false );
		BP_Review_UMG->SelectDetailInfoFilterItem( true );
		break;
	default:
		break;
	}

	if( isForce == false )
	{
		if( infoFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO )
		{
			C_ScrollBox_ShopInfo->ScrollToStart();
			PlayShopOpenAni( prevFilterType );
			//PlayInfoOpenAni( true );
		}
		else if ( infoFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_PRODUCT_INFO )
		{
			C_ScrollBox_Detail->ScrollToStart();
			PlayProductOpenAni( prevFilterType );
			//PlayInfoOpenAni( false );
		}
		else if( infoFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_REVIEW_INFO )
		{
			C_ScrollBox_ReviewInfo->ScrollToStart();
			PlayReviewOpenAni( prevFilterType );
		}
	}
}

void UBWidget_BootsDetail::OnClickOtherItem( const int32 bootsIndex, const int32 bootsIDIndex )
{
	bool isSuccess = false;
	FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
	if( isSuccess )
	{
		// 축구화 이미지 셋팅
		FText bootsProductID;
		if( bootsIDIndex == MAIN_BOOTS_COLOR_SLOT )
		{
			bootsProductID = bootsSlotInfo.ProductID;
		}
		else if( bootsSlotInfo.Other_ProductID.Num() > bootsIDIndex )
		{
			bootsProductID = bootsSlotInfo.Other_ProductID[bootsIDIndex];
		}

		FText iconPath = FText::Format( FText::FromString( "{0}_{1}" ), bootsSlotInfo.IconPath, bootsProductID );
		UTexture2D* textureBoots = GetTexture( iconPath.ToString() );
		if( textureBoots == nullptr )
		{
			textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
		}
		if (textureBoots == nullptr)
		{
			textureBoots = GetTexture( bootsSlotInfo.IconPath.ToString() );
		}

		if( textureBoots != nullptr )
		{
			C_Img_Boots->SetBrushFromTexture( textureBoots, false );
		}

		// 제품코드
		if ( bootsProductID.IsEmpty() == false)
		{
			C_Txt_ProductID->SetText( bootsProductID );
			_BootsProductID = bootsProductID.ToString();
		}

		// shop 셋팅
		if( _InfoFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO )
		{
			_SetShopInfo();
		}

		// 작은 아이콘 언더라인 셋팅
		for (auto& otherProduct : _SubOtherProduct )
		{
			if ( otherProduct->GetProductIndex() == bootsIDIndex )
			{
				otherProduct->SetSelectLine( true );
			}
			else
			{
				otherProduct->SetSelectLine( false );
			}
		}
	}
}

void UBWidget_BootsDetail::OnClickOtherItem_DB( const int32 bootsIndex, const int32 bootsIDIndex )
{
	const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
	if( bootsSlotInfo_DB != nullptr )
	{
		FString bootsProductID;
		FString bootsURL;
		int32 price = 0;
		int32 releaseDate = 0;
		if( bootsIDIndex == MAIN_BOOTS_COLOR_SLOT )
		{
			// 품번 셋팅 
			bootsProductID = bootsSlotInfo_DB->ProductID;
			// 가격 설정
			price = bootsSlotInfo_DB->Price;
			// 출시일 설정
			releaseDate = bootsSlotInfo_DB->ReleaseDate;
			// 축구화 이미지 셋팅
			bootsURL = bootsSlotInfo_DB->IconURL;
		}
		else if( bootsSlotInfo_DB->Other_ProductID.Num() > bootsIDIndex )
		{
			// 품번 셋팅 
			bootsProductID = bootsSlotInfo_DB->Other_ProductID[bootsIDIndex];
			// 가격 설정
			if( bootsSlotInfo_DB->Other_Price.Contains( bootsProductID ) )
			{
				price = bootsSlotInfo_DB->Other_Price[bootsProductID];
			}
			// 출시일 설정
			if( bootsSlotInfo_DB->Other_ReleaseDate.Contains( bootsProductID ) )
			{
				releaseDate = bootsSlotInfo_DB->Other_ReleaseDate[bootsProductID];
			}
			// 축구화 이미지 셋팅
			if( bootsSlotInfo_DB->Other_ProductURL.Contains( bootsProductID ) )
			{
				bootsURL = bootsSlotInfo_DB->Other_ProductURL[bootsProductID];
			}
		}

		// 가격
		if( price <= 0 )
		{
			C_Txt_Price->SetText( GET_BTEXT( 86 ) );
		}
		else
		{
			C_Txt_Price->SetText( FText::Format( GET_BTEXT( 79 ), FText::AsNumber( price ) ) );
		}

		// 출시일
		if( releaseDate <= 0 )
		{
			C_Txt_ReleaseDate->SetText( GET_BTEXT( 86 ) );
		}
		else
		{
			FString strReleaseDate = FString::FromInt( releaseDate );
			FString strYear = strReleaseDate.Left( 4 );
			FString strMonth = strReleaseDate.Mid( 4, 2 );
			FString strDay = strReleaseDate.Right( 2 );
			FString strReleaseDateFinal = strYear + TEXT( "." ) + strMonth; //+ TEXT( "." ) + strDay;
			C_Txt_ReleaseDate->SetText( FText::FromString( strReleaseDateFinal ) );
		}

		// 제품코드
		if( bootsProductID.IsEmpty() == false )
		{
			C_Txt_ProductID->SetText( FText::FromString( bootsProductID ) );
			_BootsProductID = bootsProductID;
		}

		// 축구화 이미지 셋팅
		UTexture2DDynamic* downLoadImg = GInst->GetDownLoadBootsImage( bootsProductID );
		if( downLoadImg != nullptr )
		{
			if( C_Img_Boots != nullptr )
			{
				C_Img_Boots->SetBrushFromTextureDynamic( downLoadImg, false );
			}
		}
		else
		{
			if( bootsURL.IsEmpty() == false )
			{
				DownLoadTexture_URL( bootsURL, OnSuccessDownLoadDetailImage, OnFailDownLoadDetailImage );
			}
		}

		// shop 셋팅
		if( _InfoFilterType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_SHOP_INFO )
		{
			_SetShopInfo();
		}

		// 작은 아이콘 언더라인 셋팅
		for( auto& otherProduct : _SubOtherProduct )
		{
			if( otherProduct->GetProductIndex() == bootsIDIndex )
			{
				otherProduct->SetSelectLine( true );
			}
			else
			{
				otherProduct->SetSelectLine( false );
			}
		}
	}
}

void UBWidget_BootsDetail::_SetShopInfo()
{
	C_ScrollBox_ShopInfo->ClearChildren();
	C_ScrollBox_ShopInfo->ScrollToStart();

	const FST_BOOTS_CRAWLING_DATA* crawlingData = UFBM_SaveGame::Get().GetBootsCrawlingData( _BootsProductID );
	if( crawlingData != nullptr )
	{
		// 국내 쇼핑몰
		bool domesticFirstCheck = false;
		for( auto& elemInfo : crawlingData->CrawlingInfo )
		{
			if( elemInfo.Value.IsDomestic == true )
			{
				UBWidget_ShopSlot* shopSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
				if( shopSlotWidget != nullptr )
				{
					if( domesticFirstCheck == false )
					{
						shopSlotWidget->SetTopNotInfo( true, true );
						domesticFirstCheck = true;
					}

					shopSlotWidget->OwnerPannel = this;
					shopSlotWidget->SetShopSlotData( elemInfo.Key, elemInfo.Value.UrlData, elemInfo.Value.PriceData );
					C_ScrollBox_ShopInfo->AddChild( shopSlotWidget );

					USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
					if( addSpacer != nullptr )
					{
						addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
						C_ScrollBox_ShopInfo->AddChild( addSpacer );
					}
				}
			}
		}

		//국내 쇼핑몰 차트
		if ( domesticFirstCheck )
		{
			UBWidget_ShopChart* shopChartWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopChart>( EDynamicWidgetParts::ShopChart );
			if( shopChartWidget != nullptr )
			{
				USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
				if( addSpacer != nullptr )
				{
					addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
					C_ScrollBox_ShopInfo->AddChild( addSpacer );
				}

				shopChartWidget->OwnerPannel = this;
				shopChartWidget->SetShopData( _BootsProductID );
				shopChartWidget->SetChartDay();
				C_ScrollBox_ShopInfo->AddChild( shopChartWidget );

				USpacer* addSpacerUnder = NewObject<USpacer>( USpacer::StaticClass() );
				if( addSpacerUnder != nullptr )
				{
					addSpacerUnder->SetSize( FVector2D( 0.f, 100.f ) );
					C_ScrollBox_ShopInfo->AddChild( addSpacerUnder );
				}
			}
		}

		// 해외 쇼핑몰
		bool globalFirstCheck = false;
		for( auto& elemInfo : crawlingData->CrawlingInfo )
		{
			if( elemInfo.Value.IsDomestic == false )
			{
				UBWidget_ShopSlot* shopSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
				if( shopSlotWidget != nullptr )
				{
					if( globalFirstCheck == false )
					{
						shopSlotWidget->SetTopNotInfo( true, false );
						globalFirstCheck = true;
					}

					shopSlotWidget->OwnerPannel = this;
					shopSlotWidget->SetShopSlotData( elemInfo.Key, elemInfo.Value.UrlData, elemInfo.Value.PriceData );
					C_ScrollBox_ShopInfo->AddChild( shopSlotWidget );

					USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
					if( addSpacer != nullptr )
					{
						addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
						C_ScrollBox_ShopInfo->AddChild( addSpacer );
					}
				}
			}
		}
	}
	else
	{
		UBWidget_ShopSlot* shopSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
		if( shopSlotWidget != nullptr )
		{
			shopSlotWidget->OwnerPannel = this;
			shopSlotWidget->SetNotInfo( true );
			C_ScrollBox_ShopInfo->AddChild( shopSlotWidget );
		}
	}

	////////// TEST ///////////////////////
	_TestShopInfo();
	//////////////////////////////////////////
}

////////// TEST ///////////////////////
void UBWidget_BootsDetail::_TestShopInfo()
{
#if PLATFORM_WINDOWS
	UBWidget_ShopSlot* shopSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget != nullptr )
	{
		shopSlotWidget->SetTopNotInfo( true, true );
		shopSlotWidget->OwnerPannel = this;
		shopSlotWidget->SetShopSlotData( E_CRAWLING_WEBPAGE::HMALL, "www.naver.com", 275000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget2 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget2 != nullptr )
	{
		shopSlotWidget2->OwnerPannel = this;
		shopSlotWidget2->SetShopSlotData( E_CRAWLING_WEBPAGE::GMARKET, "www.naver.com", 175000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget2 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget3 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget3 != nullptr )
	{
		shopSlotWidget3->OwnerPannel = this;
		shopSlotWidget3->SetShopSlotData( E_CRAWLING_WEBPAGE::AUCTION, "www.naver.com", 235000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget3 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopChart* shopChartWidget = B_HUD->CreateDynamicWidget<UBWidget_ShopChart>( EDynamicWidgetParts::ShopChart );
	if( shopChartWidget != nullptr )
	{
		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}

		shopChartWidget->OwnerPannel = this;
		shopChartWidget->SetShopData( _BootsProductID );
		shopChartWidget->SetChartDay();
		C_ScrollBox_ShopInfo->AddChild( shopChartWidget );

		USpacer* addSpacerUnder = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacerUnder != nullptr )
		{
			addSpacerUnder->SetSize( FVector2D( 0.f, 100.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacerUnder );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget4 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget4 != nullptr )
	{
		shopSlotWidget4->OwnerPannel = this;
		shopSlotWidget4->SetShopSlotData( E_CRAWLING_WEBPAGE::PDS, "www.naver.com", 235000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget4 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget5 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget5 != nullptr )
	{
		shopSlotWidget5->OwnerPannel = this;
		shopSlotWidget5->SetShopSlotData( E_CRAWLING_WEBPAGE::PDS_US, "www.naver.com", 235000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget5 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget6 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget6 != nullptr )
	{
		shopSlotWidget6->OwnerPannel = this;
		shopSlotWidget6->SetShopSlotData( E_CRAWLING_WEBPAGE::UNI, "www.naver.com", 235000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget6 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}

	UBWidget_ShopSlot* shopSlotWidget7 = B_HUD->CreateDynamicWidget<UBWidget_ShopSlot>( EDynamicWidgetParts::ShopSlot );
	if( shopSlotWidget7 != nullptr )
	{
		shopSlotWidget7->OwnerPannel = this;
		shopSlotWidget7->SetShopSlotData( E_CRAWLING_WEBPAGE::SOCCER, "www.naver.com", 235000 );
		C_ScrollBox_ShopInfo->AddChild( shopSlotWidget7 );

		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_ShopInfo->AddChild( addSpacer );
		}
	}
#endif
}
/////////////////////////////////////////////////////


void UBWidget_BootsDetail::_OnSuccessDownLoadDetailImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadBootsImage( _BootsProductID, texturl );
		
		if( C_Img_Boots != nullptr )
		{
			C_Img_Boots->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_BootsDetail::_OnFailDownLoadDetailImage( UTexture2DDynamic* texturl )
{

}