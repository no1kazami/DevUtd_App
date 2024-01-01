#include "BWidget_Version.h"
#include "UI/BWidget_Top.h"
#include "Bigtamin.h"

void UBWidget_Version::Init()
{
	Super::Init();

	BP_Top_Version_UMG->Init();
	BP_Top_Version_UMG->ChangeTopMode( E_MODE::E_MODE_VERSION );

	InitVersion();

	GInst->AddBackInput( this );
}

void UBWidget_Version::OnClose()
{
	Super::OnClose();
}

void UBWidget_Version::InitVersion()
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

bool UBWidget_Version::_OnBackInput()
{
	Super::_OnBackInput();
	CloseUI();

	return true;
}
