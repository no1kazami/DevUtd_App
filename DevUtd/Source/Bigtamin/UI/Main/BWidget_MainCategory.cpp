// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_MainCategory.h"
#include "UI/BWidget_NewMain.h"
#include "../../Plugins/MobileUtils/Source/MobileUtils/Public/IMobileUtils.h"

void UBWidget_MainCategory::Init( UBWidget* OwnerUI )
{
	Super::Init( OwnerUI );

	ButtonDelegate_Clicked( this, C_Btn_Home, &UBWidget_MainCategory::_OnClick_Home );
	ButtonDelegate_Clicked( this, C_Btn_Schedule, &UBWidget_MainCategory::_OnClick_Schedule );
	ButtonDelegate_Clicked( this, C_Btn_Result, &UBWidget_MainCategory::_OnClick_Result );
	ButtonDelegate_Clicked( this, C_Btn_Ranking, &UBWidget_MainCategory::_OnClick_Ranking );
	ButtonDelegate_Clicked( this, C_Btn_Player, &UBWidget_MainCategory::_OnClick_Player );
	ButtonDelegate_Clicked( this, C_Btn_Noti, &UBWidget_MainCategory::_OnClick_Noti );
	ButtonDelegate_Clicked( this, C_Btn_Idea, &UBWidget_MainCategory::_OnClick_Idea );
	ButtonDelegate_Clicked( this, C_Btn_Rule, &UBWidget_MainCategory::_OnClick_Rule );
	ButtonDelegate_Clicked( this, C_Btn_Share, &UBWidget_MainCategory::_OnClick_Share );
	ButtonDelegate_Clicked( this, C_Btn_Review, &UBWidget_MainCategory::_OnClick_Review );
	ButtonDelegate_Clicked( this, C_Btn_Support, &UBWidget_MainCategory::_OnClick_Support );
	ButtonDelegate_Clicked( this, C_Btn_Partnership, &UBWidget_MainCategory::_OnClick_Partnership );
	ButtonDelegate_Clicked( this, C_Btn_Version, &UBWidget_MainCategory::_OnClick_Version );
	ButtonDelegate_Clicked( this, C_Btn_Cancel, &UBWidget_MainCategory::_OnClick_Cancel );
	ButtonDelegate_Clicked( this, C_Btn_Faq, &UBWidget_MainCategory::_OnClick_Faq );

	FString reviewUrl = UFBM_SaveGame::Get().GetReviewURL();
	C_Btn_Review->SetVisibility( ESlateVisibility::Collapsed );
	//C_Btn_Review->SetVisibility( reviewUrl.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible );
	
	bool isShowPartnership = UFBM_SaveGame::Get().IsShowPartnership();
	C_Btn_Partnership->SetVisibility( isShowPartnership ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );

	bool isShowSupport = UFBM_SaveGame::Get().IsShowSupport();
	C_Btn_Support->SetVisibility( isShowSupport ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );

	bool isSendEmail = !(UFBM_SaveGame::Get().GetSendEmailAddress().IsEmpty());
	C_Btn_Idea->SetVisibility( isSendEmail ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );

	bool isShareApp = !(UFBM_SaveGame::Get().GetShareAppAddress().IsEmpty());
	C_Btn_Share->SetVisibility( isShareApp ? ESlateVisibility::Visible : ESlateVisibility::Collapsed );
}

void UBWidget_MainCategory::OnClose()
{
	Super::OnClose();
}

void UBWidget_MainCategory::_OnClick_Home()
{
	_OnClick_Cancel();
}

void UBWidget_MainCategory::_OnClick_Schedule()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::SCHEDULE );
}

void UBWidget_MainCategory::_OnClick_Result()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::RESULT );
}

void UBWidget_MainCategory::_OnClick_Ranking()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::RANKING );
}

void UBWidget_MainCategory::_OnClick_Player()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::PLAYER );
}

void UBWidget_MainCategory::_OnClick_Noti()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::NOTICE );
}

void UBWidget_MainCategory::_OnClick_Faq()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::FAQ );
}

void UBWidget_MainCategory::_OnClick_Idea()
{
#if PLATFORM_ANDROID
	IMobileUtils::Get().GetPlatformInterface()->NewSendEmail( UFBM_SaveGame::Get().GetSendEmailAddress() );
	//IMobileUtils::Get().GetPlatformInterface()->SendEmail();
#endif
}

void UBWidget_MainCategory::_OnClick_Rule()
{
	FString ruleUrl = UFBM_SaveGame::Get().GetRuleURL();
	if( !ruleUrl.IsEmpty() )
	{
		UKismetSystemLibrary::LaunchURL( ruleUrl );
	}
}

void UBWidget_MainCategory::_OnClick_Share()
{
#if PLATFORM_ANDROID
	IMobileUtils::Get().GetPlatformInterface()->NewShareApp( UFBM_SaveGame::Get().GetShareAppAddress() );
	//IMobileUtils::Get().GetPlatformInterface()->ShareApp();
#endif
}

void UBWidget_MainCategory::_OnClick_Review()
{
	FString reviewUrl = UFBM_SaveGame::Get().GetReviewURL();
	if( !reviewUrl.IsEmpty() )
	{
		UKismetSystemLibrary::LaunchURL( reviewUrl );
	}
}

void UBWidget_MainCategory::_OnClick_Support()
{

}

void UBWidget_MainCategory::_OnClick_Partnership()
{

}

void UBWidget_MainCategory::_OnClick_Version()
{
	OnClickMainCategory.Broadcast( E_MAINCATEGORY_TYPE::VERSION );
}

void UBWidget_MainCategory::_OnClick_Cancel()
{
	if( this->OwnerPannel != nullptr )
	{
		if( UBWidget_NewMain* ownerMain = Cast<UBWidget_NewMain>( this->OwnerPannel ) )
		{
			ownerMain->PlayCategoryAni( false );
		}
	}
}
