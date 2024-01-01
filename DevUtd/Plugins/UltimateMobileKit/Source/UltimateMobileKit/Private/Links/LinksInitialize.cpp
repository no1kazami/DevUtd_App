// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Links/LinksInitialize.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
#include "firebase/dynamic_links.h"
#include "firebase/util.h"

#if PLATFORM_IOS
#import <FirebaseDynamicLinks/FIRDynamicLinks.h>
#endif
#endif

FFirebaseLinksInitialize::FFirebaseLinksInitialize(FUltimateMobileKit* InSubsystem, const FOnFirebaseLinksInitializeCompleteDelegate& InDelegate, UFirebaseLinksListener* InListener)
	: FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
	, Listener(InListener)
{
}

void FFirebaseLinksInitialize::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseLinksInitialize async task..."));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid() && FirebaseApp->IsInitialized())
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if (NativeApp.IsValid())
			{
				Initializer.Initialize(NativeApp.Get(), Listener->GetNativeLinksListener().Get(), [](firebase::App* app, void* listener)
				{
					return firebase::dynamic_links::Initialize(*app, reinterpret_cast<firebase::dynamic_links::Listener*>(listener));
				});

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseLinksInitialize::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_LINKSINVITES
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if (LastResult.status() == firebase::kFutureStatusComplete)
	{
		if (LastResult.error() == 0)
		{
			bWasSuccessful = true;

			#if PLATFORM_IOS && !UE_BUILD_SHIPPING
				[FIRDynamicLinks performDiagnosticsWithCompletion : nil];
			#endif
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG(LogUltimateMobileKit, Error, TEXT("FirebaseLinksInitialize Error: %s"), *FString(LastResult.error_message()));
		}
		bIsComplete = true;
	}

	if (Initializer.InitializeLastResult().status() == firebase::kFutureStatusInvalid)
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
	LastResult.Release();
#endif
}

void FFirebaseLinksInitialize::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseLinksInitialize async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful);
}

void FFirebaseLinksInitialize::Finalize()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseLinksPtr FirebaseLinks = UltimateMobileKit->GetFirebaseLinks();

		if (FirebaseLinks.IsValid())
		{
			FirebaseLinks->SetInitialized(bWasSuccessful);
		}
	}
}
