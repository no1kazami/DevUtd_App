// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode_Main.h"
#include "Bigtamin.h"
#include "UI/BWidget_NewMain.h"
#include "UI/Survey/BWidget_Survey.h"
#include "UI/Survey/BWidget_SurveyResult.h"
#include "UI/Boots/BWidget_BootsDetail.h"
#include "UI/Equip/BWidget_EquipMain.h"
#include "UI/Equip/BWidget_Search.h"
#include "UI/Boots/BWidget_BootsCompare.h"
#include "UI/MyInfo/BWidget_BookMark.h"
#include "UI/Main/BWidget_Notice.h"
#include "UI/Main/BWidget_Version.h"
#include "UI/Upcoming/BWidget_Upcoming.h"
#include "UI/Intro/BWidget_Intro.h"
#include "UI/Main/BWidget_Faq.h"
#include "UI/Ranking/BWidget_RankingMain.h"
#include "UI/Match/BWidget_MainSchedule.h"
#include "UI/Match/BWidget_MainResult.h"
#include "UI/Match/BWidget_ResultDetail.h"
#include "UI/Player/BWidget_PlayerDetail.h"
#include "UI/Player/BWidget_PlayerCompare.h"
#include "UI/Player/BWidget_PlayerMain.h"

void ABGameMode_Main::InitGame( const FString& MapName, const FString& Options, FString& ErrorMessage )
{
	Super::InitGame( MapName, Options, ErrorMessage );
}

void ABGameMode_Main::StartPlay()
{
	Super::StartPlay();
}

void ABGameMode_Main::BeginPlay()
{
	Super::BeginPlay();

	_IsStart = false;

	ChangeMode( E_MODE::E_MODE_INTRO );
}

void ABGameMode_Main::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	if( B_FIREBASE && B_FIREBASE->IsInitSuccess() && !_IsStart /*&& GInst->IsPermissionSuccess()*/)
	{
//		UFBM_SaveGame::Get().IsTodayFirstLogin( true );
		ChangeMode( E_MODE::E_MODE_MAIN );
		_IsStart = true;
	}

}

void ABGameMode_Main::ChangeMode( E_MODE eChangeMode )
{
	auto mainuiChange = []( E_MODE changeMode ){
		if( B_HUD )
		{
			UBWidget_NewMain* mainUMG = B_HUD->GetWidgetInViewport<UBWidget_NewMain>( EBUIName::Main );
			if( mainUMG == nullptr )
				mainUMG = B_HUD->OpenUI<UBWidget_NewMain>( EBUIName::Main );

			if( mainUMG != nullptr )
				mainUMG->ChangeMode( changeMode );
		}
	};

	//GInst->PlayLoadingUI( false );
	switch (eChangeMode)
	{
	case E_MODE::E_MODE_INTRO:
		B_HUD->OpenUI<UBWidget_Intro>( EBUIName::Intro );
		break;
	case E_MODE::E_MODE_MAIN:
		B_HUD->OpenUI<UBWidget_NewMain>( EBUIName::Main );
		break;
	case E_MODE::E_MODE_SURVEY:
		B_HUD->OpenUI<UBWidget_Survey>( EBUIName::Survey );
		break;
	case E_MODE::E_MODE_SURVEY_RESULT:
		B_HUD->OpenUI<UBWidget_SurveyResult>( EBUIName::SurveyResult );
		break;
	case E_MODE::E_MODE_LOBBY:
		{
			mainuiChange( eChangeMode );
		}
		break;
	case E_MODE::E_MODE_BOOTS_DETAIL:
		B_HUD->OpenUI<UBWidget_BootsDetail>( EBUIName::BootsDetail );
		break;
	case E_MODE::E_MODE_BOOTS_COMPARE:
		B_HUD->OpenUI<UBWidget_BootsCompare>( EBUIName::BootsCompare );
		break;
	case E_MODE::E_MODE_EQUIP_MAIN:
		//GInst->PlayLoadingUI( true );
		B_HUD->OpenUI<UBWidget_EquipMain>( EBUIName::EquipMain );
		break;
	case E_MODE::E_MODE_BOOKMARK:
		B_HUD->OpenUI<UBWidget_BookMark>( EBUIName::BookMark );
		break;
	case E_MODE::E_MODE_NOTICE:
		B_HUD->OpenUI<UBWidget_Notice>( EBUIName::Notice );
		break;
	case E_MODE::E_MODE_FAQ:
		B_HUD->OpenUI<UBWidget_Faq>( EBUIName::Faq );
		break;
	case E_MODE::E_MODE_VERSION:
		B_HUD->OpenUI<UBWidget_Version>( EBUIName::Version );
		break;
	case E_MODE::E_MODE_SEARCH:
		B_HUD->OpenUI<UBWidget_Search>( EBUIName::Search );
		break;
	case E_MODE::E_MODE_UPCOMING:
		B_HUD->OpenUI<UBWidget_Upcoming>( EBUIName::Upcoming );
		break;
	case E_MODE::E_MODE_RANKING_MAIN:
		B_HUD->OpenUI<UBWidget_RankingMain>( EBUIName::Ranking );
		break;
	case E_MODE::E_MODE_SCHEDULE_MAIN:
		B_HUD->OpenUI<UBWidget_MainSchedule>( EBUIName::Schedule );
		break;
	case E_MODE::E_MODE_RESULT_MAIN:
		B_HUD->OpenUI<UBWidget_MainResult>( EBUIName::Result );
		break;
	case E_MODE::E_MODE_RESULT_DETAIL:
		B_HUD->OpenUI<UBWidget_ResultDetail>( EBUIName::ResultDetail );
		break;
	case E_MODE::E_MODE_PLAYER_DETAIL:
		B_HUD->OpenUI<UBWidget_PlayerDetail>( EBUIName::PlayerDetail );
		break;
	case E_MODE::E_MODE_PLAYER_COMPARE:
		B_HUD->OpenUI<UBWidget_PlayerCompare>( EBUIName::PlayerCompare );
		break;
	case E_MODE::E_MODE_PLAYER_MAIN:
		B_HUD->OpenUI<UBWidget_PlayerMain>( EBUIName::PlayerMain );
		break;
	default:
		break;
	}

	GInst->SetCurMode( eChangeMode );
}