// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Invites/InvitesSendInvite.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/invites.h"
#include "firebase/util.h"
#endif

FFirebaseInvitesSendInvite::FFirebaseInvitesSendInvite(FUltimateMobileKit* InSubsystem, const FOnFirebaseInvitesSendInviteCompleteDelegate& InDelegate, const FFirebaseInvite& InInvite)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Invite(InInvite)
{
}

void FFirebaseInvitesSendInvite::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseInvitesSendInvite async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseInvitesPtr FirebaseInvites = UltimateMobileKit->GetFirebaseInvites();

		if(FirebaseInvites.IsValid() && FirebaseInvites->IsInitialized())
		{
			TSharedPtr<firebase::invites::Invite, ESPMode::ThreadSafe> NativeInvite = MakeShareable(new firebase::invites::Invite());

			NativeInvite->android_minimum_version_code = Invite.AndroidMinimumVersionCode;

			TSharedPtr<std::string, ESPMode::ThreadSafe> TitleTextShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.TitleText)));
			if(!Invite.TitleText.IsEmpty())
			{
				NativeInvite->title_text = *TitleTextShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> MessageTextShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.MessageText)));
			if (!Invite.MessageText.IsEmpty())
			{
				NativeInvite->message_text = *MessageTextShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> DescriptionTextShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.DescriptionText)));
			if (!Invite.DescriptionText.IsEmpty())
			{
				NativeInvite->description_text = *DescriptionTextShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> CallToActionTextShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.CallToActionText)));
			if (!Invite.CallToActionText.IsEmpty())
			{
				NativeInvite->call_to_action_text = *CallToActionTextShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> CustomImageUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.CustomImageUrl)));
			if (!Invite.CustomImageUrl.IsEmpty())
			{
				NativeInvite->custom_image_url = *CustomImageUrlShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> EmailContentHtmlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.EmailContentHtml)));
			if (!Invite.EmailContentHtml.IsEmpty())
			{
				NativeInvite->email_content_html = *EmailContentHtmlShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> EmailSubjectTextShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.EmailSubjectText)));
			if (!Invite.EmailSubjectText.IsEmpty())
			{
				NativeInvite->email_subject_text = *EmailSubjectTextShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> DeepLinkUrlShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.DeepLinkUrl)));
			if (!Invite.DeepLinkUrl.IsEmpty())
			{
				NativeInvite->deep_link_url = *DeepLinkUrlShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> AndroidPlatformClientIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.AndroidPlatformClientId)));
			if (!Invite.AndroidPlatformClientId.IsEmpty())
			{
				NativeInvite->android_platform_client_id = *AndroidPlatformClientIdShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> GoogleAnalyticsTrackingIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.GoogleAnalyticsTrackingId)));
			if (!Invite.GoogleAnalyticsTrackingId.IsEmpty())
			{
				NativeInvite->google_analytics_tracking_id = *GoogleAnalyticsTrackingIdShared;
			}

			TSharedPtr<std::string, ESPMode::ThreadSafe> IOSPlatformClientIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*Invite.IOSPlatformClientId)));
			if (!Invite.IOSPlatformClientId.IsEmpty())
			{
				NativeInvite->ios_platform_client_id = *IOSPlatformClientIdShared;
			}


			TSharedPtr<std::map<std::string, std::string>, ESPMode::ThreadSafe> ReferralParametersNative = MakeShareable(new std::map<std::string, std::string>());

			for(auto& Elem : Invite.ReferralParameters)
			{
				if(Elem.Key.Len() > 0 && Elem.Value.Len() > 0)
				{
					ReferralParametersNative->insert(std::make_pair(std::string(TCHAR_TO_UTF8(*Elem.Key)), std::string(TCHAR_TO_UTF8(*Elem.Value))));
				}
			}

			if(ReferralParametersNative->size() > 0)
			{
				NativeInvite->referral_parameters = *ReferralParametersNative;
			}

			FetchFutureResult = firebase::invites::SendInvite(*NativeInvite);

			return;
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseInvitesSendInvite::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	if (FetchFutureResult.status() == firebase::kFutureStatusComplete)
	{
		if (FetchFutureResult.error() == 0)
		{
			const firebase::invites::SendInviteResult* InviteResultTemp = FetchFutureResult.result();

			if (InviteResultTemp != nullptr && InviteResultTemp->invitation_ids.size() > 0)
			{
				bWasSuccessful = true;
				for (int i = 0; i < InviteResultTemp->invitation_ids.size(); i++)
				{
					InviteResult.InvitationIds.Add(FString(InviteResultTemp->invitation_ids[i].c_str()));
				}
			}
			else
			{
				bWasSuccessful = false;
				UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInvitesSendInvite Error: No recipients selected"));
			}
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseInvitesSendInvite Error: %s"), *FString(FetchFutureResult.error_message()));
		}
		bIsComplete = true;
	}

	if (FetchFutureResult.status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
#endif
}

void FFirebaseInvitesSendInvite::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseInvitesSendInvite async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, InviteResult);
}

void FFirebaseInvitesSendInvite::Finalize()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FetchFutureResult.Release();
#endif
}
