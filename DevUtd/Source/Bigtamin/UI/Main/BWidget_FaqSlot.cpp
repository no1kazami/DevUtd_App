// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_FaqSlot.h"

void UBWidget_FaqSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_FaqSlot, &UBWidget_FaqSlot::_OnClick_FaqSlot );
}

void UBWidget_FaqSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_FaqSlot::SetFaqSlotData( FST_FAQ_DATA faqSlotData )
{
	_FaqData = faqSlotData;

	C_Txt_Title->SetText( FText::FromString( _FaqData.FaqTitle ) );
}

void UBWidget_FaqSlot::_OnClick_FaqSlot()
{
	OnClickFaqSlot.Broadcast( _FaqData );
}
