#include "BWidget_BookMark.h"
#include "GameMode/BGameMode_main.h"
#include "UI/Boots/BWidget_BootsSlot.h"
#include "UI/BWidget_Top.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"

void UBWidget_BookMark::Init()
{
	Super::Init();

	BP_Top_BookMark_UMG->Init();
	BP_Top_BookMark_UMG->ChangeTopMode( E_MODE::E_MODE_BOOKMARK );

	_Ani_BookmarkOpen = GetWidgetAnimation( _Ani_BookmarkOpenName );
	_Ani_BookmarkClose = GetWidgetAnimation( _Ani_BookmarkCloseName );

	InitBookMark();

	GInst->AddBackInput( this );

	PlayBookmarkOpenAni( true );
}

void UBWidget_BookMark::OnClose()
{
	Super::OnClose();
}

void UBWidget_BookMark::OnAnimationFinished_Implementation( const UWidgetAnimation* Animation )
{
	if( Animation != nullptr )
	{
		FName animName = Animation->GetMovieScene()->GetFName();
		if( animName == _Ani_BookmarkCloseName )
		{
			CloseUI();
		}
	}
}

void UBWidget_BookMark::InitBookMark()
{
	C_ScrollBox_BookMark->ClearChildren();
	C_ScrollBox_BookMark->ScrollToStart();

	TArray<int32> bookMarkList = UFBM_SaveGame::Get().GetBookMarkBoots();
	for( int32 slotIndex = 0; slotIndex < bookMarkList.Num(); ++slotIndex )
	{
		UBWidget_BootsSlot* bootsSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_BootsSlot>( EDynamicWidgetParts::BootsSlot );
		if( bootsSlotWidget != nullptr )
		{
			bootsSlotWidget->OwnerPannel = this;
#if DB_BOOTS_DATA
			bootsSlotWidget->SetBootSlotData_DB( slotIndex, bookMarkList[slotIndex] );
#else
			bootsSlotWidget->SetBootSlotData( slotIndex, bookMarkList[slotIndex] );
#endif
			C_ScrollBox_BookMark->AddChild( bootsSlotWidget );
		}
	}

	C_Txt_NoBookMark->SetVisibility( bookMarkList.Num() == 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
}

void UBWidget_BookMark::HandleBackInput()
{
	InitBookMark();
}

void UBWidget_BookMark::PlayBookmarkOpenAni( const bool isBookmarkOpen )
{
	if( isBookmarkOpen )
	{
		if( _Ani_BookmarkOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_BookmarkOpen ) )
			{
				StopAnimation( _Ani_BookmarkOpen );
			}

			PlayAnimation( _Ani_BookmarkOpen );
		}
	}
	else
	{
		if( _Ani_BookmarkClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_BookmarkClose ) )
			{
				StopAnimation( _Ani_BookmarkClose );
			}

			PlayAnimation( _Ani_BookmarkClose );
		}
	}
}

bool UBWidget_BookMark::_OnBackInput()
{
	Super::_OnBackInput();

	PlayBookmarkOpenAni( false );

	return true;
}
