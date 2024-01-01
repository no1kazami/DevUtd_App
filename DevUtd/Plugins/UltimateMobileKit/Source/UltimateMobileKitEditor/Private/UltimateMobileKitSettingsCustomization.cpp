// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "UltimateMobileKitSettingsCustomization.h"
#include "UltimateMobileKitEditor.h"
#include "UltimateMobileKitSettings.h"
#include "Runtime/Projects/Public/Interfaces/IPluginManager.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailPropertyRow.h"
#include "DetailCategoryBuilder.h"
#include "SPlatformSetupMessage.h"
#include "SourceControlHelpers.h"
#include "XmlFile.h"
#include "Editor.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"


#define LOCTEXT_NAMESPACE "UltimateMobileKitSettings"

DEFINE_LOG_CATEGORY(LogUltimateMobileKitEditor);

TSharedRef<IDetailCustomization> FUltimateMobileKitSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FUltimateMobileKitSettingsCustomization);
}

FUltimateMobileKitSettingsCustomization::FUltimateMobileKitSettingsCustomization()
	: BinariesPath(FPaths::ProjectDir() + TEXT("Binaries/"))
	, AndroidSourceConfigFolderPath(FPaths::ProjectDir() + TEXT("Config/Firebase/Android/"))
	, AndroidBuildPath(FPaths::ProjectDir() + TEXT("Build/Android/"))
	, AndroidFirebaseBuildPath(FPaths::ProjectDir() + TEXT("Build/Firebase/Android/"))
	, AndroidIntermediatePath(FPaths::ProjectDir() + TEXT("Intermediate/Android/"))
	, IOSSourceConfigFolderPath(FPaths::ProjectDir() + TEXT("Config/Firebase/IOS/"))
	, IOSDestinationConfigPath(FPaths::ProjectDir() + TEXT("Build/IOS/"))
	, UniversalPath(IPluginManager::Get().FindPlugin(TEXT("UltimateMobileKit"))->GetBaseDir() / TEXT("Source/ThirdParty/Universal/firebase_cpp_sdk/"))
{
}

void FUltimateMobileKitSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	SavedLayoutBuilder = &DetailLayout;

	BuildConfigFilesGenerator(DetailLayout);
}

