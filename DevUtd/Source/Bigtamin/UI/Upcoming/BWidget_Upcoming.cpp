// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_Upcoming.h"
#include "UI/BWidget_Top.h"
#include "BWidget_UpcomingSlot.h"
#include "Bigtamin.h"

void UBWidget_Upcoming::Init()
{
	Super::Init();

	BP_Top_Upcoming_UMG->Init();
	BP_Top_Upcoming_UMG->ChangeTopMode( E_MODE::E_MODE_UPCOMING );

	_Ani_UpcomingOpen = GetWidgetAnimation( _Ani_UpcomingOpenName );
	_Ani_UpcomingClose = GetWidgetAnimation( _Ani_UpcomingCloseName );

	InitUpcoming();

	GInst->AddBackInput( this );

	PlayUpcomingOpenAni( true );
}

void UBWidget_Upcoming::OnClose()
{
	Super::OnClose();
}

void UBWidget_Upcoming::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
 		if( animName == _Ani_UpcomingCloseName )
 		{
 			CloseUI();
 		}
	}
}

void UBWidget_Upcoming::InitUpcoming()
{
	C_SB_UpcommingSlot->ClearChildren();
	C_SB_UpcommingSlot->ScrollToStart();

#if PLATFORM_ANDROID
	const TArray<FST_UPCOMING_DATA> upcomingList = UFBM_SaveGame::Get().GetUpcomingData();
#else
	TArray<FST_UPCOMING_DATA> upcomingList;
	FST_UPCOMING_DATA tempData1( TEXT( "202011" ), TEXT( "X Ghosted Atmospheric Pack" ), TEXT( "https://i.postimg.cc/x8YR3yk3/Upcoming-001.jpg" ), E_BRAND_TYPE::E_BRAND_TYPE_ADIDAS );
	FST_UPCOMING_DATA tempData2( TEXT( "202012" ), TEXT( "Predator Freak" ), TEXT( "https://i.postimg.cc/MH7VG4Z0/Upcoming-002.jpg" ), E_BRAND_TYPE::E_BRAND_TYPE_ADIDAS );
	FST_UPCOMING_DATA tempData3( TEXT( "202012" ), TEXT( "Future Z 1.1 'Game On'" ), TEXT( "https://i.postimg.cc/q7W3x0zX/Upcoming-005.jpg" ), E_BRAND_TYPE::E_BRAND_TYPE_PUMA );
	FST_UPCOMING_DATA tempData4( TEXT( "202101" ), TEXT( "Future Z 'Teaser'" ), TEXT( "https://i.postimg.cc/GhjvwZ5d/Upcoming-006.jpg" ), E_BRAND_TYPE::E_BRAND_TYPE_PUMA );
	upcomingList.Add( tempData1 );
	upcomingList.Add( tempData2 );
	upcomingList.Add( tempData3 );
	upcomingList.Add( tempData4 );
#endif
	for( int32 slotIndex = 0; slotIndex < upcomingList.Num(); ++slotIndex )
	{
		UBWidget_UpcomingSlot* upcomingSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_UpcomingSlot>( EDynamicWidgetParts::UpcomingSlot );
		if( upcomingSlotWidget != nullptr )
		{
			bool isDateHidden = false;
			if ( slotIndex > 0)
			{
				isDateHidden = upcomingList[slotIndex - 1].UpcomingDate.Compare( upcomingList[slotIndex].UpcomingDate ) == 0;
			}
			upcomingSlotWidget->OwnerPannel = this;
			upcomingSlotWidget->SetUpcomingSlotData( upcomingList[slotIndex], isDateHidden );
			C_SB_UpcommingSlot->AddChild( upcomingSlotWidget );
		}
	}
}

void UBWidget_Upcoming::PlayUpcomingOpenAni( const bool isOpen )
{
	if( isOpen )
	{
		if( _Ani_UpcomingOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_UpcomingOpen ) )
			{
				StopAnimation( _Ani_UpcomingOpen );
			}

			PlayAnimation( _Ani_UpcomingOpen );
		}
	}
	else
	{
		if( _Ani_UpcomingClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_UpcomingClose ) )
			{
				StopAnimation( _Ani_UpcomingClose );
			}

			PlayAnimation( _Ani_UpcomingClose );
		}
	}
}

bool UBWidget_Upcoming::_OnBackInput()
{
	Super::_OnBackInput();

	PlayUpcomingOpenAni( false );

	return true;
}
