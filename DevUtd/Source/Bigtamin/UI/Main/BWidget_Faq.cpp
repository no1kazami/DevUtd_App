// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_Faq.h"
#include "UI/BWidget_Top.h"
#include "BWidget_FaqSlot.h"
#include "Bigtamin.h"
#include "../../FBM_SaveGame.h"

void UBWidget_Faq::Init()
{
	Super::Init();

	BP_Top_Faq_UMG->Init();
	BP_Top_Faq_UMG->ChangeTopMode( E_MODE::E_MODE_FAQ );

	_Ani_FaqSlotOpen = GetWidgetAnimation( _Ani_FaqSlotOpenName );
	_Ani_FaqSlotClose = GetWidgetAnimation( _Ani_FaqSlotCloseName );

	InitFaq();

	GInst->AddBackInput( this );
}

void UBWidget_Faq::OnClose()
{
	Super::OnClose();
}

void UBWidget_Faq::InitFaq()
{
	C_ScrollBox_Faq->ClearChildren();
	C_ScrollBox_Faq->ScrollToStart();

#if PLATFORM_ANDROID
	const TArray<FST_FAQ_DATA> faqData = UFBM_SaveGame::Get().GetFaqData();
#else
	TArray<FST_FAQ_DATA> faqData;
	FST_FAQ_DATA tempData1( TEXT( "안녕하세요." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_FAQ_DATA tempData2( TEXT( "Football Boots Manager에 오신것을 환영합니다." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_FAQ_DATA tempData3( TEXT( "Football Boots Manager에 오신것을 환영합니다.2." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_FAQ_DATA tempData4( TEXT( "안녕하세요." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	faqData.Add( tempData1 );
	faqData.Add( tempData2 );
	faqData.Add( tempData3 );
	faqData.Add( tempData4 );
#endif
	for( auto& faqItem : faqData )
	{
		UBWidget_FaqSlot* faqSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_FaqSlot>( EDynamicWidgetParts::FaqSlot );
		if( faqSlotWidget != nullptr )
		{
			faqSlotWidget->OwnerPannel = this;
			faqSlotWidget->SetFaqSlotData( faqItem );
			if( faqSlotWidget->OnClickFaqSlot.IsBoundToObject( this ) == false )
			{
				faqSlotWidget->OnClickFaqSlot.AddUObject( this, &UBWidget_Faq::_OnClickFaqSlotEvent );
			}
			C_ScrollBox_Faq->AddChild( faqSlotWidget );
		}
	}
}

void UBWidget_Faq::PlayFaqSlotOpenAni( const bool isFaqSlotOpen )
{
	if( isFaqSlotOpen )
	{
		if( _Ani_FaqSlotOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_FaqSlotOpen ) )
			{
				StopAnimation( _Ani_FaqSlotOpen );
			}

			PlayAnimation( _Ani_FaqSlotOpen );
		}
	}
	else
	{
		if( _Ani_FaqSlotClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_FaqSlotClose ) )
			{
				StopAnimation( _Ani_FaqSlotClose );
			}

			PlayAnimation( _Ani_FaqSlotClose );
		}
	}
}

bool UBWidget_Faq::_OnBackInput()
{
	if( C_OL_Contents->IsVisible() )
	{
		PlayFaqSlotOpenAni( false );
		return false;
	}

	Super::_OnBackInput();
	CloseUI();

	return true;
}

void UBWidget_Faq::_OnClickFaqSlotEvent( const FST_FAQ_DATA faqSlotData )
{
	C_Txt_Title->SetText( FText::FromString( faqSlotData.FaqTitle ) );
	C_Txt_Contents->SetText( FText::FromString( faqSlotData.FaqContents ) );

	PlayFaqSlotOpenAni( true );
}