void FUltimateMobileKitSettingsCustomization::BuildConfigFilesGenerator(IDetailLayoutBuilder& DetailLayout)
{
	// Android
	IDetailCategoryBuilder& ConfigFilesCategoryAndroid = DetailLayout.EditCategory(TEXT("Config Files Android"));
	ConfigFilesCategoryAndroid.AddCustomRow(LOCTEXT("FirebaseConfigInfoAndroid", "Firebase Config Info for Android"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.Padding(FMargin(10, 10, 10, 10))
				.FillWidth(1.0f)
				[
					SNew(SRichTextBlock)
					.Text(LOCTEXT("FirebaseConfigAndroidMessage", "<RichTextBlock.TextHighlight>Android configuration</>:\nDownload google-services.json from Firebase dashboard, copy to [PROJECT_FOLDER]/Config/Firebase/Android and click Load Firebase Config"))
					.TextStyle(FEditorStyle::Get(), "MessageLog")
					.DecoratorStyleSet(&FEditorStyle::Get())
					.AutoWrapText(true)
				]
			]
		];

	ConfigFilesCategoryAndroid.AddCustomRow(LOCTEXT("FirebaseAndroidConfigFolderLabel", "Firebase Android Config Folder"), false)
		.NameContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.Padding(FMargin(1, 2, 1, 2))
			.FillWidth(2.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FirebaseAndroidConfigFolderLabel", "Firebase Android Config Folder"))
				.Font(DetailLayout.GetDetailFont())
			]
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenFirebaseConfigFolderButton", "Open Firebase Config Folder"))
				.ToolTipText(LOCTEXT("OpenFirebaseConfigFolderButton_Tooltip", "Opens the folder containing the Firebase config files in Explorer or Finder (it's recommended you check these in to source control to share with your team)"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::OpenFirebaseAndroidConfigFolder)
			]
		];

	ConfigFilesCategoryAndroid.AddCustomRow(LOCTEXT("FirebaseAndroidLoadConfigFiles", "Load Firebase Android Config File"), false)
		.NameContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.Padding(FMargin(1, 2, 1, 2))
			.FillWidth(2.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FirebaseAndroidLoadConfigFilesLabel", "Load Firebase Android Config File"))
				.Font(DetailLayout.GetDetailFont())
			]
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("LoadFirebaseAndroidConfigFilesButton", "Load Firebase Config File"))
				.ToolTipText(LOCTEXT("LoadFirebaseAndroidConfigFilesButton_Tooltip", "Load config file for Android from location [PROJECT_FOLDER]/Config/Firebase/Android/google-services.json"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::LoadAndroidConfigFiles)
			]
		];

	TSharedRef<SPlatformSetupMessage> PlatformSetupMessageAndroid = SNew(SPlatformSetupMessage, AndroidIntermediatePath / TEXT("googleservices.xml"))
		.PlatformName(LOCTEXT("AndroidPlatformName", "Android"))
		.OnSetupClicked(this, &FUltimateMobileKitSettingsCustomization::GenerateAndroidConfigFiles);

	SetupForPlatformAndroidAttribute = PlatformSetupMessageAndroid->GetReadyToGoAttribute();

	ConfigFilesCategoryAndroid.AddCustomRow(LOCTEXT("Warning", "Warning"), false)
		.WholeRowWidget
		[
			PlatformSetupMessageAndroid
		];

	TSharedRef<IPropertyHandle> BundleIdAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseBundleIdAndroid));
	ConfigFilesCategoryAndroid.AddProperty(BundleIdAndroidProperty).IsEnabled(true);

	TSharedRef<IPropertyHandle> AppIDAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseAppIdAndroid));
	ConfigFilesCategoryAndroid.AddProperty(AppIDAndroidProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ClientIdAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseClientIdAndroid));
	ConfigFilesCategoryAndroid.AddProperty(ClientIdAndroidProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ApiKeyAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseApiKeyAndroid));
	ConfigFilesCategoryAndroid.AddProperty(ApiKeyAndroidProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> CloudMessagingSenderIdAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseCloudMessagingSenderIdAndroid));
	ConfigFilesCategoryAndroid.AddProperty(CloudMessagingSenderIdAndroidProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> GoogleCloudStorageBucketNameAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseGoogleCloudStorageBucketNameAndroid));
	ConfigFilesCategoryAndroid.AddProperty(GoogleCloudStorageBucketNameAndroidProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> DatabaseURLAndroidProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseDatabaseURLAndroid));
	ConfigFilesCategoryAndroid.AddProperty(DatabaseURLAndroidProperty).IsEnabled(false);

	// IOS
	IDetailCategoryBuilder& ConfigFilesCategoryIOS = DetailLayout.EditCategory(TEXT("Config Files IOS"));
	ConfigFilesCategoryIOS.AddCustomRow(LOCTEXT("FirebaseConfigInfoIOS", "Firebase Config Info for IOS"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.Padding(FMargin(10, 10, 10, 10))
				.FillWidth(1.0f)
				[
					SNew(SRichTextBlock)
					.Text(LOCTEXT("FirebaseConfigIOSMessage", "<RichTextBlock.TextHighlight>IOS configuration</>:\nDownload GoogleService-Info.plist from Firebase dashboard, copy to [PROJECT_FOLDER]/Config/Firebase/IOS and click Load Firebase Config"))
					.TextStyle(FEditorStyle::Get(), "MessageLog")
					.DecoratorStyleSet(&FEditorStyle::Get())
					.AutoWrapText(true)
				]
			]
		];

	ConfigFilesCategoryIOS.AddCustomRow(LOCTEXT("FirebaseIOSConfigFolderLabel", "Firebase Config Folder"), false)
		.NameContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.Padding(FMargin(1, 2, 1, 2))
			.FillWidth(2.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FirebaseIOSConfigFolderLabel", "Firebase IOS Config Folder"))
				.Font(DetailLayout.GetDetailFont())
			]
		]
	.ValueContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenFirebaseConfigFolderButton", "Open Firebase Config Folder"))
				.ToolTipText(LOCTEXT("OpenFirebaseConfigFolderButton_Tooltip", "Opens the folder containing the Firebase config files in Explorer or Finder (it's recommended you check these in to source control to share with your team)"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::OpenFirebaseIOSConfigFolder)
			]
		];

	ConfigFilesCategoryIOS.AddCustomRow(LOCTEXT("FirebaseIOSLoadConfigFiles", "Load Firebase IOS Config File"), false)
		.NameContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.Padding(FMargin(1, 2, 1, 2))
			.FillWidth(2.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FirebaseIOSLoadConfigFilesLabel", "Load Firebase IOS Config File"))
				.Font(DetailLayout.GetDetailFont())
			]
		]
	.ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("LoadFirebaseIOSConfigFilesButton", "Load Firebase Config File"))
				.ToolTipText(LOCTEXT("LoadFirebaseIOSConfigFilesButton_Tooltip", "Load config file for IOS from location [PROJECT_FOLDER]/Config/Firebase/IOS/GoogleService-Info.plist"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::LoadIOSConfigFiles)
			]
		];

	TSharedRef<SPlatformSetupMessage> PlatformSetupMessageIOS = SNew(SPlatformSetupMessage, IOSDestinationConfigPath / TEXT("GoogleService-Info.plist"))
		.PlatformName(LOCTEXT("IOSPlatformName", "IOS"))
		.OnSetupClicked(this, &FUltimateMobileKitSettingsCustomization::GenerateIOSConfigFiles);

	SetupForPlatformIOSAttribute = PlatformSetupMessageIOS->GetReadyToGoAttribute();

	ConfigFilesCategoryIOS.AddCustomRow(LOCTEXT("Warning", "Warning"), false)
		.WholeRowWidget
		[
			PlatformSetupMessageIOS
		];

	TSharedRef<IPropertyHandle> BundleIdIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseBundleIdIOS));
	ConfigFilesCategoryIOS.AddProperty(BundleIdIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> AppIDIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseAppIdIOS));
	ConfigFilesCategoryIOS.AddProperty(AppIDIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ClientIdIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseClientIdIOS));
	ConfigFilesCategoryIOS.AddProperty(ClientIdIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ReversedClientIdIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseReversedClientIdIOS));
	ConfigFilesCategoryIOS.AddProperty(ReversedClientIdIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ApiKeyIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseApiKeyIOS));
	ConfigFilesCategoryIOS.AddProperty(ApiKeyIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> ProjectIdIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseProjectIdIOS));
	ConfigFilesCategoryIOS.AddProperty(ProjectIdIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> CloudMessagingSenderIdIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseCloudMessagingSenderIdIOS));
	ConfigFilesCategoryIOS.AddProperty(CloudMessagingSenderIdIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> GoogleCloudStorageBucketNameIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseGoogleCloudStorageBucketNameIOS));
	ConfigFilesCategoryIOS.AddProperty(GoogleCloudStorageBucketNameIOSProperty).IsEnabled(false);

	TSharedRef<IPropertyHandle> DatabaseURLIOSProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UUltimateMobileKitSettings, FirebaseDatabaseURLIOS));
	ConfigFilesCategoryIOS.AddProperty(DatabaseURLIOSProperty).IsEnabled(false);

	// Crashlytics
	IDetailCategoryBuilder& CrashlyticsCategory = DetailLayout.EditCategory(TEXT("Firebase Crashlytics"));

	CrashlyticsCategory.AddCustomRow(LOCTEXT("FirebaseIOSUploadDsyms", "Upload dSYMs for iOS"), false)
		.NameContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(FMargin(1, 2, 1, 2))
			.FillWidth(2.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("FirebaseIOSUploadDsymsLabel", "Upload dSYMs for iOS"))
				.Font(DetailLayout.GetDetailFont())
			]
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("FirebaseIOSUploadDsymsButton", "Upload dSYMs for IOS"))
				.ToolTipText(LOCTEXT("FirebaseIOSUploadDsymsButton_Tooltip", "Upload dSYMs symbols for iOS to Crashlytics"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::UploadDSymsIOS)
			]
		];

	CrashlyticsCategory.AddCustomRow(LOCTEXT("FirebaseAndroidUploadDsymsDevelopment", "Upload dSYMs for Android [Development]"), false)
			.NameContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(1, 2, 1, 2))
				.FillWidth(2.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("FirebaseAndroidUploadDsymsDevelopmentLabel", "Upload dSYMs for Android [Development]"))
					.Font(DetailLayout.GetDetailFont())
				]
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("FirebaseAndroidUploadDsymsDevelopmentButton", "Upload dSYMs for Android [Development]"))
					.ToolTipText(LOCTEXT("FirebaseAndroidUploadDsymsDevelopmentButton_Tooltip", "Upload dSYMs symbols for Android to Crashlytics for Development mode"))
					.OnClicked(this, &FUltimateMobileKitSettingsCustomization::UploadDSymsAndroidDevelopment)
				]
			];

	CrashlyticsCategory.AddCustomRow(LOCTEXT("FirebaseAndroidUploadDsymsShipping", "Upload dSYMs for Android [Shipping]"), false)
			.NameContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(1, 2, 1, 2))
				.FillWidth(2.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("FirebaseAndroidUploadDsymsShippingLabel", "Upload dSYMs for Android [Shipping]"))
				.Font(DetailLayout.GetDetailFont())
				]
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("FirebaseAndroidUploadDsymsShippingButton", "Upload dSYMs for Android [Shipping]"))
				.ToolTipText(LOCTEXT("FirebaseAndroidUploadDsymsShippingButton_Tooltip", "Upload dSYMs symbols for Android to Crashlytics for Shipping mode"))
				.OnClicked(this, &FUltimateMobileKitSettingsCustomization::UploadDSymsAndroidShipping)
				]
			];
}

