// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Messaging/FirebaseMessaging.h"
#include "Messaging/MessagingInitialize.h"
#include "Messaging/MessagingSubscribe.h"
#include "Messaging/MessagingUnsubscribe.h"
#include "Messaging/MessagingRequestPermission.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "UltimateMobileKitComponent.h"

FFirebaseMessaging::FFirebaseMessaging()
{	
}

FFirebaseMessaging::~FFirebaseMessaging()
{
}

void FFirebaseMessaging::Init(bool RequestPermission /*= true */, const FOnFirebaseMessagingInitializeCompleteDelegate& Delegate /*= FOnFirebaseMessagingInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseMessagingInitialize(UltimateMobileKit->Get(), Delegate, RequestPermission, this);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseMessaging::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Messaging Shutdown"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	firebase::messaging::Terminate();
#endif
}

const bool FFirebaseMessaging::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseMessaging::SetInitialized(bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Messaging is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Messaging is not initialized"));
	}
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
void FFirebaseMessaging::OnMessage(const firebase::messaging::Message& message)
{
	UUltimateMobileKitComponent::MessageReceivedDelegate.Broadcast(TransformNativeToUnrealMessage(message));
}

void FFirebaseMessaging::OnTokenReceived(const char* token)
{
	UUltimateMobileKitComponent::TokenReceivedDelegate.Broadcast(FString(token));
}
#endif

void FFirebaseMessaging::Subscribe(const FString& Topic, const FOnFirebaseMessagingSubscribeCompleteDelegate& Delegate /*= FOnFirebaseMessagingSubscribeCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseMessagingSubscribe(UltimateMobileKit->Get(), Delegate, Topic);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseMessagingError::None);
}

void FFirebaseMessaging::Unsubscribe(const FString& Topic, const FOnFirebaseMessagingUnsubscribeCompleteDelegate& Delegate /*= FOnFirebaseMessagingUnsubscribeCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseMessagingUnsubscribe(UltimateMobileKit->Get(), Delegate, Topic);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseMessagingError::None);
}

void FFirebaseMessaging::RequestPermission(const FOnFirebaseMessagingRequestPermissionCompleteDelegate& Delegate /*= FOnFirebaseMessagingRequestPermissionCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseMessagingRequestPermission(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseMessagingError::None);
}

void FFirebaseMessaging::Send(const FFirebaseMessage FirebaseMessage) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
	TSharedRef<firebase::messaging::Message, ESPMode::ThreadSafe> NativeMessage = TransformUnrealToNativeMessage(FirebaseMessage);
	firebase::messaging::Send(NativeMessage.Get());

	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Messaging send message. From: %s, to: %s, type: %s"), *FirebaseMessage.From, *FirebaseMessage.To, *FirebaseMessage.MessageType);
#endif
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING
const FFirebaseMessage FFirebaseMessaging::TransformNativeToUnrealMessage(const firebase::messaging::Message& NativeMessage) const
{
	FFirebaseMessage FirebaseMessage;
	if(!NativeMessage.collapse_key.empty())
		FirebaseMessage.CollapseKey = FString(NativeMessage.collapse_key.c_str());

	if(!NativeMessage.error.empty())
		FirebaseMessage.Error = FString(NativeMessage.error.c_str());

	if(!NativeMessage.error_description.empty())
		FirebaseMessage.ErrorDescription = FString(NativeMessage.error_description.c_str());

	if(!NativeMessage.from.empty())
		FirebaseMessage.From = FString(NativeMessage.from.c_str());

	if (!NativeMessage.link.empty())
		FirebaseMessage.Link = FString(NativeMessage.link.c_str());

	if(!NativeMessage.message_id.empty())
		FirebaseMessage.MessageId = FString(NativeMessage.message_id.c_str());

	if(!NativeMessage.message_type.empty())
		FirebaseMessage.MessageType = FString(NativeMessage.message_type.c_str());

	FirebaseMessage.NotificationOpened = NativeMessage.notification_opened;

	if(!NativeMessage.priority.empty())
		FirebaseMessage.Priority = FString(NativeMessage.priority.c_str());

	if(!NativeMessage.raw_data.empty())
		FirebaseMessage.RawData = FString(NativeMessage.raw_data.c_str());

	FirebaseMessage.TimeToLive = NativeMessage.time_to_live;

	if(!NativeMessage.to.empty())
		FirebaseMessage.To = FString(NativeMessage.to.c_str());

	std::map<std::string, std::string> NativeDataMap = NativeMessage.data;
	std::map<std::string, std::string>::iterator NativeDataMapIterator;

	for (NativeDataMapIterator = NativeDataMap.begin(); NativeDataMapIterator != NativeDataMap.end(); NativeDataMapIterator++)
	{
		FirebaseMessage.Data.Add(FString(NativeDataMapIterator->first.c_str()), FString(NativeDataMapIterator->second.c_str()));
	}

	if (NativeMessage.notification != nullptr)
	{
		FFirebaseNotification FirebaseNotification;
		FirebaseNotification.Badge = FString(NativeMessage.notification->badge.c_str());
		FirebaseNotification.Body = FString(NativeMessage.notification->body.c_str());
		FirebaseNotification.BodyLocKey = FString(NativeMessage.notification->body_loc_key.c_str());
		FirebaseNotification.ClickAction = FString(NativeMessage.notification->click_action.c_str());
		FirebaseNotification.Color = FString(NativeMessage.notification->color.c_str());
		FirebaseNotification.Icon = FString(NativeMessage.notification->icon.c_str());
		FirebaseNotification.Sound = FString(NativeMessage.notification->sound.c_str());
		FirebaseNotification.Tag = FString(NativeMessage.notification->tag.c_str());
		FirebaseNotification.Title = FString(NativeMessage.notification->title.c_str());
		FirebaseNotification.TitleLocKey = FString(NativeMessage.notification->title_loc_key.c_str());

		for (auto const& BodyLocArg : NativeMessage.notification->body_loc_args)
		{
			FirebaseNotification.BodyLocArgs.Add(FString(BodyLocArg.c_str()));
		}

		for (auto const& TitleLocArg : NativeMessage.notification->title_loc_args)
		{
			FirebaseNotification.TitleLocArgs.Add(FString(TitleLocArg.c_str()));
		}

		FirebaseMessage.Notification = FirebaseNotification;
	}

	return FirebaseMessage;
}

TSharedRef<firebase::messaging::Message, ESPMode::ThreadSafe> FFirebaseMessaging::TransformUnrealToNativeMessage(const FFirebaseMessage FirebaseMessage) const
{
	TSharedRef<firebase::messaging::Message, ESPMode::ThreadSafe> NativeMessage = MakeShareable(new firebase::messaging::Message());
    
	NativeMessage->notification_opened = FirebaseMessage.NotificationOpened;

	NativeMessage->time_to_live = FirebaseMessage.TimeToLive;

	TSharedPtr<std::string, ESPMode::ThreadSafe> CollapseKeyShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.CollapseKey)));
	if(!FirebaseMessage.CollapseKey.IsEmpty())
		NativeMessage->collapse_key = CollapseKeyShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> ErrorShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.Error)));
	if (!FirebaseMessage.Error.IsEmpty())
		NativeMessage->error = ErrorShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> ErrorDescriptionShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.ErrorDescription)));
	if (!FirebaseMessage.ErrorDescription.IsEmpty())
		NativeMessage->error_description = ErrorDescriptionShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> FromShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.From)));
	if (!FirebaseMessage.From.IsEmpty())
		NativeMessage->from = FromShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> MessageIdShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.MessageId)));
	if (!FirebaseMessage.MessageId.IsEmpty())
		NativeMessage->message_id = MessageIdShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> MessageTypeShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.MessageType)));
	if (!FirebaseMessage.MessageType.IsEmpty())
		NativeMessage->message_type = MessageTypeShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> PriorityShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.Priority)));
	if (!FirebaseMessage.Priority.IsEmpty())
		NativeMessage->priority = PriorityShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> RawDataShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.RawData)));
	if (!FirebaseMessage.RawData.IsEmpty())
		NativeMessage->raw_data = RawDataShared->c_str();

	TSharedPtr<std::string, ESPMode::ThreadSafe> ToShared = MakeShareable(new std::string(TCHAR_TO_UTF8(*FirebaseMessage.To)));
	if (!FirebaseMessage.To.IsEmpty())
		NativeMessage->to = ToShared->c_str();


	TSharedPtr<std::map<std::string, std::string>, ESPMode::ThreadSafe> NativeDataMap = MakeShareable(new std::map<std::string, std::string>());

	for (auto& DataElement : FirebaseMessage.Data)
	{
		FString DataElementValue = *DataElement.Value;
		NativeDataMap->insert(std::pair<std::string, std::string>(TCHAR_TO_UTF8(*DataElement.Key), TCHAR_TO_UTF8(*DataElementValue)));
	}

	NativeMessage->data = *NativeDataMap;
  
    return NativeMessage;
}

const EFirebaseMessagingError FFirebaseMessaging::FirebaseErrorFromNative(const firebase::messaging::Error& NativeError)
{
	switch (NativeError)
	{
		case firebase::messaging::kErrorNone:
			return EFirebaseMessagingError::None;
		case firebase::messaging::kErrorFailedToRegisterForRemoteNotifications:
			return EFirebaseMessagingError::FailedToRegisterForRemoteNotifications;
		case firebase::messaging::kErrorInvalidTopicName:
			return EFirebaseMessagingError::InvalidTopicName;
		case firebase::messaging::kErrorUnknown:
			return EFirebaseMessagingError::Unknown;
	}
}

#endif
