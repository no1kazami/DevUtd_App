#include "BWidget_NoticeSlot.h"

void UBWidget_NoticeSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_NoticeSlot, &UBWidget_NoticeSlot::_OnClick_NoticeSlot );
}

void UBWidget_NoticeSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_NoticeSlot::SetNoticeSlotData( FST_NOTICE_DATA noticeSlotData )
{
	_NoticeData = noticeSlotData;

	C_Txt_Title->SetText( FText::FromString( _NoticeData.NoticeTitle ) );
	C_Txt_Date->SetText( FText::FromString( _NoticeData.NoticeDate ) );
}

void UBWidget_NoticeSlot::_OnClick_NoticeSlot()
{
	OnClickNoticeSlot.Broadcast( _NoticeData );
}