FReply FUltimateMobileKitSettingsCustomization::OpenFirebaseAndroidConfigFolder()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Open Firebase Config Folder for Android"));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.CreateDirectoryTree(*AndroidSourceConfigFolderPath);

	const FString ConfigFolder = FPaths::ConvertRelativePathToFull(FPaths::GetPath(AndroidSourceConfigFolderPath));
	FPlatformProcess::ExploreFolder(*ConfigFolder);

	return FReply::Handled();
}

FReply FUltimateMobileKitSettingsCustomization::UploadDSymsAndroid(bool bIsShipping /*= true*/)
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Upload Android dSYMs to Crashlytics"));

	FString CommandLine = FString("-p ") + FPaths::ConvertRelativePathToFull(AndroidIntermediatePath + FString("APK/gradle/")) + (bIsShipping ? FString(" crashlyticsUploadSymbolsRelease") : FString(" crashlyticsUploadSymbolsDebug"));

	FString ProcessPath = FString();

#if PLATFORM_MAC
	FString CmdExe = TEXT("/bin/sh");
	ProcessPath = FPaths::ConvertRelativePathToFull(AndroidIntermediatePath + FString("APK/gradle/gradlew"));
	FString FullCommandLine = FString::Printf(TEXT("\"%s\" %s"), *ProcessPath, *CommandLine);
