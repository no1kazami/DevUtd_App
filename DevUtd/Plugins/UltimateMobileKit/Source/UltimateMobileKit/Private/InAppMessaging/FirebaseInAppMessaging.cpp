// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InAppMessaging/FirebaseInAppMessaging.h"
#include "InAppMessaging/InAppMessagingInitialize.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING && PLATFORM_IOS
#import <FirebaseInAppMessaging/FirebaseInAppMessaging.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING && PLATFORM_ANDROID
void AndroidThunkCpp_FirebaseSetAutomaticDataCollectionEnabled(bool Enabled)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseSetAutomaticDataCollectionEnabled", "(Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, Enabled);
	}
}

void AndroidThunkCpp_FirebaseSetMessagesSuppressed(bool Suppressed)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseSetMessagesSuppressed", "(Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, Suppressed);
	}
}

bool AndroidThunkCpp_FirebaseIsAutomaticDataCollectionEnabled()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseIsAutomaticDataCollectionEnabled", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return false;
}

bool AndroidThunkCpp_FirebaseAreMessagesSuppressed()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseAreMessagesSuppressed", "()Z", false);
		return FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return false;
}
#endif

FFirebaseInAppMessaging::FFirebaseInAppMessaging()
{
}

FFirebaseInAppMessaging::~FFirebaseInAppMessaging()
{
}

void FFirebaseInAppMessaging::Init(const FOnFirebaseInAppMessagingInitializeCompleteDelegate& Delegate /*= FOnFirebaseInAppMessagingInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseInAppMessagingInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseInAppMessaging::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase In-App Messaging Shutdown"));
}

const bool FFirebaseInAppMessaging::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseInAppMessaging::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase In-App Messaging is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase In-App Messaging is not initialized"));
	}
}

void FFirebaseInAppMessaging::SetAutomaticDataCollectionEnabled(bool Enabled /*= true*/)
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	if (IsInitialized())
	{
#if PLATFORM_IOS
		[FIRInAppMessaging inAppMessaging].automaticDataCollectionEnabled = Enabled ? YES : NO;
#elif PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseSetAutomaticDataCollectionEnabled(Enabled);
#endif
	}
#endif
}

void FFirebaseInAppMessaging::SetMessagesSuppressed(bool Suppresed /*= true*/)
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	if (IsInitialized())
	{
#if PLATFORM_IOS
		[FIRInAppMessaging inAppMessaging].messageDisplaySuppressed = Suppresed ? YES : NO;
#elif PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseSetMessagesSuppressed(Suppresed);
#endif
	}
#endif
}

bool FFirebaseInAppMessaging::IsAutomaticDataCollectionEnabled()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	if (IsInitialized())
	{
#if PLATFORM_IOS
		return [FIRInAppMessaging inAppMessaging].automaticDataCollectionEnabled;
#elif PLATFORM_ANDROID
		return AndroidThunkCpp_FirebaseIsAutomaticDataCollectionEnabled();
#endif
	}
#endif

	return false;
}

bool FFirebaseInAppMessaging::AreMessagesSuppressed()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING
	if (IsInitialized())
	{
#if PLATFORM_IOS
		return [FIRInAppMessaging inAppMessaging].messageDisplaySuppressed;
#elif PLATFORM_ANDROID
		return AndroidThunkCpp_FirebaseAreMessagesSuppressed();
#endif
	}
#endif

	return false;
}
