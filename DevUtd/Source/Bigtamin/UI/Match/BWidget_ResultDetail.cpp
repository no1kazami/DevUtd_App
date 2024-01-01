#include "BWidget_ResultDetail.h"
#include "BWidget_MatchItem.h"
#include "BWidget_ResultDetailSlot.h"
#include "Bigtamin.h"

void UBWidget_ResultDetail::Init()
{
	Super::Init();

	BP_Top_MainResultDetail_UMG->Init();
	BP_Top_MainResultDetail_UMG->ChangeTopMode( E_MODE::E_MODE_RESULT_DETAIL );

	BP_MatchItem_UMG->Init();

	_Ani_ResultDetailOpen = GetWidgetAnimation( _Ani_ResultDetailOpenName );
	_Ani_ResultDetailClose = GetWidgetAnimation( _Ani_ResultDetailCloseName );


	GInst->AddBackInput( this );

	PlayResultDetailOpenAni( true );
}

void UBWidget_ResultDetail::OnClose()
{
	Super::OnClose();
}

void UBWidget_ResultDetail::SetData( FST_MATCH_DATA matchData )
{
	BP_MatchItem_UMG->SetMatchItem( matchData );

	C_SB_Item->ClearChildren();
	C_SB_Item->ScrollToStart();

	int32 homePlayerNum = matchData.HomePlayerInfo.Num();
	int32 awayPlayerNum = matchData.AwayPlayerInfo.Num();
	int32 commonNum = FMath::Min(homePlayerNum, awayPlayerNum);
	bool isHomeMoreBig = homePlayerNum > awayPlayerNum;
	for( int32 playerIndex = 0; playerIndex < commonNum; ++playerIndex )
	{
		UBWidget_ResultDetailSlot* resultDetailSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ResultDetailSlot>( EDynamicWidgetParts::ResultDetailSlot );
		if( resultDetailSlotWidget != nullptr )
		{
			int32 homeGoalNum = 0;
			int32 homeAssistNum = 0;
			FString homePlayerName = matchData.HomePlayerInfo[playerIndex];
			for( auto& homeGoalItem : matchData.HomeGoalInfo )
			{
				if ( homePlayerName == homeGoalItem )
				{
					homeGoalNum++;
				}
			}
			for( auto& homeAssistItem : matchData.HomeAssistInfo )
			{
				if( homePlayerName == homeAssistItem )
				{
					homeAssistNum++;
				}
			}

			int32 awayGoalNum = 0;
			int32 awayAssistNum = 0;
			FString awayPlayerName = matchData.AwayPlayerInfo[playerIndex];
			for( auto& awayGoalItem : matchData.AwayGoalInfo )
			{
				if( awayPlayerName == awayGoalItem )
				{
					awayGoalNum++;
				}
			}
			for( auto& awayAssistItem : matchData.AwayAssistInfo )
			{
				if( awayPlayerName == awayAssistItem )
				{
					awayAssistNum++;
				}
			}

			resultDetailSlotWidget->SetData( homePlayerName, homeGoalNum, homeAssistNum, awayPlayerName, awayGoalNum, awayAssistNum );
			C_SB_Item->AddChild( resultDetailSlotWidget );
		}
	}

	int32 lastNum = isHomeMoreBig ? homePlayerNum : awayPlayerNum;
	for( int32 playerIndex2 = commonNum; playerIndex2 < lastNum; ++playerIndex2 )
	{
		UBWidget_ResultDetailSlot* resultDetailSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_ResultDetailSlot>( EDynamicWidgetParts::ResultDetailSlot );
		if( resultDetailSlotWidget != nullptr )
		{
			if ( isHomeMoreBig )
			{
				int32 homeGoalNum = 0;
				int32 homeAssistNum = 0;
				FString homePlayerName = matchData.HomePlayerInfo[playerIndex2];
				for( auto& homeGoalItem : matchData.HomeGoalInfo )
				{
					if( homePlayerName == homeGoalItem )
					{
						homeGoalNum++;
					}
				}
				for( auto& homeAssistItem : matchData.HomeAssistInfo )
				{
					if( homePlayerName == homeAssistItem )
					{
						homeAssistNum++;
					}
				}

				resultDetailSlotWidget->SetData( homePlayerName, homeGoalNum, homeAssistNum, TEXT(""), 0, 0 );
			}
			else
			{
				int32 awayGoalNum = 0;
				int32 awayAssistNum = 0;
				FString awayPlayerName = matchData.AwayPlayerInfo[playerIndex2];
				for( auto& awayGoalItem : matchData.AwayGoalInfo )
				{
					if( awayPlayerName == awayGoalItem )
					{
						awayGoalNum++;
					}
				}
				for( auto& awayAssistItem : matchData.AwayAssistInfo )
				{
					if( awayPlayerName == awayAssistItem )
					{
						awayAssistNum++;
					}
				}

				resultDetailSlotWidget->SetData( TEXT( "" ), 0, 0, awayPlayerName, awayGoalNum, awayAssistNum );
			}
			C_SB_Item->AddChild( resultDetailSlotWidget );
		}
	}
}

void UBWidget_ResultDetail::PlayResultDetailOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_ResultDetailOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultDetailOpen ) )
			{
				StopAnimation( _Ani_ResultDetailOpen );
			}

			PlayAnimation( _Ani_ResultDetailOpen );
		}
	}
	else
	{
		if( _Ani_ResultDetailClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_ResultDetailClose ) )
			{
				StopAnimation( _Ani_ResultDetailClose );
			}

			PlayAnimation( _Ani_ResultDetailClose );
		}
	}
}

bool UBWidget_ResultDetail::_OnBackInput()
{
	Super::_OnBackInput();
	PlayResultDetailOpenAni( false );
	return true;
}