#elif PLATFORM_LINUX
	FString CmdExe = TEXT("/bin/bash");
	ProcessPath = FPaths::ConvertRelativePathToFull(AndroidIntermediatePath + FString("APK/gradle/gradlew"));
	FString FullCommandLine = FString::Printf(TEXT("\"%s\" %s"), *ProcessPath, *CommandLine);
#else
	FString CmdExe = FPaths::ConvertRelativePathToFull(AndroidIntermediatePath + FString("APK/gradle/gradlew.bat"));
	ProcessPath = CmdExe;
	FString FullCommandLine = CommandLine;
#endif

	if (FPaths::FileExists(ProcessPath))
	{
		FNotificationInfo Info = FNotificationInfo(LOCTEXT("UploadDsymAndroidErrorGradlew", "Uploading dSYMs for Android..."));
		Info.bUseThrobber = true;
		Info.bFireAndForget = false;
		Info.FadeOutDuration = 0.0f;
		Info.ExpireDuration = 0.0f;
		Info.ButtonDetails.Add(
			FNotificationButtonInfo(
				LOCTEXT("UploadDsymsAndroidCancel", "Cancel"),
				LOCTEXT("UploadDsymsAndroidCancelTooltip", "Cancels uploading of dSYMs for Android to Crashlytics"),
				FSimpleDelegate::CreateRaw(this, &FUltimateMobileKitSettingsCustomization::HandleUploadDsymsAndroidButtonCancelClicked),
				SNotificationItem::CS_Pending
			)
		);

		TSharedPtr<SNotificationItem> NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);

		if (!NotificationItem.IsValid())
		{
			return FReply::Handled();
		}

		NotificationItem->SetCompletionState(SNotificationItem::CS_Pending);

		UploadDsymsAndroidProcess = MakeShareable(new FMonitoredProcess(CmdExe, FullCommandLine, true, false));
		UploadDsymsAndroidProcess->OnCompleted().BindRaw(this, &FUltimateMobileKitSettingsCustomization::UploadDsymsAndroidCompleted, NotificationItem);
		UploadDsymsAndroidProcess->OnCanceled().BindRaw(this, &FUltimateMobileKitSettingsCustomization::UploadDsymsAndroidCanceled, NotificationItem);
		bool bSuccess = UploadDsymsAndroidProcess->Launch();

		if (bSuccess)
		{
			GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));
			return FReply::Handled();
		}
		else
		{
			GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));
			NotificationItem->SetExpireDuration(3.0f);
			NotificationItem->SetFadeOutDuration(0.5f);
			NotificationItem->SetCompletionState(SNotificationItem::CS_Fail);
			NotificationItem->ExpireAndFadeout();
		}
	}

	FNotificationInfo Info(LOCTEXT("UploadDsymAndroidErrorGradlew", "Can't find file gradlew. You must build the game first and then try to upload dSYMs."));
	Info.ExpireDuration = 3.0f;
	FSlateNotificationManager::Get().AddNotification(Info);

	UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't find file gradlew. You must build the game first and then try to upload dSYMs."));

	return FReply::Handled();
}

FReply FUltimateMobileKitSettingsCustomization::UploadDSymsAndroidDevelopment()
{
	return UploadDSymsAndroid(false);
}

FReply FUltimateMobileKitSettingsCustomization::UploadDSymsAndroidShipping()
{
	return UploadDSymsAndroid(true);
}

void FUltimateMobileKitSettingsCustomization::UploadDsymsAndroidCompleted(int32 ReturnCode, TSharedPtr<SNotificationItem> NotificationItemPtr)
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_UploadDsymsAndroidCompleted"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UploadDsymsAndroidCompleted, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
		if (ReturnCode == 0)
		{
			UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("dSYMs for Android uploaded successfully to Crashlytics"));

			GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));
			NotificationItemPtr->SetExpireDuration(3.0f);
			NotificationItemPtr->SetFadeOutDuration(0.5f);
			NotificationItemPtr->SetCompletionState(SNotificationItem::CS_Success);
			NotificationItemPtr->ExpireAndFadeout();

			FNotificationInfo Info(LOCTEXT("UploadDsymAndroidSuccess", "dSYMs for Android uploaded successfully to Crashlytics"));
			Info.ExpireDuration = 3.0f;
			FSlateNotificationManager::Get().AddNotification(Info);
		}
		else
		{
			UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Error during uploading dSYMs for Android to Crashlytics"));

			GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));
			NotificationItemPtr->SetExpireDuration(3.0f);
			NotificationItemPtr->SetFadeOutDuration(0.5f);
			NotificationItemPtr->SetCompletionState(SNotificationItem::CS_Fail);
			NotificationItemPtr->ExpireAndFadeout();

			FNotificationInfo Info(LOCTEXT("UploadDsymAndroidError", "Error during uploading dSYMs for Android to Crashlytics"));
			Info.ExpireDuration = 3.0f;
			FSlateNotificationManager::Get().AddNotification(Info);
		}
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UploadDsymsAndroidCompleted),
		nullptr,
		ENamedThreads::GameThread
	);
}

