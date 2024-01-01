// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Storage/FirebaseStorage.h"
#include "Storage/StorageInitialize.h"
#include "Storage/StorageReferenceDelete.h"
#include "Storage/StorageReferenceGetDownloadUrl.h"
#include "Storage/StorageReferenceGetFile.h"
#include "Storage/StorageReferenceGetMetadata.h"
#include "Storage/StorageReferencePutFile.h"
#include "Storage/StorageReferenceUpdateMetadata.h"
#include "UltimateMobileKit.h"
#include <string>
#include <iostream>

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE && PLATFORM_ANDROID
FString AndroidThunkCpp_FirebaseGetPlatformStoragePath()
{
	FString Result = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseGetPlatformStoragePath", "()Ljava/lang/String;", false);
		jstring StoragePath = (jstring) FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);

		if (StoragePath != NULL)
		{
			const char* StoragePathChars = Env->GetStringUTFChars(StoragePath, 0);
			Result = FString(UTF8_TO_TCHAR(StoragePathChars));
			Env->ReleaseStringUTFChars(StoragePath, StoragePathChars);
			Env->DeleteLocalRef(StoragePath);
		}
	}
	return Result;
}

bool AndroidThunkCpp_FirebaseUseExternalFilesDir()
{
	bool bUserExternalFilesDir = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseUseExternalFilesDir", "()Z", false);
		bUserExternalFilesDir = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
	return bUserExternalFilesDir;
}
#endif

FFirebaseStorage::FFirebaseStorage()
{
}

FFirebaseStorage::~FFirebaseStorage()
{
}

