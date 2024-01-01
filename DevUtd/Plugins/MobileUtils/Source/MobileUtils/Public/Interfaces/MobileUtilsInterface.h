// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "Core.h"

class IMobileUtilsInterface
{
public:
	/**
	* Check if internet connection is available on a device
	*
	* @return - true if connection is available
	*/
	virtual bool CheckInternetConnection() = 0;

	/**
	* Check if Google Play Services are available on a device
	*
	* @return - true if Google Play Services are available
	*/
	virtual bool CheckGooglePlayServices() = 0;

	/**
	* Custom ToggleOrientation Func
	*
	* @return - true if PORTRAIT -> LANDSCAPE
	*/
	virtual bool ToggleOrientation() = 0;

	/**
	*  SendEmail Func
	*/
	virtual bool SendEmail() = 0;

	/**
	*  ShareApp Func
	*/
	virtual bool ShareApp() = 0;

	/**
	*  SendEmail Func
	*/
	virtual bool NewSendEmail( FString emailAddress ) = 0;

	/**
	*  ShareApp Func
	*/
	virtual bool NewShareApp( FString shareAddres ) = 0;

	/**
	* Return persistent Unique Device ID without reset after app reinstall
	*
	* @return - Unique Device ID
	*/
	virtual FString GetPersistentUniqueDeviceId();

	/**
	* Return Device ID. Should be unique but not guaranteed.
	*
	* @return - Device ID
	*/
	virtual FString GetDeviceId();
};
