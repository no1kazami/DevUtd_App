// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_Top.h"
#include "UI/BWidget_NewMain.h"
#include "UI/Equip/BWidget_Search.h"
#include "GameMode/BGameMode_main.h"
#include "Bigtamin.h"

void UBWidget_Top::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Menu, &UBWidget_Top::_OnClick_MenuBtn );
	ButtonDelegate_Clicked( this, C_Btn_Back, &UBWidget_Top::_OnClick_BackBtn );
	ButtonDelegate_Clicked( this, C_Btn_MyInfo_Search, &UBWidget_Top::_OnClick_MyInfoSearchBtn );
	ButtonDelegate_Clicked( this, C_Btn_Search, &UBWidget_Top::_OnClick_SearchBtn );
	//C_Img_Search->OnMouseButtonDownEvent.BindUFunction( this, "_OnClick_SearchImg" );

	C_ET_Search->OnTextChanged.RemoveDynamic( this, &UBWidget_Top::_OnTextChangeSearch );
	C_ET_Search->OnTextChanged.AddDynamic( this, &UBWidget_Top::_OnTextChangeSearch );
	C_ET_Search->OnTextCommitted.RemoveDynamic( this, &UBWidget_Top::_OnTextChangeSearchFocus );
	C_ET_Search->OnTextCommitted.AddDynamic( this, &UBWidget_Top::_OnTextChangeSearchFocus );
}

void UBWidget_Top::OnClose()
{
	Super::OnClose();
}

void UBWidget_Top::ChangeTopMode( E_MODE changeMode )
{
	_CurTopMode= changeMode;

	switch( changeMode )
	{
	case E_MODE::E_MODE_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 3 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 0 );
		break;
	case E_MODE::E_MODE_SURVEY:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::Hidden );
		break;
	case E_MODE::E_MODE_SURVEY_RESULT:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 20 ) );
		break;
	case E_MODE::E_MODE_BOOTS_DETAIL:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 22 ) );
		break;
	case E_MODE::E_MODE_BOOTS_COMPARE:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 44 ) );
		break;
	case E_MODE::E_MODE_EQUIP_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 1 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 33 ) );
		C_Txt_TopTitle2->SetText( GET_BTEXT( 33 ) );
		break;
	case E_MODE::E_MODE_BOOKMARK:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 69 ) );
		break;
	case E_MODE::E_MODE_NOTICE:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 27 ) );
		break;
	case E_MODE::E_MODE_FAQ:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 28 ) );
		break;
	case E_MODE::E_MODE_VERSION:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 29 ) );
		break;
	case E_MODE::E_MODE_SEARCH:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 2 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( FText::FromString( "" ) );
		C_ET_Search->SetText( FText::FromString( "" ) );
		break;
	case E_MODE::E_MODE_UPCOMING:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 80 ) );
		break;
	case E_MODE::E_MODE_LOBBY:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 1 );
		break;
	case E_MODE::E_MODE_SET:
		break;
	case E_MODE::E_MODE_RANKING_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 4 ) );
		break;
	case E_MODE::E_MODE_SCHEDULE_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 2 ) );
		break;
	case E_MODE::E_MODE_SCHEDULE_DETAIL:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 60 ) );
		break;
	case E_MODE::E_MODE_RESULT_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 3 ) );
		break;
	case E_MODE::E_MODE_RESULT_DETAIL:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 25 ) );
		break;
	case E_MODE::E_MODE_PLAYER_DETAIL:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 39 ) );
		break;
		case E_MODE::E_MODE_PLAYER_COMPARE:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 44 ) );
		break;
	case E_MODE::E_MODE_PLAYER_MAIN:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 43 ) );
		break;
	case E_MODE::E_MODE_STADIUM_INFO:
		C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
		C_WS_TopBtn->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_WS_TopBtn->SetActiveWidgetIndex( 1 );
		C_Txt_TopTitle1->SetText( GET_BTEXT( 61 ) );
		break;
	default:
		break;
	}
}

