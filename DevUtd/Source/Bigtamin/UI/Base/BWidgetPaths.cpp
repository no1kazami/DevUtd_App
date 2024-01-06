// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidgetPaths.h"
#include "Bigtamin.h"

void UBWidgetPaths::Init()
{
	_InitWidgetPath();
	_InitDynamicWidgetPartsPath();
	_InitModalWidgetPath();
}

void UBWidgetPaths::_InitWidgetPath()
{
	WidgetPathMap.Add( EBUIName::Main, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "BP_NewMain_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Survey, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Survey/BP_Survey_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::SurveyResult, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Survey/BP_Survey_Result_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::BootsDetail, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Boots/BP_Boots_Detail_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::EquipMain, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Equip/BP_EquipMain_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::BootsCompare, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Boots/BP_Boots_Compare_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::BookMark, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "MyInfo/BP_BookMark_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Notice, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_Notice_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Version, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_Version_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Search, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Equip/BP_Search_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Upcoming, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Upcoming/BP_Upcoming_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Intro, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Intro/BP_Intro_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Faq, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_FAQ_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Ranking, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Ranking/BP_RankingMain_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Schedule, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_MainSchedule_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::ScheduleDetail, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_MainSchedule_Detail_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::Result, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_MainResult_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::ResultDetail, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_MainResult_Detail_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::PlayerDetail, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Player/BP_Player_Detail_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::PlayerCompare, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Player/BP_Player_Compare_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::PlayerMain, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Player/BP_Player_Main_UMG" ) ) );
	WidgetPathMap.Add( EBUIName::StadiumInfo, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_StadiumInfo_UMG" ) ) );
}

void UBWidgetPaths::_InitDynamicWidgetPartsPath()
{
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemImgBtn, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Survey/BP_SurveyItemImgBtn_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemTwoTextBtn, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Survey/BP_SurveyItemTwoText_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemTwoTextDownBtn, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemTwoTextDown_UMG") ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemManyTextBtn, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemManyText_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemManyTextSlot, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemManyTextSlot_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemDropDown, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemDropDown")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemDropDownSlot, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemDropDownSlot_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemManyImgBtn, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemManyImgBtn_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyItemManyImgBtnSlot, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_SurveyItemManyImgBtnSlot_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::SurveyNextBtn, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Survey/BP_Survey_NextBtn_UMG")));
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::BootsSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Boots/BP_BOOTS_SLOT_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::EquipFilterItem, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Equip/BP_EquipFilterItem_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::Warning, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "BP_Warning_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::CommonItemSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Common/BP_Common_ItemSlot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::EquipBootsFilterItem, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Equip/BP_EquipBootsFilterItem_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::ShopSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Shop/BP_Shop_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::ShopChart, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Shop/BP_Shop_Chart_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::CommonItemSlot2, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Common/BP_Common_ItemSlot2_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::NoticeSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_Notice_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::UpdateCheck, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_UpdateCheck_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::UpcomingSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Upcoming/BP_Upcoming_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::ReviewSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Boots/BP_Review_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::FaqSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_FAQ_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::Loading, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Common/BP_Loading_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::MatchItemSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_MatchItem_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::MainRankingSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Ranking/BP_MainRankingSlot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::RankingSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Ranking/BP_Ranking_Slot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::ResultDetailSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Match/BP_ResultDetailSlot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::PlayerChart, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Player/BP_Player_Chart_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::PlayerSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Player/BP_PlayerSlot_UMG" ) ) );
	DynamicWidgetPathMap.Add( EDynamicWidgetParts::StadiumInfoSlot, UBWidgetPaths::GetWidgetDirectoryPath( TEXT( "Main/BP_StadiumInfo_Slot_UMG" ) ) );
}

void UBWidgetPaths::_InitModalWidgetPath()
{
	/*
	ModalWidgetPathMap.Add(EModalPopupWidget::EquipSellFilter, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Inventory/BP_Widget_SellEquipFilter")));
	ModalWidgetPathMap.Add(EModalPopupWidget::SellPriceModal, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Inventory/BP_Widget_SimpleModal_SellPrice")));

	ModalWidgetPathMap.Add(EModalPopupWidget::ReinforceResult, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Inventory/BP_Widget_ModalPopup_Reinforce_Result")));
	ModalWidgetPathMap.Add(EModalPopupWidget::RemodelResult, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Inventory/BP_Widget_ModalPopup_Remodel_Result")));

	ModalWidgetPathMap.Add(EModalPopupWidget::InviteModal, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Inventory/BP_Widget_PopupInvite")));

	ModalWidgetPathMap.Add(EModalPopupWidget::LicenseModal, UBWidgetPaths::GetWidgetDirectoryPath(TEXT("Frontline/BP_Widget_ModalPopup_License")));

	*/
}