void FFirebaseStorage::Init(const FOnFirebaseStorageInitializeCompleteDelegate& Delegate /*= FOnFirebaseStorageInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true, EFirebaseStorageError::None);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseStorageInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown);
}

void FFirebaseStorage::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage Shutdown"));
}

const bool FFirebaseStorage::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseStorage::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage is not initialized"));
	}
}

const bool FFirebaseStorage::RegisterService()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FirebaseNativeStoragePtr = MakeShareable(firebase::storage::Storage::GetInstance(UltimateMobileKit->GetFirebaseApp()->GetFirebaseNativeApp().Get()));

		if (FirebaseNativeStoragePtr.IsValid())
		{
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Native Storage service registered"));

			return true;
		}
	}
#endif

	return false;
}

const FString FFirebaseStorage::GetPlatformStoragePath() const
{
#if PLATFORM_IOS
	NSArray<NSString *> *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = paths.firstObject;	
	std::string PlatformPath = "file://" + std::string([[documentsDirectory stringByStandardizingPath] stringByAppendingString:@"/"].UTF8String);
	return FString(PlatformPath.c_str());
#elif PLATFORM_ANDROID && WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	return AndroidThunkCpp_FirebaseGetPlatformStoragePath();
#endif

	return FString();
}

const FString FFirebaseStorage::GetUnrealStoragePath() const
{
#if PLATFORM_IOS
	return GetPlatformStoragePath() + FApp::GetProjectName() + FString("/");
#elif PLATFORM_ANDROID && WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		// External Storage Directory
		static FString BasePath = FString("");
		if (!AndroidThunkCpp_FirebaseUseExternalFilesDir())
		{
			jclass EnvClass = Env->FindClass("android/os/Environment");
			jmethodID getExternalStorageDir = Env->GetStaticMethodID(EnvClass, "getExternalStorageDirectory", "()Ljava/io/File;");
			jobject externalStoragePath = Env->CallStaticObjectMethod(EnvClass, getExternalStorageDir, nullptr);
			jmethodID getFilePath = Env->GetMethodID(Env->FindClass("java/io/File"), "getPath", "()Ljava/lang/String;");
			jstring pathString = (jstring)Env->CallObjectMethod(externalStoragePath, getFilePath, nullptr);
			const char *nativePathString = Env->GetStringUTFChars(pathString, 0);
			BasePath = FString(nativePathString);
			Env->ReleaseStringUTFChars(pathString, nativePathString);
			Env->DeleteLocalRef(pathString);
			Env->DeleteLocalRef(externalStoragePath);
			Env->DeleteLocalRef(EnvClass);
		}
		// External Files Dir
		else
		{
			jclass ContextClass = Env->FindClass("android/content/Context");
			jmethodID getExternalFilesDir = Env->GetMethodID(ContextClass, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
			jobject externalFilesDirPath = Env->CallObjectMethod(FJavaWrapper::GameActivityThis, getExternalFilesDir, nullptr);
			jmethodID getFilePath = Env->GetMethodID(Env->FindClass("java/io/File"), "getPath", "()Ljava/lang/String;");
			jstring externalFilesPathString = (jstring)Env->CallObjectMethod(externalFilesDirPath, getFilePath, nullptr);
			const char *nativeExternalFilesPathString = Env->GetStringUTFChars(externalFilesPathString, 0);
			BasePath = FString(nativeExternalFilesPathString);
			Env->ReleaseStringUTFChars(externalFilesPathString, nativeExternalFilesPathString);
			Env->DeleteLocalRef(externalFilesPathString);
			Env->DeleteLocalRef(externalFilesDirPath);
			Env->DeleteLocalRef(ContextClass);
		}		

		return BasePath + FString("/UE4Game/") + FApp::GetProjectName() + FString("/") + FApp::GetProjectName() + FString("/");;
	}
#endif

	return FString();
}

const FString FFirebaseStorage::GetSaveGameStoragePath() const
{
	return GetUnrealStoragePath() + FString("Saved/SaveGames/");
}

UStorageReference* FFirebaseStorage::GetStorageReferenceToRoot() const
{
	UStorageReference* NewStorageReference = NewObject<UStorageReference>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			FFirebaseNativeStoragePtr NativeStorage = UltimateMobileKit->GetFirebaseStorage()->GetFirebaseNativeStorage();

			if (NativeStorage.IsValid())
			{
				FFirebaseNativeStorageReferencePtr NewNativeStorageReference = MakeShareable(new firebase::storage::StorageReference(NativeStorage->GetReference()));
				NewStorageReference->RegisterStorageFullPath(NewNativeStorageReference);

				UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage Reference to root retrieved successfully"));
			}
		}
	}
#endif

	return NewStorageReference;
}

UStorageReference* FFirebaseStorage::GetStorageReferenceFromUrl(const FString& Url) const
{
	UStorageReference* NewStorageReference = NewObject<UStorageReference>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			FFirebaseNativeStoragePtr NativeStorage = UltimateMobileKit->GetFirebaseStorage()->GetFirebaseNativeStorage();

			if (NativeStorage.IsValid())
			{
				FFirebaseNativeStorageReferencePtr NewNativeStorageReference = MakeShareable(new firebase::storage::StorageReference(NativeStorage->GetReferenceFromUrl(TCHAR_TO_UTF8(*Url))));
				NewStorageReference->RegisterStorageFullPath(NewNativeStorageReference);

				UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage Reference from URL %s retrieved successfully"), *Url);
			}
		}
	}
#endif

	return NewStorageReference;
}

UStorageReference* FFirebaseStorage::GetStorageReferenceFromPath(const FString& Path) const
{
	UStorageReference* NewStorageReference = NewObject<UStorageReference>();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			FFirebaseNativeStoragePtr NativeStorage = UltimateMobileKit->GetFirebaseStorage()->GetFirebaseNativeStorage();

			if (NativeStorage.IsValid())
			{
				FFirebaseNativeStorageReferencePtr NewNativeStorageReference = MakeShareable(new firebase::storage::StorageReference(NativeStorage->GetReference(TCHAR_TO_UTF8(*Path))));
				NewStorageReference->RegisterStorageFullPath(NewNativeStorageReference);

				UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Storage Reference from path %s retrieved successfully"), *Path);
			}
		}
}
#endif

	return NewStorageReference;
}

void FFirebaseStorage::ReferenceDelete(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceDeleteCompleteDelegate& Delegate /*= FOnFirebaseStorageReferenceDeleteCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferenceDelete(UltimateMobileKit->Get(), Delegate, StorageReference);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown);
}

void FFirebaseStorage::ReferenceGetDownloadUrl(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate& Delegate /*= FOnFirebaseStorageReferenceGetDownloadUrlCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferenceGetDownloadUrl(UltimateMobileKit->Get(), Delegate, StorageReference);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown, FString());
}

void FFirebaseStorage::ReferenceGetFile(const UStorageReference* StorageReference, const FString& PathFile, const FOnFirebaseStorageReferenceGetFileCompleteDelegate& Delegate /*= FOnFirebaseStorageReferenceGetFileCompleteDelegate()*/, const FOnFirebaseStorageReferenceGetFileStartCompleteDelegate& StartDelegate /*= FOnFirebaseStorageReferenceGetFileStartCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferenceGetFile(UltimateMobileKit->Get(), Delegate, StartDelegate, StorageReference, PathFile);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown);
}

void FFirebaseStorage::ReferenceGetMetadata(const UStorageReference* StorageReference, const FOnFirebaseStorageReferenceGetMetadataCompleteDelegate& Delegate /*= FOnFirebaseStorageReferenceGetMetadataCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferenceGetMetadata(UltimateMobileKit->Get(), Delegate, StorageReference);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown, FFirebaseStorageMetadata());
}

void FFirebaseStorage::ReferencePutFile(const UStorageReference* StorageReference, const FString& PathFile, const FOnFirebaseStorageReferencePutFileCompleteDelegate& Delegate /*= FOnFirebaseStorageReferencePutFileCompleteDelegate()*/, const FOnFirebaseStorageReferencePutFileStartCompleteDelegate& StartDelegate /*= FOnFirebaseStorageReferencePutFileStartCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferencePutFile(UltimateMobileKit->Get(), Delegate, StartDelegate, StorageReference, PathFile);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown);
}

void FFirebaseStorage::ReferenceUpdateMetadata(const UStorageReference* StorageReference, const FFirebaseStorageMetadataWrite StorageMetadata, const FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate& Delegate /*= FOnFirebaseStorageReferenceUpdateMetadataCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseStorageReferenceUpdateMetadata(UltimateMobileKit->Get(), Delegate, StorageReference, StorageMetadata);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseStorageError::Unknown, FFirebaseStorageMetadata());
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_STORAGE
EFirebaseStorageError FFirebaseStorage::FirebaseErrorFromNative(const firebase::storage::Error& NativeError)
{
	switch (NativeError)
	{
	case firebase::storage::kErrorBucketNotFound:
		return EFirebaseStorageError::BucketNotFound;
	case firebase::storage::kErrorCancelled:
		return EFirebaseStorageError::Cancelled;
	case firebase::storage::kErrorDownloadSizeExceeded:
		return EFirebaseStorageError::DownloadSizeExceeded;
	case firebase::storage::kErrorNonMatchingChecksum:
		return EFirebaseStorageError::NonMatchingChecksum;
	case firebase::storage::kErrorNone:
		return EFirebaseStorageError::None;
	case firebase::storage::kErrorObjectNotFound:
		return EFirebaseStorageError::ObjectNotFound;
	case firebase::storage::kErrorProjectNotFound:
		return EFirebaseStorageError::ProjectNotFound;
	case firebase::storage::kErrorQuotaExceeded:
		return EFirebaseStorageError::QuotaExceeded;
	case firebase::storage::kErrorRetryLimitExceeded:
		return EFirebaseStorageError::RetryLimitExceeded;
	case firebase::storage::kErrorUnauthenticated:
		return EFirebaseStorageError::Unauthenticated;
	case firebase::storage::kErrorUnauthorized:
		return EFirebaseStorageError::Unauthorized;
	case firebase::storage::kErrorUnknown:
		return EFirebaseStorageError::Unknown;
	default:
		return EFirebaseStorageError::None;
	}
}
#endif