void UBWidget_Top::ChangeTopMode_Lobby( E_LOBBY_MODE changeLobbyMode )
{
	switch ( changeLobbyMode )
	{
	case E_LOBBY_MODE::E_LOBBY_MODE_MYINFO:
		{
			C_WidgetSwitcher_Top->SetActiveWidgetIndex( 1 );
			C_Txt_TopTitle2->SetText( GET_BTEXT( 1 ) );
		}
		break;
	case E_LOBBY_MODE::E_LOBBY_MODE_DAILY:
		{
			C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
			C_Txt_TopTitle1->SetText( GET_BTEXT( 31 ) );
		}
		break;
	case E_LOBBY_MODE::E_LOBBY_MODE_SEARCH:
		{
			C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
			C_Txt_TopTitle1->SetText( GET_BTEXT( 32 ) );
		}
		break;
	case E_LOBBY_MODE::E_LOBBY_MODE_NEWS:
		{
			C_WidgetSwitcher_Top->SetActiveWidgetIndex( 0 );
			C_Txt_TopTitle1->SetText( GET_BTEXT( 33 ) );
		}
		break;
	default:
		break;
	}
}

void UBWidget_Top::SetTopSurvey( int32 nCurPage, int32 nTotalPage )
{
	FText txtTitle = FText::Format( GET_BTEXT( 17 ), nCurPage, nTotalPage );
	C_Txt_TopTitle1->SetText( txtTitle );
}

void UBWidget_Top::SetSearchText( FText searchText, bool isEmpty/* = false*/ )
{
	if ( isEmpty )
	{
		C_ET_Search->SetText( FText::FromString( "" ) );
		return;
	}

	if( searchText.IsEmpty() )
	{
		return;
	}

	C_ET_Search->SetText( searchText );

	_OnClick_SearchBtn();
}

void UBWidget_Top::_OnClick_MenuBtn()
{
	UBWidget_NewMain* mainUMG = B_HUD->GetWidgetInViewport<UBWidget_NewMain>( EBUIName::Main );
	if( mainUMG != nullptr )
	{
		mainUMG->PlayCategoryAni( true );
	}
}

void UBWidget_Top::_OnClick_BackBtn()
{
	GInst->BackInput();
}

void UBWidget_Top::_OnClick_MyInfoSearchBtn()
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_SEARCH );
	}
}

void UBWidget_Top::_OnClick_SearchBtn()
{
	if( _CurTopMode == E_MODE::E_MODE_SEARCH )
	{
		FText searchText = C_ET_Search->GetText();
		if (searchText.IsEmpty())
		{
			return;
		}

		UBWidget_Search* searchUMG = B_HUD->GetWidgetInViewport<UBWidget_Search>( EBUIName::Search );
		if( searchUMG != nullptr )
		{
			searchUMG->HandleTopSearch( searchText );
		}
	}
}

void UBWidget_Top::_OnClick_SearchImg()
{
	if( _CurTopMode == E_MODE::E_MODE_SEARCH )
	{
		UBWidget_Search* searchUMG = B_HUD->GetWidgetInViewport<UBWidget_Search>( EBUIName::Search );
		if( searchUMG != nullptr )
		{
			searchUMG->HandleTopSearchImg();
		}
		/*
		C_ET_Search->SetKeyboardFocus();
		C_ET_Search->SetUserFocus( this->GetPlayerController() );
		*/
	}
}

void UBWidget_Top::_OnTextChangeSearch( const FText& InText )
{

}

void UBWidget_Top::_OnTextChangeSearchFocus( const FText& InText, ETextCommit::Type commitMethod )
{
	if( _CurTopMode == E_MODE::E_MODE_SEARCH )
	{
		switch( commitMethod )
		{
		case ETextCommit::OnEnter:
			_OnClick_SearchBtn();
			break;
		case ETextCommit::OnUserMovedFocus:
			break;
		default:
			break;
		}
	}
}
