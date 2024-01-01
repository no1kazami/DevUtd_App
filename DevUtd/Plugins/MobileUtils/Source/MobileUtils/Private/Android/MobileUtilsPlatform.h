// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Interfaces/MobileUtilsInterface.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#include "EngineMinimal.h"
#include "Core.h"

class FMobileUtilsPlatform : public IMobileUtilsInterface
{
public:
	FMobileUtilsPlatform();
	virtual ~FMobileUtilsPlatform();

	virtual bool CheckInternetConnection() override;
	virtual bool CheckGooglePlayServices() override;
	virtual FString GetPersistentUniqueDeviceId() override;
	virtual FString GetDeviceId() override;
	virtual bool ToggleOrientation() override;
	virtual bool SendEmail() override;
	virtual bool ShareApp() override;
	virtual bool NewSendEmail( FString emailAddress ) override;
	virtual bool NewShareApp( FString shareAddres ) override;

	// JNI Methods
	static jmethodID CheckInternetConnectionMethod;
	static jmethodID CheckGooglePlayServicesMethod;
	static jmethodID GetPersistentUniqueDeviceIdMethod;
	static jmethodID GetDeviceIdMethod;
	static jmethodID ToggleOrientationMethod;
	static jmethodID SendEmailMethod;
	static jmethodID ShareAppMethod;
	static jmethodID NewSendEmailMethod;
	static jmethodID NewShareAppMethod;
};
