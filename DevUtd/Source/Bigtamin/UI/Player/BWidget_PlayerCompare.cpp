#include "BWidget_PlayerCompare.h"

void UBWidget_PlayerCompare::Init()
{
	Super::Init();

	BP_Top_PlayerCompare_UMG->Init();
	BP_Top_PlayerCompare_UMG->ChangeTopMode( E_MODE::E_MODE_PLAYER_COMPARE );

	_Ani_CompareOpen = GetWidgetAnimation( _Ani_CompareOpenName );
	_Ani_CompareClose = GetWidgetAnimation( _Ani_CompareCloseName );

	GInst->AddBackInput( this );

	OnSuccessDownLoadCompareImage.BindUFunction( this, "_OnSuccessDownLoadCompareImage" );
	OnFailDownLoadCompareImage.BindUFunction( this, "_OnFailDownLoadCompareImage" );
	OnSuccessDownLoadCompareImage2.BindUFunction( this, "_OnSuccessDownLoadCompareImage2" );
	OnFailDownLoadCompareImage2.BindUFunction( this, "_OnFailDownLoadCompareImage2" );
	OnSuccessDownLoadCompareImage3.BindUFunction( this, "_OnSuccessDownLoadCompareImage3" );
	OnFailDownLoadCompareImage3.BindUFunction( this, "_OnFailDownLoadCompareImage3" );

	_InitPlayerCompare();
	PlayCompareOpenAni( true );
}

void UBWidget_PlayerCompare::OnClose()
{
	Super::OnClose();
}

void UBWidget_PlayerCompare::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
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

void UBWidget_PlayerCompare::PlayCompareOpenAni( const bool isOpen )
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

bool UBWidget_PlayerCompare::_OnBackInput()
{
	Super::_OnBackInput();

	PlayCompareOpenAni( false );

	return true;
}

void UBWidget_PlayerCompare::_InitPlayerCompare()
{
	_ClearPlayerCompareUI();

	_SetPlayerCompareUI();
}

void UBWidget_PlayerCompare::_ClearPlayerCompareUI()
{
	C_Img_Product1->SetBrushFromTexture( nullptr, false );
	C_Img_Product2->SetBrushFromTexture( nullptr, false );
	C_Img_Product3->SetBrushFromTexture( nullptr, false );
	C_Txt_Name1->SetText( FText::FromString( "" ) );
	C_Txt_Name2->SetText( FText::FromString( "" ) );
	C_Txt_Name3->SetText( FText::FromString( "" ) );

	C_Txt_Team1->SetText( FText::FromString( "" ) );
	C_Txt_Team2->SetText( FText::FromString( "" ) );
	C_Txt_Team3->SetText( FText::FromString( "" ) );

	C_Txt_Goal1->SetText( FText::FromString( "" ) );
	C_Txt_Goal2->SetText( FText::FromString( "" ) );
	C_Txt_Goal3->SetText( FText::FromString( "" ) );
	C_Txt_CompareGoal2->SetText( FText::FromString( "" ) );
	C_Txt_CompareGoal3->SetText( FText::FromString( "" ) );
	C_Img_Goal_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Goal_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Assist1->SetText( FText::FromString( "" ) );
	C_Txt_Assist2->SetText( FText::FromString( "" ) );
	C_Txt_Assist3->SetText( FText::FromString( "" ) );
	C_Txt_CompareAssist2->SetText( FText::FromString( "" ) );
	C_Txt_CompareAssist3->SetText( FText::FromString( "" ) );
	C_Img_Assist_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Assist_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_TotalPoint1->SetText( FText::FromString( "" ) );
	C_Txt_TotalPoint2->SetText( FText::FromString( "" ) );
	C_Txt_TotalPoint3->SetText( FText::FromString( "" ) );
	C_Txt_CompareTotalPoint2->SetText( FText::FromString( "" ) );
	C_Txt_CompareTotalPoint3->SetText( FText::FromString( "" ) );
	C_Img_TotalPoint_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_TotalPoint_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Attendance1->SetText( FText::FromString( "" ) );
	C_Txt_Attendance2->SetText( FText::FromString( "" ) );
	C_Txt_Attendance3->SetText( FText::FromString( "" ) );
	C_Txt_CompareAttendance2->SetText( FText::FromString( "" ) );
	C_Txt_CompareAttendance3->SetText( FText::FromString( "" ) );
	C_Img_Attendance_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Attendance_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Mvp1->SetText( FText::FromString( "" ) );
	C_Txt_Mvp2->SetText( FText::FromString( "" ) );
	C_Txt_Mvp3->SetText( FText::FromString( "" ) );
	C_Txt_CompareMvp2->SetText( FText::FromString( "" ) );
	C_Txt_CompareMvp3->SetText( FText::FromString( "" ) );
	C_Img_Mvp_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Mvp_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Rank_Goal1->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Goal2->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Goal3->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankGoal2->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankGoal3->SetText( FText::FromString( "" ) );
	C_Img_Rank_Goal_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Rank_Goal_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Rank_Assist1->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Assist2->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Assist3->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankAssist2->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankAssist3->SetText( FText::FromString( "" ) );
	C_Img_Rank_Assist_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Rank_Assist_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Rank_Attendance1->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Attendance2->SetText( FText::FromString( "" ) );
	C_Txt_Rank_Attendance3->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankAttendance2->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankAttendance3->SetText( FText::FromString( "" ) );
	C_Img_Rank_Attendance_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Rank_Attendance_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	C_Txt_Rank_TotalPoint1->SetText( FText::FromString( "" ) );
	C_Txt_Rank_TotalPoint2->SetText( FText::FromString( "" ) );
	C_Txt_Rank_TotalPoint3->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankTotalPoint2->SetText( FText::FromString( "" ) );
	C_Txt_CompareRankTotalPoint3->SetText( FText::FromString( "" ) );
	C_Img_Rank_TotalPoint_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
	C_Img_Rank_TotalPoint_Arrow3->SetVisibility( ESlateVisibility::Collapsed );

	_ProductID1.Empty();
	_ProductID2.Empty();
	_ProductID3.Empty();
}

