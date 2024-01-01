// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "UltimateMobileKitComponent.h"
#include "UltimateMobileKit.h"

void UUltimateMobileKitComponent::OnRegister()
{
	Super::OnRegister();

	UUltimateMobileKitComponent::UserSignedInDelegate.AddUObject(this, &UUltimateMobileKitComponent::UserSignedIn_Handler);
	UUltimateMobileKitComponent::UserSignedOutDelegate.AddUObject(this, &UUltimateMobileKitComponent::UserSignedOut_Handler);
	UUltimateMobileKitComponent::UserIdTokenChangedDelegate.AddUObject(this, &UUltimateMobileKitComponent::UserSignedIn_Handler);
	UUltimateMobileKitComponent::MessageReceivedDelegate.AddUObject(this, &UUltimateMobileKitComponent::MessageReceived_Handler);
	UUltimateMobileKitComponent::TokenReceivedDelegate.AddUObject(this, &UUltimateMobileKitComponent::TokenReceived_Handler);
}

void UUltimateMobileKitComponent::OnUnregister()
{
	Super::OnUnregister();

	UUltimateMobileKitComponent::UserSignedInDelegate.RemoveAll(this);
	UUltimateMobileKitComponent::UserSignedOutDelegate.RemoveAll(this);
	UUltimateMobileKitComponent::UserIdTokenChangedDelegate.RemoveAll(this);
	UUltimateMobileKitComponent::MessageReceivedDelegate.RemoveAll(this);
	UUltimateMobileKitComponent::TokenReceivedDelegate.RemoveAll(this);
}

void UUltimateMobileKitComponent::UserSignedIn_Handler(const FFirebaseUser& User)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase user signed in. Display name: %s, Email: %s, IsAnonymous: %d, IsEmailVerified: %d, PhotoUrl: %s, Provider: %s, User ID: %s"), *User.DisplayName, *User.Email, User.IsAnonymous, User.IsEmailVerified, *User.PhotoUrl, *UFirebaseCredential::ProviderToString(User.Provider), *User.UserID);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_UserSignedIn"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserSignedIn, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			UserSignedIn.Broadcast(User);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserSignedIn),
		nullptr,
		ENamedThreads::GameThread
	);
}

void UUltimateMobileKitComponent::UserSignedOut_Handler()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase user signed out."));

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_UserSignedOut"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserSignedOut, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			UserSignedOut.Broadcast();
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserSignedOut),
		nullptr,
		ENamedThreads::GameThread
	);
}

void UUltimateMobileKitComponent::UserIdTokenChanged_Handler(const FFirebaseUser& User)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase user ID token changed. Display name: %s, Email: %s, IsAnonymous: %d, IsEmailVerified: %d, PhotoUrl: %s, Provider: %s, User ID: %s"), *User.DisplayName, *User.Email, User.IsAnonymous, User.IsEmailVerified, *User.PhotoUrl, *UFirebaseCredential::ProviderToString(User.Provider), *User.UserID);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_UserIdTokenChanged"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserIdTokenChanged, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			UserIdTokenChanged.Broadcast(User);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UserIdTokenChanged),
		nullptr,
		ENamedThreads::GameThread
	);
}

void UUltimateMobileKitComponent::MessageReceived_Handler(const FFirebaseMessage& Message)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase message received. From: %s, To: %s, Message ID: %s, Message Type: %s"), *Message.From, *Message.To, *Message.MessageId, *Message.MessageType);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_MessageReceived"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_MessageReceived, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			MessageReceived.Broadcast(Message);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_MessageReceived),
		nullptr,
		ENamedThreads::GameThread
	);
}

void UUltimateMobileKitComponent::TokenReceived_Handler(const FString& Token)
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase token received: %s"), *Token);

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_TokenReceived"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_TokenReceived, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			TokenReceived.Broadcast(Token);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_TokenReceived),
		nullptr,
		ENamedThreads::GameThread
	);
}

UUltimateMobileKitComponent::FUltimateMobileKit_UserSignedInDelegate UUltimateMobileKitComponent::UserSignedInDelegate;
UUltimateMobileKitComponent::FUltimateMobileKit_UserSignedOutDelegate UUltimateMobileKitComponent::UserSignedOutDelegate;
UUltimateMobileKitComponent::FUltimateMobileKit_UserIdTokenChangedDelegate UUltimateMobileKitComponent::UserIdTokenChangedDelegate;
UUltimateMobileKitComponent::FUltimateMobileKit_MessageReceivedDelegate UUltimateMobileKitComponent::MessageReceivedDelegate;
UUltimateMobileKitComponent::FUltimateMobileKit_TokenReceivedDelegate UUltimateMobileKitComponent::TokenReceivedDelegate;