void FUltimateMobileKitSettingsCustomization::UploadDsymsAndroidCanceled(TSharedPtr<SNotificationItem> NotificationItemPtr)
{
	UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Error during uploading dSYMs for Android to Crashlytics"));

	GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));
	NotificationItemPtr->SetExpireDuration(3.0f);
	NotificationItemPtr->SetFadeOutDuration(0.5f);
	NotificationItemPtr->SetCompletionState(SNotificationItem::CS_Fail);
	NotificationItemPtr->ExpireAndFadeout();

	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_UploadDsymsAndroidCanceled"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UploadDsymsAndroidCanceled, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			FNotificationInfo Info(LOCTEXT("UploadDsymAndroidError", "Error during uploading dSYMs for Android to Crashlytics"));
			Info.ExpireDuration = 3.0f;
			Info.bUseSuccessFailIcons = true;
			FSlateNotificationManager::Get().AddNotification(Info);
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_UploadDsymsAndroidCanceled),
		nullptr,
		ENamedThreads::GameThread
	);
}

void FUltimateMobileKitSettingsCustomization::HandleUploadDsymsAndroidButtonCancelClicked()
{
	if(UploadDsymsAndroidProcess.IsValid())
	{
		UploadDsymsAndroidProcess->Cancel(true);
	}
}

FReply FUltimateMobileKitSettingsCustomization::LoadAndroidConfigFiles()
{
	GenerateAndroidConfigFiles();

	return FReply::Handled();
}

FReply FUltimateMobileKitSettingsCustomization::LoadIOSConfigFiles()
{
	GenerateIOSConfigFiles();

	return FReply::Handled();
}

FReply FUltimateMobileKitSettingsCustomization::OpenFirebaseIOSConfigFolder()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Open Firebase Config Folder for IOS"));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.CreateDirectoryTree(*IOSSourceConfigFolderPath);

	const FString ConfigFolder = FPaths::ConvertRelativePathToFull(FPaths::GetPath(IOSSourceConfigFolderPath));
	FPlatformProcess::ExploreFolder(*ConfigFolder);

	return FReply::Handled();
}

FReply FUltimateMobileKitSettingsCustomization::UploadDSymsIOS()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Upload IOS dSYMs to Crashlytics"));

	UUltimateMobileKitSettings* DefaultSettings = const_cast<UUltimateMobileKitSettings*>(GetDefault<UUltimateMobileKitSettings>());
	if(!DefaultSettings->FirebaseBundleIdIOS.IsEmpty() && !DefaultSettings->FirebaseProjectIdIOS.IsEmpty())
	{
		if (FPaths::FileExists(BinariesPath + FString("IOS/") + FApp::GetProjectName() + FString(".dSYM.zip")) || FPaths::FileExists(BinariesPath + FString("IOS/") + FApp::GetProjectName() + FString("-IOS-Shipping.dSYM.zip")))
		{
			FPlatformProcess::LaunchURL((FString("https://console.firebase.google.com/project/") + DefaultSettings->FirebaseProjectIdIOS + FString("/crashlytics/app/ios:") + DefaultSettings->FirebaseBundleIdIOS + FString("/dsyms")).GetCharArray().GetData(), nullptr, nullptr);
		}
		else
		{
			UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Please generate dSYMs for iOS first."));

			FNotificationInfo Info(LOCTEXT("UploadDsymIOSGenerateDsyms", "Please generate dSYMs for iOS first."));
			Info.ExpireDuration = 3.0f;
			FSlateNotificationManager::Get().AddNotification(Info);
		}
	}
	else
	{
		UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Please load Firebase config file for iOS before uploading dSYMs."));

		FNotificationInfo Info(LOCTEXT("UploadDsymIOSConfigFile", "Please load Firebase config file for iOS before uploading dSYMs."));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}

	return FReply::Handled();
}

