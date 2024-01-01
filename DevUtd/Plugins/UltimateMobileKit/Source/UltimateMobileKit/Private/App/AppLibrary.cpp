// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "App/AppLibrary.h"
#include "UltimateMobileKit.h"

UUltimateMobileKitApp::UUltimateMobileKitApp(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitApp::IsFirebaseInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid())
		{
			return FirebaseApp->IsInitialized();
		}
	}

	return false;
}

const EGooglePlayAvailability UUltimateMobileKitApp::CheckGooglePlayAvailability()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if (FirebaseApp.IsValid())
		{
			return FirebaseApp->CheckGooglePlayAvailability();
		}
	}

	return EGooglePlayAvailability::UnavailableMissing;
}
