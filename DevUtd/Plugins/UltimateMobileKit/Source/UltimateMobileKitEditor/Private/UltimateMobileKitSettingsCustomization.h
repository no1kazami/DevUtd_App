// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "IDetailCustomization.h"
#include "Misc/MonitoredProcess.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

class IDetailLayoutBuilder;

/** Custom settings menu for Ultimate Mobile Kit */
class FUltimateMobileKitSettingsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

private:
	FUltimateMobileKitSettingsCustomization();

	void BuildConfigFilesGenerator(IDetailLayoutBuilder& DetailLayout);

	// IOS
	FReply LoadIOSConfigFiles();
	FReply OpenFirebaseIOSConfigFolder();
	FReply UploadDSymsIOS();
	void GenerateIOSConfigFiles();
	void GeneratePlistFramework();

	// Android
	FReply LoadAndroidConfigFiles();
	FReply OpenFirebaseAndroidConfigFolder();
	FReply UploadDSymsAndroid(bool bIsShipping = true);
	FReply UploadDSymsAndroidDevelopment();
	FReply UploadDSymsAndroidShipping();
	void GenerateAndroidConfigFiles();

private:
	IDetailLayoutBuilder* SavedLayoutBuilder;

	const FString BinariesPath;
	const FString AndroidSourceConfigFolderPath;
	const FString AndroidBuildPath;
	const FString AndroidFirebaseBuildPath;
	const FString AndroidIntermediatePath;
	TAttribute<bool> SetupForPlatformAndroidAttribute;

	const FString IOSSourceConfigFolderPath;
	const FString IOSDestinationConfigPath;
	TAttribute<bool> SetupForPlatformIOSAttribute;

	const FString UniversalPath;

	TSharedPtr<FMonitoredProcess> AndroidConfigParseProcess;
	FDelegateHandle AndroidConfigParseTickerHandle;
	bool AndroidConfigParseUpdateStatus(float Delay);
	
	void OnGeneratingPlistCompleted(int32 ReturnCode);
	void OnGeneratingPlistCanceled();
	void OnGeneratingPlistProgress(FString Output);

	bool GeneratingPlistState = false;

	void GeneratingPlistSuccess();
	void GeneratingPlistFailure();

	TSharedPtr<FMonitoredProcess> UploadDsymsAndroidProcess;
	void UploadDsymsAndroidCompleted(int32 ReturnCode, TSharedPtr<SNotificationItem> NotificationItemPtr);
	void UploadDsymsAndroidCanceled(TSharedPtr<SNotificationItem> NotificationItemPtr);
	void HandleUploadDsymsAndroidButtonCancelClicked();
};