void FUltimateMobileKitSettingsCustomization::GenerateAndroidConfigFiles()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Generate Firebase Config Files for Android"));

	FString SourceConfigPath = FPaths::ConvertRelativePathToFull(FPaths::GetPath(AndroidSourceConfigFolderPath)) / TEXT("google-services.json");
	FString DestinationConfigPath = FPaths::ConvertRelativePathToFull(FPaths::GetPath(AndroidIntermediatePath)) / TEXT("googleservices.xml");
	FString DestinationJsonConfigPath = FPaths::ConvertRelativePathToFull(FPaths::GetPath(AndroidBuildPath)) / TEXT("gradle/app/google-services.json");

	FText ErrorMessage;
	if (!SourceControlHelpers::CopyFileUnderSourceControl(DestinationJsonConfigPath, SourceConfigPath, LOCTEXT("FirebaseAndroidJsonConfigFile", "Firebase Android Json Config File"), /*out*/ ErrorMessage))
	{
		FNotificationInfo Info(LOCTEXT("GenerateFirebaseAndroidJsonConfigFileError", "Can't find file google-services.json"));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't find file google-services.json"));
	}

	FString CmdExe;
	FString CommandLine;

#if PLATFORM_WINDOWS
	CmdExe = FPaths::ConvertRelativePathToFull(FPaths::GetPath(UniversalPath)) / TEXT("generate_xml_from_google_services_json.exe");
	CommandLine = FString::Printf(TEXT("-i \"%s\" -o \"%s\""), *SourceConfigPath, *DestinationConfigPath);
#else
#if PLATFORM_MAC
    CmdExe = TEXT("/bin/sh");
#elif PLATFORM_LINUX
    CmdExe = TEXT("/bin/bash");
#else
    CmdExe = TEXT("python");
#endif
	CommandLine = FString::Printf(TEXT("python \"%s\" -i \"%s\" -o \"%s\""), *(FPaths::ConvertRelativePathToFull(FPaths::GetPath(UniversalPath)) / TEXT("generate_xml_from_google_services_json.py")), *SourceConfigPath, *DestinationConfigPath);
#endif

	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Source Config Path: %s\nDestination Config Path: %s\nCmdExe: %s\nCommand Line: %s"), *SourceConfigPath, *DestinationConfigPath, *CmdExe, *CommandLine);

	if (!FPaths::FileExists(SourceConfigPath))
	{
		FNotificationInfo Info(LOCTEXT("GenerateFirebaseAndroidConfigFileError", "Can't find file google-services.json"));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't find file %s"), *SourceConfigPath);

		return;
	}

#if PLATFORM_WINDOWS
	if (!FPaths::FileExists(CmdExe))
	{
		FNotificationInfo Info(LOCTEXT("GenerateFirebaseAndroidConfigFileError", "Can't find file generate_xml_from_google_services_json.exe"));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't find file %s"), *CmdExe);

		return;
	}
#endif

	AndroidConfigParseProcess = MakeShareable(new FMonitoredProcess(CmdExe, CommandLine, true, false));
	AndroidConfigParseProcess->Launch();
	AndroidConfigParseTickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FUltimateMobileKitSettingsCustomization::AndroidConfigParseUpdateStatus), 0.0f);
}

bool FUltimateMobileKitSettingsCustomization::AndroidConfigParseUpdateStatus(float Delay)
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Generating googleservices.xml..."));

	if (AndroidConfigParseProcess.IsValid())
	{
		if (AndroidConfigParseProcess->Update())
		{
			return true;
		}
		int RetCode = AndroidConfigParseProcess->GetReturnCode();
		AndroidConfigParseProcess = NULL;

		if (RetCode == 0)
		{
			UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("googleservices.xml generated successfully"));

			bool bParsingSuccessful = false;

			TArray<FString> LoadedData;
			TSharedPtr<FXmlFile, ESPMode::ThreadSafe> ConfigFile = MakeShareable(new FXmlFile());
			UUltimateMobileKitSettings* DefaultSettings = const_cast<UUltimateMobileKitSettings*>(GetDefault<UUltimateMobileKitSettings>());
			if (FFileHelper::LoadANSITextFileToStrings(*(AndroidIntermediatePath / TEXT("googleservices.xml")), NULL, LoadedData))
			{
				FString ParsedData;
				for (int i = 0; i < LoadedData.Num(); i++)
				{
					if (!LoadedData[i].StartsWith(TEXT("<?xml")))
					{
						ParsedData += LoadedData[i];
					}
				}

				if (ConfigFile->LoadFile(ParsedData, EConstructMethod::ConstructFromBuffer))
				{
					DefaultSettings->FirebaseClientIdAndroid.Empty();

					FXmlNode* RootNode = ConfigFile->GetRootNode();
					TArray<FXmlNode*> Children = RootNode->GetChildrenNodes();
					UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Parsing googleservices.xml..."));

					for (int i = 0; i < Children.Num(); i++)
					{
						const FString Key = Children[i]->GetAttribute("name");
						const FString Value = Children[i]->GetContent();

						if (Key.Equals("google_app_id"))
						{
							DefaultSettings->FirebaseAppIdAndroid = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("google_app_id: %s"), *Value);
						}
						if (Key.Equals("default_web_client_id"))
						{
							DefaultSettings->FirebaseClientIdAndroid.Add(Value);
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("default_web_client_id: %s"), *Value);
						}
						if (Key.Equals("google_api_key"))
						{
							DefaultSettings->FirebaseApiKeyAndroid = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("google_api_key: %s"), *Value);
						}
						if (Key.Equals("gcm_defaultSenderId"))
						{
							DefaultSettings->FirebaseCloudMessagingSenderIdAndroid = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("gcm_defaultSenderId: %s"), *Value);
						}
						if (Key.Equals("google_storage_bucket"))
						{
							DefaultSettings->FirebaseGoogleCloudStorageBucketNameAndroid = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("google_storage_bucket: %s"), *Value);
						}
						if (Key.Equals("firebase_database_url"))
						{
							DefaultSettings->FirebaseDatabaseURLAndroid = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("firebase_database_url: %s"), *Value);
						}
					}

					DefaultSettings->UpdateDefaultConfigFile();

					bParsingSuccessful = true;

					UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("googleservices.xml parsed successfully"));
				}
			}

			if (!bParsingSuccessful)
			{
				FNotificationInfo Info(LOCTEXT("ParseFirebaseAndroidConfigFileError", "Can't load googleservices.xml"));
				Info.ExpireDuration = 3.0f;
				FSlateNotificationManager::Get().AddNotification(Info);

				UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't load %s"), *(AndroidIntermediatePath / TEXT("googleservices.xml")));
			}
		}
	}

	return false;
}

