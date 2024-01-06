// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_StadiumInfoSlot.h"

void UBWidget_StadiumInfoSlot::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_StadiumInfoSlot, &UBWidget_StadiumInfoSlot::_OnClick_StadiumInfoSlot );
}

void UBWidget_StadiumInfoSlot::OnClose()
{
	Super::OnClose();
}

void UBWidget_StadiumInfoSlot::SetStadiumInfoSlotData( FST_STADIUM_INFO_DATA stadiumInfoSlotData )
{
	_StadiumInfoData = stadiumInfoSlotData;

	C_Txt_Title->SetText( FText::FromString( _StadiumInfoData.StadiumName ) );
}

void UBWidget_StadiumInfoSlot::_OnClick_StadiumInfoSlot()
{
	OnClickStadiumInfoSlot.Broadcast( _StadiumInfoData );
}
