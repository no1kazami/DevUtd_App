#include "BWidget_Notice.h"
#include "UI/BWidget_Top.h"
#include "BWidget_NoticeSlot.h"
#include "../../FBM_SaveGame.h"
#include "Bigtamin.h"

void UBWidget_Notice::Init()
{
	Super::Init();

	BP_Top_Notice_UMG->Init();
	BP_Top_Notice_UMG->ChangeTopMode( E_MODE::E_MODE_NOTICE );

	_Ani_NotiSlotOpen = GetWidgetAnimation( _Ani_NotiSlotOpenName );
	_Ani_NotiSlotClose = GetWidgetAnimation( _Ani_NotiSlotCloseName );

	InitNotice();

	GInst->AddBackInput( this );
}

void UBWidget_Notice::OnClose()
{
	Super::OnClose();
}

void UBWidget_Notice::InitNotice()
{
	C_ScrollBox_Notice->ClearChildren();
	C_ScrollBox_Notice->ScrollToStart();

#if PLATFORM_ANDROID
	const TArray<FST_NOTICE_DATA> noticeData = UFBM_SaveGame::Get().GetNoticeData();
#else
	TArray<FST_NOTICE_DATA> noticeData;
	FST_NOTICE_DATA tempData1( TEXT( "2020-06-06" ), TEXT( "안녕하세요." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_NOTICE_DATA tempData2( TEXT( "2020-06-04" ), TEXT( "Football Boots Manager에 오신것을 환영합니다." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_NOTICE_DATA tempData3( TEXT( "2020-06-07" ), TEXT( "Football Boots Manager에 오신것을 환영합니다.2." ), TEXT( "반갑습니다.\n잘 부탁드립니다." ) );
	FST_NOTICE_DATA tempData4( TEXT( "2019-12-06" ), TEXT( "안녕하세요." ), TEXT( "반갑습니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다.\n잘 부탁드립니다." ) );
	noticeData.Add( tempData1 );
	noticeData.Add( tempData2 );
	noticeData.Add( tempData3 );
	noticeData.Add( tempData4 );

	noticeData.Sort( []( const FST_NOTICE_DATA& A, const FST_NOTICE_DATA& B ) {
							   return A.NoticeDate > B.NoticeDate;
						   } );						   
#endif
	for( auto& noticeItem : noticeData)
	{
		UBWidget_NoticeSlot* noticeSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_NoticeSlot>( EDynamicWidgetParts::NoticeSlot );
		if( noticeSlotWidget != nullptr )
		{
			noticeSlotWidget->OwnerPannel = this;
			noticeSlotWidget->SetNoticeSlotData( noticeItem );
			if( noticeSlotWidget->OnClickNoticeSlot.IsBoundToObject( this ) == false )
			{
				noticeSlotWidget->OnClickNoticeSlot.AddUObject( this, &UBWidget_Notice::_OnClickNoticeSlotEvent );
            }
			C_ScrollBox_Notice->AddChild( noticeSlotWidget );
		}
	}
}

void UBWidget_Notice::PlayNotiSlotOpenAni( const bool isNotiSlotOpen )
{
	if( isNotiSlotOpen )
	{
		if( _Ani_NotiSlotOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_NotiSlotOpen ) )
			{
				StopAnimation( _Ani_NotiSlotOpen );
			}

			PlayAnimation( _Ani_NotiSlotOpen );
		}
	}
	else
	{
		if( _Ani_NotiSlotClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_NotiSlotClose ) )
			{
				StopAnimation( _Ani_NotiSlotClose );
			}

			PlayAnimation( _Ani_NotiSlotClose );
		}
	}
}

bool UBWidget_Notice::_OnBackInput()
{
	if( C_OL_Contents->IsVisible() )
	{
		PlayNotiSlotOpenAni( false );
		return false;
	}

	Super::_OnBackInput();
	CloseUI();

	return true;
}

void UBWidget_Notice::_OnClickNoticeSlotEvent( const FST_NOTICE_DATA noticeSlotData )
{
	C_Txt_Title->SetText( FText::FromString( noticeSlotData.NoticeTitle ) );
	C_Txt_Date->SetText( FText::FromString( noticeSlotData.NoticeDate ) );
	C_Txt_Contents->SetText( FText::FromString( noticeSlotData.NoticeContents ) );

	PlayNotiSlotOpenAni( true );
}