void FUltimateMobileKitSettingsCustomization::OnGeneratingPlistCompleted(int32 ReturnCode)
{
	// Success
	if (ReturnCode == 0)
	{
		if (GeneratingPlistState)
		{
			GeneratingPlistSuccess();
		}
		else
		{
			GeneratingPlistFailure();
		}
	}
	// Failure
	else
	{
		GeneratingPlistFailure();
	}
}

void FUltimateMobileKitSettingsCustomization::OnGeneratingPlistCanceled()
{
	GeneratingPlistFailure();
}

void FUltimateMobileKitSettingsCustomization::OnGeneratingPlistProgress(FString Output)
{
	// Success
	if (Output.Equals("1"))
	{
		GeneratingPlistState = true;
	}
	// Failure
	else
	{
		GeneratingPlistState = false;
	}
}

void FUltimateMobileKitSettingsCustomization::GeneratingPlistSuccess()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("GoogleServicesPlist.embeddedframework.zip generated successfully"));
}

void FUltimateMobileKitSettingsCustomization::GeneratingPlistFailure()
{
    DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_GeneratingPlistFailure"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_GeneratingPlistFailure, STATGROUP_TaskGraphTasks);
    
    FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
        FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
            FNotificationInfo Info(LOCTEXT("GeneratingPlistError", "Can't generate GoogleServicesPlist.embeddedframework.zip"));
            Info.ExpireDuration = 3.0f;
            FSlateNotificationManager::Get().AddNotification(Info);
            UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't generate GoogleServicesPlist.embeddedframework.zip"));
        }),
        GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_GeneratingPlistFailure),
        nullptr,
        ENamedThreads::GameThread
    );
}

