#include "BWidget_PlayerDetail.h"
#include "UI/BWidget_Top.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"
#include "UI/Player/BWidget_PlayerChart.h"

void UBWidget_PlayerDetail::Init()
{
	Super::Init();

	OnSuccessDownLoadPlayerDetailImage.BindUFunction( this, "_OnSuccessDownLoadDetailImage" );
	OnFailDownLoadPlayerDetailImage.BindUFunction( this, "_OnFailDownLoadDetailImage" );

	BP_Top_PlayerDetail_UMG->Init();
	BP_Top_PlayerDetail_UMG->ChangeTopMode( E_MODE::E_MODE_PLAYER_DETAIL );

	BP_Player_Option_Slot_UMG->Init();
	BP_Player_Chart_Goal_UMG->Init();
	BP_Player_Chart_Assist_UMG->Init();

	_Ani_DetailOpen = GetWidgetAnimation( _Ani_DetailOpenName );
	_Ani_DetailClose = GetWidgetAnimation( _Ani_DetailCloseName );

	GInst->AddBackInput( this );
	PlayDetailOpenAni( true );
}

void UBWidget_PlayerDetail::OnClose()
{
	Super::OnClose();
}

void UBWidget_PlayerDetail::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
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

void UBWidget_PlayerDetail::PlayDetailOpenAni( const bool isDetailOpen )
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

void UBWidget_PlayerDetail::SetPlayerData( FString playerName )
{
	_PlayerName = playerName;
	FDateTime nowDateTime = FDateTime::Now();
	FString nowYear = FString::FromInt( nowDateTime.GetYear() );

	const FST_PLAYER_DATA* playerData = UFBM_SaveGame::Get().GetPlayerData_DB_ByName( playerName );
	if( playerData )
	{
		C_Txt_PlayerName->SetText( FText::FromString( playerData->PlayerName ) );
		C_Txt_Team->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
		C_Txt_Team->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
		C_Txt_Goal->SetText( FText::AsNumber( playerData->GetGoalNum( nowYear ) ) );
		C_Txt_Assist->SetText( FText::AsNumber( playerData->GetAssistNum( nowYear ) ) );
		C_Txt_TotalPoint->SetText( FText::AsNumber( playerData->GetPointNum( nowYear ) ) );
		C_Txt_Attendance->SetText( FText::AsNumber( playerData->GetGamesNum( nowYear ) ) );
		C_Txt_Mvp->SetText( FText::AsNumber( playerData->MvpNum ) );
		C_Txt_Rank_Goal->SetText( FText::AsNumber( playerData->TopScorerNum ) );
		C_Txt_Rank_Assist->SetText( FText::AsNumber( playerData->TopAssistNum ) );
		C_Txt_Rank_Attendance->SetText( FText::AsNumber( playerData->TopAttendanceNum ) );
		C_Txt_Rank_TotalPoint->SetText( FText::AsNumber( playerData->TopPointNum ) );

		UTexture2DDynamic* playerImg = GInst->GetDownLoadPlayerImage( playerName );
		if( playerImg != nullptr )
		{
			if( C_Img_Player != nullptr )
			{
				C_Img_Player->SetBrushFromTextureDynamic( playerImg, false );
			}
		}
		else
		{
			const FString picturlURL = playerData->PictureURL;
			if( picturlURL.IsEmpty() || picturlURL == TEXT( "nan" ) )
			{
				UTexture2D* texturePlayer = GetTexture( TEXT( "Etc/DefaultPerson_256" ) );
				if( texturePlayer != nullptr )
				{
					C_Img_Player->SetBrushFromTexture( texturePlayer, false );
				}
			}
			else
			{
				DownLoadTexture_URL( picturlURL, OnSuccessDownLoadPlayerDetailImage, OnFailDownLoadPlayerDetailImage );
			}
		}

		_SetChartInfo();
	}
}

bool UBWidget_PlayerDetail::_OnBackInput()
{
	Super::_OnBackInput();
	PlayDetailOpenAni( false );
	return true;
}

void UBWidget_PlayerDetail::_OnSuccessDownLoadPlayerDetailImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _PlayerName, texturl );
		if( C_Img_Player != nullptr )
		{
			C_Img_Player->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerDetail::_OnFailDownLoadPlayerDetailImage( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerDetail::_SetChartInfo()
{
	BP_Player_Chart_Goal_UMG->SetPlayerData( E_SORT_TYPE::E_SORT_TYPE_GOAL, _PlayerName );
	BP_Player_Chart_Goal_UMG->SetChartDay();

	BP_Player_Chart_Assist_UMG->SetPlayerData( E_SORT_TYPE::E_SORT_TYPE_ASSIST, _PlayerName );
	BP_Player_Chart_Assist_UMG->SetChartDay();

	/*
	UBWidget_PlayerChart* playerChartWidget = B_HUD->CreateDynamicWidget<UBWidget_PlayerChart>( EDynamicWidgetParts::PlayerChart );
	if( playerChartWidget != nullptr )
	{
		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr )
		{
			addSpacer->SetSize( FVector2D( 0.f, 50.f ) );
			C_ScrollBox_Detail->AddChild( addSpacer );
		}

		playerChartWidget->OwnerPannel = this;
		playerChartWidget->SetPlayerData( _PlayerName );
		playerChartWidget->SetChartDay();
		C_ScrollBox_Detail->AddChild( playerChartWidget );

		USpacer* addSpacerUnder = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacerUnder != nullptr )
		{
			addSpacerUnder->SetSize( FVector2D( 0.f, 100.f ) );
			C_ScrollBox_Detail->AddChild( addSpacerUnder );
		}
	}
	*/
}
