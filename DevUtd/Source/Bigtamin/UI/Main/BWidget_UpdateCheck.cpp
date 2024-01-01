// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_UpdateCheck.h"
#include "Bigtamin.h"
#include "Kismet/KismetStringLibrary.h"

void UBWidget_UpdateCheck::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Update, &UBWidget_UpdateCheck::_OnClick_Update );
	ButtonDelegate_Clicked( this, C_Btn_ServerOK, &UBWidget_UpdateCheck::_OnClick_ServerCheckOK );
}

void UBWidget_UpdateCheck::OnClose()
{
	Super::OnClose();
}

void UBWidget_UpdateCheck::InitUpdateCheck( const E_UPDATE_CHECK_TYPE updateCheckType )
{
	_UpdateCheckType = updateCheckType;

	switch( _UpdateCheckType )
	{
	case E_UPDATE_CHECK_TYPE::UPDATE:
		SetUpdate();
		C_WS_Type->SetActiveWidgetIndex( 0 );
		break;
	case E_UPDATE_CHECK_TYPE::SERVER_CHECK:
		SetServerCheck();
		C_WS_Type->SetActiveWidgetIndex( 1 );
		break;
	default:
		break;
	}
}

void UBWidget_UpdateCheck::SetUpdate()
{
#if PLATFORM_ANDROID
	FString curServerVer = UFBM_SaveGame::Get().GetCurVersion();
#else
	FString curServerVer = TEXT( "1.0.0" );
#endif

	FString curClientVersion;
	bool isFound = GConfig->GetString( TEXT( "/Script/AndroidRuntimeSettings.AndroidRuntimeSettings" ), TEXT( "VersionDisplayName" ), curClientVersion, GEngineIni );

	C_Txt_NewVersion->SetText( FText::FromString( curServerVer ) );
	C_Txt_CurVersion->SetText( FText::FromString( curClientVersion ) );
}

void UBWidget_UpdateCheck::SetServerCheck()
{
#if PLATFORM_ANDROID
	FString serverCheckTime = UFBM_SaveGame::Get().GetServetCheckTime();
#else
	FString serverCheckTime = TEXT( "10:00 ~ 12:00" );
#endif

	C_Txt_CheckTime->SetText( FText::FromString( serverCheckTime ) );
}

void UBWidget_UpdateCheck::_OnClick_Update()
{
	FString updateUrl = UFBM_SaveGame::Get().GetReviewURL();
	if( !updateUrl.IsEmpty() )
	{
		UKismetSystemLibrary::LaunchURL( updateUrl );
	}

	UKismetSystemLibrary::QuitGame( this->GetWorld(), this->GetPlayerController(), EQuitPreference::Quit, false );

}

void UBWidget_UpdateCheck::_OnClick_ServerCheckOK()
{
	UKismetSystemLibrary::QuitGame( this->GetWorld(), this->GetPlayerController(), EQuitPreference::Quit, false );
}
