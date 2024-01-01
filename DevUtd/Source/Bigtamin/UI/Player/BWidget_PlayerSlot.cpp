#include "BWidget_PlayerSlot.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"
#include "UI/Ranking/BWidget_RankingMain.h"
#include "UI/Player/BWidget_PlayerDetail.h"

#define SHOW_PLAYER_NUM 3

void UBWidget_PlayerSlot::Init()
{
	Super::Init();

	OnSuccessDownLoadPlayerImage1.BindUFunction( this, "_OnSuccessDownLoadPlayerImage1" );
	OnFailDownLoadPlayerImage1.BindUFunction( this, "_OnFailDownLoadPlayerImage1" );
	OnSuccessDownLoadPlayerImage2.BindUFunction( this, "_OnSuccessDownLoadPlayerImage2" );
	OnFailDownLoadPlayerImage2.BindUFunction( this, "_OnFailDownLoadPlayerImage2" );
	OnSuccessDownLoadPlayerImage3.BindUFunction( this, "_OnSuccessDownLoadPlayerImage3" );
	OnFailDownLoadPlayerImage3.BindUFunction( this, "_OnFailDownLoadPlayerImage3" );

	ButtonDelegate_Clicked( this, C_Btn_Player1, &UBWidget_PlayerSlot::_OnClick_PlayerSlot1 );
	ButtonDelegate_Clicked( this, C_Btn_Player2, &UBWidget_PlayerSlot::_OnClick_PlayerSlot2 );
	ButtonDelegate_Clicked( this, C_Btn_Player3, &UBWidget_PlayerSlot::_OnClick_PlayerSlot3 );
}

void UBWidget_PlayerSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_PlayerSlot::SetData( TArray<FString> PlayerNames )
{
	C_VB_Player1->SetVisibility(ESlateVisibility::Hidden);
	C_VB_Player2->SetVisibility( ESlateVisibility::Hidden );
	C_VB_Player3->SetVisibility( ESlateVisibility::Hidden );
	if( PlayerNames.Num() > 0 )
	{
		// Player 1
		C_VB_Player1->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_Txt_Name1->SetText( FText::FromString( PlayerNames[0] ) );
		_PlayerName1 = GetPlayerName( PlayerNames[0] );
		const FST_PLAYER_DATA* playerData1 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( _PlayerName1 );
		if( playerData1 )
		{
			UTexture2DDynamic* playerImg1 = GInst->GetDownLoadPlayerImage( _PlayerName1 );
			if( playerImg1 != nullptr )
			{
				if( C_Img_Person1 != nullptr )
				{
					C_Img_Person1->SetBrushFromTextureDynamic( playerImg1, false );
				}
			}
			else
			{
				const FString picturlURL1 = playerData1->PictureURL;
				if( picturlURL1.IsEmpty() == false )
				{
					DownLoadTexture_URL( picturlURL1, OnSuccessDownLoadPlayerImage1, OnFailDownLoadPlayerImage1 );
				}
			}
		}
	}

	if( PlayerNames.Num() > 1 )
	{
		// Player 2
		C_VB_Player2->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_Txt_Name2->SetText( FText::FromString( PlayerNames[1] ) );
		_PlayerName2 = GetPlayerName( PlayerNames[1] );
		const FST_PLAYER_DATA* playerData2 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( _PlayerName2 );
		if( playerData2 )
		{
			UTexture2DDynamic* playerImg2 = GInst->GetDownLoadPlayerImage( _PlayerName2 );
			if( playerImg2 != nullptr )
			{
				if( C_Img_Person2 != nullptr )
				{
					C_Img_Person2->SetBrushFromTextureDynamic( playerImg2, false );
				}
			}
			else
			{
				const FString picturlURL2 = playerData2->PictureURL;
				if( picturlURL2.IsEmpty() == false )
				{
					DownLoadTexture_URL( picturlURL2, OnSuccessDownLoadPlayerImage2, OnFailDownLoadPlayerImage2 );
				}
			}
		}
	}

	if( PlayerNames.Num() > 2)
	{
		// Player 3
		C_VB_Player3->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
		C_Txt_Name3->SetText( FText::FromString( PlayerNames[2] ) );
		_PlayerName3 = GetPlayerName( PlayerNames[2] );
		const FST_PLAYER_DATA* playerData3 = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( _PlayerName3 );
		if( playerData3 )
		{
			UTexture2DDynamic* playerImg3 = GInst->GetDownLoadPlayerImage( _PlayerName3 );
			if( playerImg3 != nullptr )
			{
				if( C_Img_Person3 != nullptr )
				{
					C_Img_Person3->SetBrushFromTextureDynamic( playerImg3, false );
				}
			}
			else
			{
				const FString picturlURL3 = playerData3->PictureURL;
				if( picturlURL3.IsEmpty() == false )
				{
					DownLoadTexture_URL( picturlURL3, OnSuccessDownLoadPlayerImage3, OnFailDownLoadPlayerImage3 );
				}
			}
		}
	}
}

void UBWidget_PlayerSlot::_OnSuccessDownLoadPlayerImage1( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName1, texturl );
		if( C_Img_Person1 != nullptr )
		{
			C_Img_Person1->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerSlot::_OnFailDownLoadPlayerImage1( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerSlot::_OnSuccessDownLoadPlayerImage2( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName2, texturl );
		if( C_Img_Person2 != nullptr )
		{
			C_Img_Person2->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerSlot::_OnFailDownLoadPlayerImage2( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerSlot::_OnSuccessDownLoadPlayerImage3( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName3, texturl );
		if( C_Img_Person3 != nullptr )
		{
			C_Img_Person3->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerSlot::_OnFailDownLoadPlayerImage3( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerSlot::OpenPlayerDetail( FString playerName )
{
	ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
	if( gameMode != nullptr )
	{
		gameMode->ChangeMode( E_MODE::E_MODE_PLAYER_DETAIL );
		UBWidget_PlayerDetail* playerDetailWidget = B_HUD->GetWidgetInViewport<UBWidget_PlayerDetail>( EBUIName::PlayerDetail );
		if( playerDetailWidget != nullptr )
		{
			GInst->SetCurSelectPlayerName( playerName );
			playerDetailWidget->SetPlayerData( playerName );
		}
	}
}

FString UBWidget_PlayerSlot::GetPlayerName( FString inNamne )
{
	TArray<FString> Array = {};
	inNamne.ParseIntoArray( Array, TEXT( " : " ) );
	if ( Array.Num() == 0)
	{
		return inNamne;
	}
	
	return Array[Array.Num() - 1];
}

void UBWidget_PlayerSlot::_OnClick_PlayerSlot1()
{
	OpenPlayerDetail( _PlayerName1 );
}

void UBWidget_PlayerSlot::_OnClick_PlayerSlot2()
{
	OpenPlayerDetail( _PlayerName2 );
}

void UBWidget_PlayerSlot::_OnClick_PlayerSlot3()
{
	OpenPlayerDetail( _PlayerName3 );
}
