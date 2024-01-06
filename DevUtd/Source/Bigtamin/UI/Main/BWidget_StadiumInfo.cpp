// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_StadiumInfo.h"
#include "UI/BWidget_Top.h"
#include "BWidget_StadiumInfoSlot.h"
#include "Bigtamin.h"
#include "../../FBM_SaveGame.h"
#include "Kismet/KismetSystemLibrary.h"

void UBWidget_StadiumInfo::Init()
{
	Super::Init();

	BP_Top_StadiumInfo_UMG->Init();
	BP_Top_StadiumInfo_UMG->ChangeTopMode( E_MODE::E_MODE_STADIUM_INFO );

	_Ani_StadiumInfoSlotOpen = GetWidgetAnimation( _Ani_StadiumInfoSlotOpenName );
	_Ani_StadiumInfoSlotClose = GetWidgetAnimation( _Ani_StadiumInfoSlotCloseName );

	ButtonDelegate_Clicked( this, C_Btn_TMap, &UBWidget_StadiumInfo::_OnClick_TMap );
	ButtonDelegate_Clicked( this, C_Btn_KakaoNavi, &UBWidget_StadiumInfo::_OnClick_KakaoNavi );
	ButtonDelegate_Clicked( this, C_Btn_NaverMap, &UBWidget_StadiumInfo::_OnClick_NaverMap );

	InitStadiumInfo();

	GInst->AddBackInput( this );
}

void UBWidget_StadiumInfo::OnClose()
{
	Super::OnClose();
}

void UBWidget_StadiumInfo::InitStadiumInfo()
{
	C_ScrollBox_StadiumInfo->ClearChildren();
	C_ScrollBox_StadiumInfo->ScrollToStart();

	const TArray<FST_STADIUM_INFO_DATA> stadiumDataList = UFBM_SaveGame::Get().GetStadiumData_DB();
	for( auto& stadiumData : stadiumDataList )
	{
		UBWidget_StadiumInfoSlot* stadiumInfoSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_StadiumInfoSlot>( EDynamicWidgetParts::StadiumInfoSlot );
		if( stadiumInfoSlotWidget != nullptr )
		{
			stadiumInfoSlotWidget->OwnerPannel = this;
			stadiumInfoSlotWidget->SetStadiumInfoSlotData( stadiumData );
			if( stadiumInfoSlotWidget->OnClickStadiumInfoSlot.IsBoundToObject( this ) == false )
			{
				stadiumInfoSlotWidget->OnClickStadiumInfoSlot.AddUObject( this, &UBWidget_StadiumInfo::_OnClickStadiumInfoSlotEvent );
			}
			C_ScrollBox_StadiumInfo->AddChild( stadiumInfoSlotWidget );
		}
	}
}

void UBWidget_StadiumInfo::PlayStadiumInfoSlotOpenAni( const bool isStadiumInfoSlotOpen )
{
	if( isStadiumInfoSlotOpen )
	{
		if( _Ani_StadiumInfoSlotOpen != nullptr )
		{
			if( IsAnimationPlaying( _Ani_StadiumInfoSlotOpen ) )
			{
				StopAnimation( _Ani_StadiumInfoSlotOpen );
			}

			PlayAnimation( _Ani_StadiumInfoSlotOpen );
		}
	}
	else
	{
		if( _Ani_StadiumInfoSlotClose != nullptr )
		{
			if( IsAnimationPlaying( _Ani_StadiumInfoSlotClose ) )
			{
				StopAnimation( _Ani_StadiumInfoSlotClose );
			}

			PlayAnimation( _Ani_StadiumInfoSlotClose );
		}
	}
}

bool UBWidget_StadiumInfo::_OnBackInput()
{
	if( C_OL_Contents->IsVisible() )
	{
		PlayStadiumInfoSlotOpenAni( false );
		return false;
	}

	Super::_OnBackInput();
	CloseUI();

	return true;
}

void UBWidget_StadiumInfo::_OnClickStadiumInfoSlotEvent( const FST_STADIUM_INFO_DATA stadiumInfoData )
{
	_StadiumInfoData = stadiumInfoData;

	C_Txt_Title->SetText( FText::FromString( _StadiumInfoData.StadiumName ) );
	C_Txt_Address->SetText( FText::FromString( _StadiumInfoData.Address ) );

	PlayStadiumInfoSlotOpenAni( true );
}

void UBWidget_StadiumInfo::_OnClick_TMap()
{
	if( _StadiumInfoData.NaviURL_TMap.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( _StadiumInfoData.NaviURL_TMap );
	}
}

void UBWidget_StadiumInfo::_OnClick_KakaoNavi()
{
	if( _StadiumInfoData.NaviURL_Kakao.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( _StadiumInfoData.NaviURL_Kakao );
	}
}

void UBWidget_StadiumInfo::_OnClick_NaverMap()
{
	if( _StadiumInfoData.NaviURL_Naver.IsEmpty() == false )
	{
		UKismetSystemLibrary::LaunchURL( _StadiumInfoData.NaviURL_Naver );
	}
}