void FUltimateMobileKitSettingsCustomization::GenerateIOSConfigFiles()
{
	UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Generate Firebase Config Files for IOS"));

	FText ErrorMessage;
	if (!SourceControlHelpers::CopyFileUnderSourceControl(IOSDestinationConfigPath / TEXT("GoogleService-Info.plist"), (IOSSourceConfigFolderPath / TEXT("GoogleService-Info.plist")), LOCTEXT("FirebaseIOSConfigFile", "Firebase IOS Config File"), /*out*/ ErrorMessage))
	{
		FNotificationInfo Info(LOCTEXT("GenerateFirebaseIOSConfigFileError", "Can't find file GoogleService-Info.plist"));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);

		UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't find file GoogleService-Info.plist"));
	}
	else
	{
		bool bParsingSuccessful = false;

		TArray<FString> LoadedData;
		TSharedPtr<FXmlFile, ESPMode::ThreadSafe> ConfigFile = MakeShareable(new FXmlFile());
		if (FFileHelper::LoadANSITextFileToStrings(*(IOSDestinationConfigPath / TEXT("GoogleService-Info.plist")), NULL, LoadedData))
		{
			FString ParsedData;
			for (int i = 0; i < LoadedData.Num(); i++)
			{
				if (!LoadedData[i].StartsWith(TEXT("<plist")) && !LoadedData[i].StartsWith(TEXT("<!DOCTYPE")) && !LoadedData[i].StartsWith(TEXT("<?xml")))
				{
					ParsedData += LoadedData[i];
				}
			}

			if (ConfigFile->LoadFile(ParsedData, EConstructMethod::ConstructFromBuffer))
			{
				UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("GoogleService-Info.plist loaded successfully"));

				UUltimateMobileKitSettings* DefaultSettings = const_cast<UUltimateMobileKitSettings*>(GetDefault<UUltimateMobileKitSettings>());

				FXmlNode* RootNode = ConfigFile->GetRootNode();
				TArray<FXmlNode*> Children = RootNode->GetChildrenNodes();

				UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("Parsing GoogleService-Info.plist..."));

				for (int i = 0; i < Children.Num() - 1; i++)
				{
					if (Children[i]->GetTag().Equals("key") && Children[i + 1]->GetTag().Equals("string"))
					{
						const FString Key = Children[i]->GetContent();
						const FString Value = Children[i + 1]->GetContent();

						if (Key.Equals("BUNDLE_ID"))
						{
							DefaultSettings->FirebaseBundleIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("BUNDLE_ID: %s"), *Value);
						}
						if (Key.Equals("GOOGLE_APP_ID"))
						{
							DefaultSettings->FirebaseAppIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("GOOGLE_APP_ID: %s"), *Value);
						}
						if (Key.Equals("CLIENT_ID"))
						{
							DefaultSettings->FirebaseClientIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("CLIENT_ID: %s"), *Value);
						}
						if (Key.Equals("REVERSED_CLIENT_ID"))
						{
							DefaultSettings->FirebaseReversedClientIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("REVERSED_CLIENT_ID: %s"), *Value);
						}
						if (Key.Equals("API_KEY"))
						{
							DefaultSettings->FirebaseApiKeyIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("API_KEY: %s"), *Value);
						}
						if (Key.Equals("PROJECT_ID"))
						{
							DefaultSettings->FirebaseProjectIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("PROJECT_ID: %s"), *Value);
						}
						if (Key.Equals("GCM_SENDER_ID"))
						{
							DefaultSettings->FirebaseCloudMessagingSenderIdIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("GCM_SENDER_ID: %s"), *Value);
						}
						if (Key.Equals("STORAGE_BUCKET"))
						{
							DefaultSettings->FirebaseGoogleCloudStorageBucketNameIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("STORAGE_BUCKET: %s"), *Value);
						}
						if (Key.Equals("DATABASE_URL"))
						{
							DefaultSettings->FirebaseDatabaseURLIOS = Value;
							UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("DATABASE_URL: %s"), *Value);
						}
					}
				}

				DefaultSettings->UpdateDefaultConfigFile();

				bParsingSuccessful = true;

				GeneratePlistFramework();

				UE_LOG(LogUltimateMobileKitEditor, Display, TEXT("GoogleService-Info.plist parsed successfully"));
			}
		}

		if (!bParsingSuccessful)
		{
			FNotificationInfo Info(LOCTEXT("ParseFirebaseIOSConfigFileError", "Can't load GoogleService-Info.plist"));
			Info.ExpireDuration = 3.0f;
			FSlateNotificationManager::Get().AddNotification(Info);

			UE_LOG(LogUltimateMobileKitEditor, Error, TEXT("Can't load GoogleService-Info.plist"));
		}
	}

	SavedLayoutBuilder->ForceRefreshDetails();
}

void FUltimateMobileKitSettingsCustomization::GeneratePlistFramework()
{
	FString PluginDir = IPluginManager::Get().FindPlugin(TEXT("UltimateMobileKit"))->GetBaseDir();
	FString ProjectDir = FPaths::ProjectDir();
	FString FrameworkSourcePath = PluginDir + "/Extras/GoogleServicesPlistGenerator/GoogleServicesPlist.framework/";

	FString ProcessPath = FPaths::ConvertRelativePathToFull(PluginDir + TEXT("/Extras/GoogleServicesPlistGenerator/GoogleServicesPlistGenerator.exe"));
	FString CommandLine = FString("\"") + FPaths::ConvertRelativePathToFull(ProjectDir) + FString("\" \"") + FPaths::ConvertRelativePathToFull(FrameworkSourcePath) + FString("\"");

#if PLATFORM_MAC
	FString CmdExe = TEXT("/bin/sh");
	FString ScriptPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Build/BatchFiles/Mac/RunMono.sh"));
	FString FullCommandLine = FString::Printf(TEXT("\"%s\" \"%s\" %s"), *ScriptPath, *ProcessPath, *CommandLine);
#elif PLATFORM_LINUX
	FString CmdExe = TEXT("/bin/bash");
	FString ScriptPath = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Build/BatchFiles/Linux/RunMono.sh"));
	FString FullCommandLine = FString::Printf(TEXT("\"%s\" \"%s\" %s"), *ScriptPath, *ProcessPath, *CommandLine);
#else
	FString CmdExe = ProcessPath;
	FString FullCommandLine = CommandLine;
#endif

	FMonitoredProcess* InstallerProcess = new FMonitoredProcess(CmdExe, FullCommandLine, true);
	InstallerProcess->OnOutput().BindRaw(this, &FUltimateMobileKitSettingsCustomization::OnGeneratingPlistProgress);
	InstallerProcess->OnCompleted().BindRaw(this, &FUltimateMobileKitSettingsCustomization::OnGeneratingPlistCompleted);
	InstallerProcess->OnCanceled().BindRaw(this, &FUltimateMobileKitSettingsCustomization::OnGeneratingPlistCanceled);
	bool bSuccess = InstallerProcess->Launch();

	if (!bSuccess)
	{
		GeneratingPlistFailure();
	}
}

#undef LOCTEXT_NAMESPACE
