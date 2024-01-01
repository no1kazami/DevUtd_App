// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "MobileUtilsPlatform.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


jmethodID FMobileUtilsPlatform::CheckInternetConnectionMethod;
jmethodID FMobileUtilsPlatform::CheckGooglePlayServicesMethod;
jmethodID FMobileUtilsPlatform::GetPersistentUniqueDeviceIdMethod;
jmethodID FMobileUtilsPlatform::GetDeviceIdMethod;
jmethodID FMobileUtilsPlatform::ToggleOrientationMethod;
jmethodID FMobileUtilsPlatform::SendEmailMethod;
jmethodID FMobileUtilsPlatform::ShareAppMethod;
jmethodID FMobileUtilsPlatform::NewSendEmailMethod;
jmethodID FMobileUtilsPlatform::NewShareAppMethod;

FMobileUtilsPlatform::FMobileUtilsPlatform()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		CheckInternetConnectionMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CheckInternetConnection", "()Z", false);
		CheckGooglePlayServicesMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CheckGooglePlayServices", "()Z", false);
		GetPersistentUniqueDeviceIdMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetPersistentUniqueDeviceId", "()Ljava/lang/String;", false);
		GetDeviceIdMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetDeviceId", "()Ljava/lang/String;", false);
		ToggleOrientationMethod = FJavaWrapper::FindMethod( Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ToggleOrientation", "()Z", false );
		SendEmailMethod = FJavaWrapper::FindMethod( Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SendEmail", "()Z", false );
		ShareAppMethod = FJavaWrapper::FindMethod( Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShareApp", "()Z", false );
		NewSendEmailMethod = FJavaWrapper::FindMethod( Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_NewSendEmail", "(Ljava/lang/String;)Z", false );
		NewShareAppMethod = FJavaWrapper::FindMethod( Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_NewShareApp", "(Ljava/lang/String;)Z", false );
	}
}

FMobileUtilsPlatform::~FMobileUtilsPlatform()
{
}

bool FMobileUtilsPlatform::CheckInternetConnection()
{
	bool bResult = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::CheckInternetConnectionMethod);
	}
	return bResult;
}

bool FMobileUtilsPlatform::CheckGooglePlayServices()
{
	bool bResult = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::CheckGooglePlayServicesMethod);
	}
	return bResult;
}

FString FMobileUtilsPlatform::GetPersistentUniqueDeviceId()
{
	FString ResultDeviceId = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring ResultDeviceIdString = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::GetPersistentUniqueDeviceIdMethod);
		const char *nativeDeviceIdString = Env->GetStringUTFChars(ResultDeviceIdString, 0);
		ResultDeviceId = FString(nativeDeviceIdString);
		Env->ReleaseStringUTFChars(ResultDeviceIdString, nativeDeviceIdString);
		Env->DeleteLocalRef(ResultDeviceIdString);
	}
	return ResultDeviceId;
}

FString FMobileUtilsPlatform::GetDeviceId()
{
	FString ResultDeviceId = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring ResultDeviceIdString = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::GetDeviceIdMethod);
		const char *nativeDeviceIdString = Env->GetStringUTFChars(ResultDeviceIdString, 0);
		ResultDeviceId = FString(nativeDeviceIdString);
		Env->ReleaseStringUTFChars(ResultDeviceIdString, nativeDeviceIdString);
		Env->DeleteLocalRef(ResultDeviceIdString);
	}
	return ResultDeviceId;
}

bool FMobileUtilsPlatform::ToggleOrientation()
{
	bool tResult = false;
	if( JNIEnv* Env = FAndroidApplication::GetJavaEnv() )
	{
		tResult = FJavaWrapper::CallBooleanMethod( Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::ToggleOrientationMethod );
	}
	return tResult;
}

bool FMobileUtilsPlatform::SendEmail()
{
	bool tResult = false;
	if( JNIEnv* Env = FAndroidApplication::GetJavaEnv() )
	{
		tResult = FJavaWrapper::CallBooleanMethod( Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::SendEmailMethod );
	}
	return tResult;
}

bool FMobileUtilsPlatform::ShareApp()
{
	bool tResult = false;
	if( JNIEnv* Env = FAndroidApplication::GetJavaEnv() )
	{
		tResult = FJavaWrapper::CallBooleanMethod( Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::ShareAppMethod );
	}
	return tResult;
}

bool FMobileUtilsPlatform::NewSendEmail( FString emailAddress )
{
	bool tResult = false;
	if( JNIEnv* Env = FAndroidApplication::GetJavaEnv() )
	{
		jstring emailAddressFinal = Env->NewStringUTF( TCHAR_TO_UTF8( *emailAddress ) );
		tResult = FJavaWrapper::CallBooleanMethod( Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::NewSendEmailMethod, emailAddressFinal );
		Env->DeleteLocalRef( emailAddressFinal );
	}
	return tResult;
}

bool FMobileUtilsPlatform::NewShareApp( FString shareAddres )
{
	bool tResult = false;
	if( JNIEnv* Env = FAndroidApplication::GetJavaEnv() )
	{
		jstring shareAddresFinal = Env->NewStringUTF( TCHAR_TO_UTF8( *shareAddres ) );
		tResult = FJavaWrapper::CallBooleanMethod( Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::NewShareAppMethod, shareAddresFinal );
		Env->DeleteLocalRef( shareAddresFinal );
	}
	return tResult;
}
