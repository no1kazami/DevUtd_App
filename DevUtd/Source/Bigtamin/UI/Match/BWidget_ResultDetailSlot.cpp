#include "BWidget_ResultDetailSlot.h"

void UBWidget_ResultDetailSlot::Init()
{
	Super::Init();
}

void UBWidget_ResultDetailSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_ResultDetailSlot::SetData( FString strHomeName, int32 homeGoal, int32 homeAssist, FString strAwayName, int32 awayGoal, int32 awayAssist )
{
	C_Txt_Name_Home->SetText( FText::FromString( strHomeName ) );
	C_Txt_Name_Away->SetText( FText::FromString( strAwayName ) );

	if( homeGoal > 0 && homeAssist > 0 )
	{
		C_Txt_Stat_Home->SetText( FText::Format( GET_BTEXT( 26 ), FText::AsNumber( homeGoal ), FText::AsNumber( homeAssist ) ) );
	}
	else if ( homeGoal > 0 )
	{
		C_Txt_Stat_Home->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( homeGoal ) ) );
	}
	else if( homeAssist > 0 )
	{
		C_Txt_Stat_Home->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( homeAssist ) ) );
	}

	if( awayGoal > 0 && awayAssist > 0 )
	{
		C_Txt_Stat_Away->SetText( FText::Format( GET_BTEXT( 26 ), FText::AsNumber( awayGoal ), FText::AsNumber( awayAssist ) ) );
	}
	else if( awayGoal > 0 )
	{
		C_Txt_Stat_Away->SetText( FText::Format( GET_BTEXT( 22 ), FText::AsNumber( awayGoal ) ) );
	}
	else if( awayAssist > 0 )
	{
		C_Txt_Stat_Away->SetText( FText::Format( GET_BTEXT( 23 ), FText::AsNumber( awayAssist ) ) );
	}
}