void UBWidget_PlayerCompare::_SetPlayerCompareUI()
{
	auto funcPlayerCompareUISet = [this]( int32 slotIndex )
	{
		FDateTime nowDateTime = FDateTime::Now();
		FString nowYear = FString::FromInt( nowDateTime.GetYear() );

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
					if( C_Img_Product1 != nullptr )
					{
						C_Img_Product1->SetBrushFromTextureDynamic( downLoadImg, false );
					}
					break;
				case 2:
					_ProductID2 = playerName;
					if( C_Img_Product2 != nullptr )
					{
						C_Img_Product2->SetBrushFromTextureDynamic( downLoadImg, false );
					}
					break;
				case 3:
					_ProductID3 = playerName;
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
				if( iconURL.IsEmpty() || iconURL == TEXT( "nan" ) )
				{
					UTexture2D* texturePlayer = GetTexture( TEXT( "Etc/DefaultPerson_256" ) );
					if( texturePlayer != nullptr )
					{
						switch( slotIndex )
						{
						case 1:
							_ProductID1 = playerName;
							C_Img_Product1->SetBrushFromTexture( texturePlayer, false );
							break;
						case 2:
							_ProductID2 = playerName;
							C_Img_Product2->SetBrushFromTexture( texturePlayer, false );
							break;
						case 3:
							_ProductID3 = playerName;
							C_Img_Product3->SetBrushFromTexture( texturePlayer, false );
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
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage, OnFailDownLoadCompareImage );
						break;
					case 2:
						_ProductID2 = playerName;
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage2, OnFailDownLoadCompareImage2 );
						break;
					case 3:
						_ProductID3 = playerName;
						DownLoadTexture_URL( iconURL, OnSuccessDownLoadCompareImage3, OnFailDownLoadCompareImage3 );
						break;
					default:
						break;
					}
				}
			}


			UTexture2D* textureUp = GetTexture( TEXT( "Icon/Up" ) );
			UTexture2D* textureDown = GetTexture( TEXT( "Icon/Down" ) );

			int32 goalInterval = 0;
			int32 assistInterval = 0;
			int32 totalPointInterval = 0;
			int32 attendanceInterval = 0;
			int32 mvpInterval = 0;
			int32 rankGoalInterval = 0;
			int32 rankAssistInterval = 0;
			int32 rankTotalPointInterval = 0;
			int32 rankAttendanceInterval = 0;
			if( slotIndex == 1 )
			{
				_GoalValue = playerData->GetGoalNum( nowYear );
				_AssistValue = playerData->GetAssistNum( nowYear );
				_TotalPointValue = playerData->GetPointNum( nowYear );
				_AttendanceValue = playerData->GetGamesNum( nowYear );
				_MvpValue = playerData->MvpNum;
				_RankGoalValue = playerData->TopScorerNum;
				_RankAssistValue = playerData->TopAssistNum;
				_RankTotalPointValue = playerData->TopPointNum;
				_RankAttendanceValue = playerData->TopAttendanceNum;

				C_Txt_Name1->SetText( FText::FromString( playerData->PlayerName ) );
				C_Txt_Team1->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
				C_Txt_Team1->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
				C_Txt_Goal1->SetText( FText::AsNumber( playerData->GetGoalNum( nowYear ) ) );
				C_Txt_Assist1->SetText( FText::AsNumber( playerData->GetAssistNum( nowYear ) ) );
				C_Txt_TotalPoint1->SetText( FText::AsNumber( playerData->GetPointNum( nowYear ) ) );
				C_Txt_Attendance1->SetText( FText::AsNumber( playerData->GetGamesNum( nowYear ) ) );
				C_Txt_Mvp1->SetText( FText::AsNumber( playerData->MvpNum ) );
				C_Txt_Rank_Goal1->SetText( FText::AsNumber( playerData->TopScorerNum ) );
				C_Txt_Rank_Assist1->SetText( FText::AsNumber( playerData->TopAssistNum ) );
				C_Txt_Rank_Attendance1->SetText( FText::AsNumber( playerData->TopAttendanceNum ) );
				C_Txt_Rank_TotalPoint1->SetText( FText::AsNumber( playerData->TopPointNum ) );
			}
			else if( slotIndex == 2 )
			{
				C_Txt_Name2->SetText( FText::FromString( playerData->PlayerName ) );
				C_Txt_Team2->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
				C_Txt_Team2->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
				C_Txt_Goal2->SetText( FText::AsNumber( playerData->GetGoalNum( nowYear ) ) );
				C_Txt_Assist2->SetText( FText::AsNumber( playerData->GetAssistNum( nowYear ) ) );
				C_Txt_TotalPoint2->SetText( FText::AsNumber( playerData->GetPointNum( nowYear ) ) );
				C_Txt_Attendance2->SetText( FText::AsNumber( playerData->GetGamesNum( nowYear ) ) );
				C_Txt_Mvp2->SetText( FText::AsNumber( playerData->MvpNum ) );
				C_Txt_Rank_Goal2->SetText( FText::AsNumber( playerData->TopScorerNum ) );
				C_Txt_Rank_Assist2->SetText( FText::AsNumber( playerData->TopAssistNum ) );
				C_Txt_Rank_Attendance2->SetText( FText::AsNumber( playerData->TopAttendanceNum ) );
				C_Txt_Rank_TotalPoint2->SetText( FText::AsNumber( playerData->TopPointNum ) );

				goalInterval = playerData->GetGoalNum( nowYear ) - _GoalValue;
				C_Txt_CompareGoal2->SetText( FText::AsNumber( goalInterval ) );
				C_Txt_CompareGoal2->SetVisibility( goalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareGoal2->SetColorAndOpacity( (goalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Goal_Arrow2->SetVisibility( goalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Goal_Arrow2->SetColorAndOpacity( (goalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( goalInterval == 0 )
				{
					C_Txt_CompareGoal2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Goal_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				assistInterval = playerData->GetAssistNum( nowYear ) - _AssistValue;
				C_Txt_CompareAssist2->SetText( FText::AsNumber( assistInterval ) );
				C_Txt_CompareAssist2->SetVisibility( assistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareAssist2->SetColorAndOpacity( (assistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Assist_Arrow2->SetVisibility( assistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Assist_Arrow2->SetColorAndOpacity( (assistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( assistInterval == 0 )
				{
					C_Txt_CompareAssist2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Assist_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				totalPointInterval = playerData->GetPointNum( nowYear ) - _TotalPointValue;
				C_Txt_CompareTotalPoint2->SetText( FText::AsNumber( totalPointInterval ) );
				C_Txt_CompareTotalPoint2->SetVisibility( totalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareTotalPoint2->SetColorAndOpacity( (totalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_TotalPoint_Arrow2->SetVisibility( totalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_TotalPoint_Arrow2->SetColorAndOpacity( (totalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( totalPointInterval == 0 )
				{
					C_Txt_CompareTotalPoint2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_TotalPoint_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				attendanceInterval = playerData->GetGamesNum( nowYear ) - _AttendanceValue;
				C_Txt_CompareAttendance2->SetText( FText::AsNumber( attendanceInterval ) );
				C_Txt_CompareAttendance2->SetVisibility( attendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareAttendance2->SetColorAndOpacity( (attendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Attendance_Arrow2->SetVisibility( attendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Attendance_Arrow2->SetColorAndOpacity( (attendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( attendanceInterval == 0 )
				{
					C_Txt_CompareAttendance2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Attendance_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				mvpInterval = playerData->MvpNum - _MvpValue;
				C_Txt_CompareMvp2->SetText( FText::AsNumber( mvpInterval ) );
				C_Txt_CompareMvp2->SetVisibility( mvpInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareMvp2->SetColorAndOpacity( (mvpInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Mvp_Arrow2->SetVisibility( mvpInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Mvp_Arrow2->SetColorAndOpacity( (mvpInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( mvpInterval == 0 )
				{
					C_Txt_CompareMvp2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Mvp_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankGoalInterval = playerData->TopScorerNum - _RankGoalValue;
				C_Txt_CompareRankGoal2->SetText( FText::AsNumber( rankGoalInterval ) );
				C_Txt_CompareRankGoal2->SetVisibility( rankGoalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankGoal2->SetColorAndOpacity( (rankGoalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Goal_Arrow2->SetVisibility( rankGoalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Goal_Arrow2->SetColorAndOpacity( (rankGoalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankGoalInterval == 0 )
				{
					C_Txt_CompareRankGoal2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Goal_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankAssistInterval = playerData->TopAssistNum - _RankAssistValue;
				C_Txt_CompareRankAssist2->SetText( FText::AsNumber( rankAssistInterval ) );
				C_Txt_CompareRankAssist2->SetVisibility( rankAssistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankAssist2->SetColorAndOpacity( (rankAssistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Assist_Arrow2->SetVisibility( rankAssistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Assist_Arrow2->SetColorAndOpacity( (rankAssistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankAssistInterval == 0 )
				{
					C_Txt_CompareRankAssist2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Assist_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankTotalPointInterval = playerData->TopPointNum - _RankTotalPointValue;
				C_Txt_CompareRankTotalPoint2->SetText( FText::AsNumber( rankTotalPointInterval ) );
				C_Txt_CompareRankTotalPoint2->SetVisibility( rankTotalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankTotalPoint2->SetColorAndOpacity( (rankTotalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_TotalPoint_Arrow2->SetVisibility( rankTotalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_TotalPoint_Arrow2->SetColorAndOpacity( (rankTotalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankTotalPointInterval == 0 )
				{
					C_Txt_CompareRankTotalPoint2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_TotalPoint_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankAttendanceInterval = playerData->TopAttendanceNum - _RankAttendanceValue;
				C_Txt_CompareRankAttendance2->SetText( FText::AsNumber( rankAttendanceInterval ) );
				C_Txt_CompareRankAttendance2->SetVisibility( rankAttendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankAttendance2->SetColorAndOpacity( (rankAttendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Attendance_Arrow2->SetVisibility( rankAttendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Attendance_Arrow2->SetColorAndOpacity( (rankAttendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankAttendanceInterval == 0 )
				{
					C_Txt_CompareRankAttendance2->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Attendance_Arrow2->SetVisibility( ESlateVisibility::Collapsed );
				}

				if( textureUp != nullptr && textureDown != nullptr )
				{
					C_Img_Goal_Arrow2->SetBrushFromTexture( goalInterval < 0 ? textureDown : textureUp, false );
					C_Img_Assist_Arrow2->SetBrushFromTexture( assistInterval < 0 ? textureDown : textureUp, false );
					C_Img_TotalPoint_Arrow2->SetBrushFromTexture( totalPointInterval < 0 ? textureDown : textureUp, false );
					C_Img_Attendance_Arrow2->SetBrushFromTexture( attendanceInterval < 0 ? textureDown : textureUp, false );
					C_Img_Mvp_Arrow2->SetBrushFromTexture( mvpInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Goal_Arrow2->SetBrushFromTexture( rankGoalInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Assist_Arrow2->SetBrushFromTexture( rankAssistInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_TotalPoint_Arrow2->SetBrushFromTexture( rankTotalPointInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Attendance_Arrow2->SetBrushFromTexture( rankAttendanceInterval < 0 ? textureDown : textureUp, false );
				}
			}
			else if( slotIndex == 3 )
			{
				C_Txt_Name3->SetText( FText::FromString( playerData->PlayerName ) );
				C_Txt_Team3->SetText( GET_BTEXT( UFBM_SaveGame::Get().GetDevUtdTeamStrIndex( playerData->TeamName ) ) );
				C_Txt_Team3->SetColorAndOpacity( UFBM_SaveGame::Get().GetDevUtdTeamColor( playerData->TeamName ) );
				C_Txt_Goal3->SetText( FText::AsNumber( playerData->GetGoalNum( nowYear ) ) );
				C_Txt_Assist3->SetText( FText::AsNumber( playerData->GetAssistNum( nowYear ) ) );
				C_Txt_TotalPoint3->SetText( FText::AsNumber( playerData->GetPointNum( nowYear ) ) );
				C_Txt_Attendance3->SetText( FText::AsNumber( playerData->GetGamesNum( nowYear ) ) );
				C_Txt_Mvp3->SetText( FText::AsNumber( playerData->MvpNum ) );
				C_Txt_Rank_Goal3->SetText( FText::AsNumber( playerData->TopScorerNum ) );
				C_Txt_Rank_Assist3->SetText( FText::AsNumber( playerData->TopAssistNum ) );
				C_Txt_Rank_Attendance3->SetText( FText::AsNumber( playerData->TopAttendanceNum ) );
				C_Txt_Rank_TotalPoint3->SetText( FText::AsNumber( playerData->TopPointNum ) );

				goalInterval = playerData->GetGoalNum( nowYear ) - _GoalValue;
				C_Txt_CompareGoal3->SetText( FText::AsNumber( goalInterval ) );
				C_Txt_CompareGoal3->SetVisibility( goalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareGoal3->SetColorAndOpacity( (goalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Goal_Arrow3->SetVisibility( goalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Goal_Arrow3->SetColorAndOpacity( (goalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( goalInterval == 0 )
				{
					C_Txt_CompareGoal3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Goal_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				assistInterval = playerData->GetAssistNum( nowYear ) - _AssistValue;
				C_Txt_CompareAssist3->SetText( FText::AsNumber( assistInterval ) );
				C_Txt_CompareAssist3->SetVisibility( assistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareAssist3->SetColorAndOpacity( (assistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Assist_Arrow3->SetVisibility( assistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Assist_Arrow3->SetColorAndOpacity( (assistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( assistInterval == 0 )
				{
					C_Txt_CompareAssist3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Assist_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				totalPointInterval = playerData->GetPointNum( nowYear ) - _TotalPointValue;
				C_Txt_CompareTotalPoint3->SetText( FText::AsNumber( totalPointInterval ) );
				C_Txt_CompareTotalPoint3->SetVisibility( totalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareTotalPoint3->SetColorAndOpacity( (totalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_TotalPoint_Arrow3->SetVisibility( totalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_TotalPoint_Arrow3->SetColorAndOpacity( (totalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( totalPointInterval == 0 )
				{
					C_Txt_CompareTotalPoint3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_TotalPoint_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				attendanceInterval = playerData->GetGamesNum( nowYear ) - _AttendanceValue;
				C_Txt_CompareAttendance3->SetText( FText::AsNumber( attendanceInterval ) );
				C_Txt_CompareAttendance3->SetVisibility( attendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareAttendance3->SetColorAndOpacity( (attendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Attendance_Arrow3->SetVisibility( attendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Attendance_Arrow3->SetColorAndOpacity( (attendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( attendanceInterval == 0 )
				{
					C_Txt_CompareAttendance3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Attendance_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				mvpInterval = playerData->MvpNum - _MvpValue;
				C_Txt_CompareMvp3->SetText( FText::AsNumber( mvpInterval ) );
				C_Txt_CompareMvp3->SetVisibility( mvpInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareMvp3->SetColorAndOpacity( (mvpInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Mvp_Arrow3->SetVisibility( mvpInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Mvp_Arrow3->SetColorAndOpacity( (mvpInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( mvpInterval == 0 )
				{
					C_Txt_CompareMvp3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Mvp_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankGoalInterval = playerData->TopScorerNum - _RankGoalValue;
				C_Txt_CompareRankGoal3->SetText( FText::AsNumber( rankGoalInterval ) );
				C_Txt_CompareRankGoal3->SetVisibility( rankGoalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankGoal3->SetColorAndOpacity( (rankGoalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Goal_Arrow3->SetVisibility( rankGoalInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Goal_Arrow3->SetColorAndOpacity( (rankGoalInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankGoalInterval == 0 )
				{
					C_Txt_CompareRankGoal3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Goal_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankAssistInterval = playerData->TopAssistNum - _RankAssistValue;
				C_Txt_CompareRankAssist3->SetText( FText::AsNumber( rankAssistInterval ) );
				C_Txt_CompareRankAssist3->SetVisibility( rankAssistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankAssist3->SetColorAndOpacity( (rankAssistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Assist_Arrow3->SetVisibility( rankAssistInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Assist_Arrow3->SetColorAndOpacity( (rankAssistInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankAssistInterval == 0 )
				{
					C_Txt_CompareRankAssist3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Assist_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankTotalPointInterval = playerData->TopPointNum - _RankTotalPointValue;
				C_Txt_CompareRankTotalPoint3->SetText( FText::AsNumber( rankTotalPointInterval ) );
				C_Txt_CompareRankTotalPoint3->SetVisibility( rankTotalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankTotalPoint3->SetColorAndOpacity( (rankTotalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_TotalPoint_Arrow3->SetVisibility( rankTotalPointInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_TotalPoint_Arrow3->SetColorAndOpacity( (rankTotalPointInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankTotalPointInterval == 0 )
				{
					C_Txt_CompareRankTotalPoint3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_TotalPoint_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				rankAttendanceInterval = playerData->TopAttendanceNum - _RankAttendanceValue;
				C_Txt_CompareRankAttendance3->SetText( FText::AsNumber( rankAttendanceInterval ) );
				C_Txt_CompareRankAttendance3->SetVisibility( rankAttendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Txt_CompareRankAttendance3->SetColorAndOpacity( (rankAttendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				C_Img_Rank_Attendance_Arrow3->SetVisibility( rankAttendanceInterval == 0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
				C_Img_Rank_Attendance_Arrow3->SetColorAndOpacity( (rankAttendanceInterval < 0) ? Color_BootsCompare_Blue : Color_BootsCompare_Red );
				if( rankAttendanceInterval == 0 )
				{
					C_Txt_CompareRankAttendance3->SetVisibility( ESlateVisibility::Collapsed );
					C_Img_Rank_Attendance_Arrow3->SetVisibility( ESlateVisibility::Collapsed );
				}

				if( textureUp != nullptr && textureDown != nullptr )
				{
					C_Img_Goal_Arrow3->SetBrushFromTexture( goalInterval < 0 ? textureDown : textureUp, false );
					C_Img_Assist_Arrow3->SetBrushFromTexture( assistInterval < 0 ? textureDown : textureUp, false );
					C_Img_TotalPoint_Arrow3->SetBrushFromTexture( totalPointInterval < 0 ? textureDown : textureUp, false );
					C_Img_Attendance_Arrow3->SetBrushFromTexture( attendanceInterval < 0 ? textureDown : textureUp, false );
					C_Img_Mvp_Arrow3->SetBrushFromTexture( mvpInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Goal_Arrow3->SetBrushFromTexture( rankGoalInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Assist_Arrow3->SetBrushFromTexture( rankAssistInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_TotalPoint_Arrow3->SetBrushFromTexture( rankTotalPointInterval < 0 ? textureDown : textureUp, false );
					C_Img_Rank_Attendance_Arrow3->SetBrushFromTexture( rankAttendanceInterval < 0 ? textureDown : textureUp, false );
				}
			}
		}
	};

	funcPlayerCompareUISet( 1 );
	funcPlayerCompareUISet( 2 );
	funcPlayerCompareUISet( 3 );
}

void UBWidget_PlayerCompare::_OnSuccessDownLoadCompareImage( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _ProductID1, texturl );

		if( C_Img_Product1 != nullptr )
		{
			C_Img_Product1->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerCompare::_OnFailDownLoadCompareImage( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerCompare::_OnSuccessDownLoadCompareImage2( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _ProductID2, texturl );

		if( C_Img_Product2 != nullptr )
		{
			C_Img_Product2->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerCompare::_OnFailDownLoadCompareImage2( UTexture2DDynamic* texturl )
{

}

void UBWidget_PlayerCompare::_OnSuccessDownLoadCompareImage3( UTexture2DDynamic* texturl )
{
	if( texturl != nullptr )
	{
		GInst->SetDownLoadPlayerImage( _ProductID3, texturl );

		if( C_Img_Product3 != nullptr )
		{
			C_Img_Product3->SetBrushFromTextureDynamic( texturl, false );
		}
	}
}

void UBWidget_PlayerCompare::_OnFailDownLoadCompareImage3( UTexture2DDynamic* texturl )
{

}
