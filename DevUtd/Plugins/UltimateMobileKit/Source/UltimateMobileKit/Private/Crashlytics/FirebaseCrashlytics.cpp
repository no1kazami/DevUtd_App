// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Crashlytics/FirebaseCrashlytics.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS && PLATFORM_IOS
#import <Fabric/Fabric.h>
#import <Crashlytics/Crashlytics.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS && PLATFORM_ANDROID
void AndroidThunkCpp_FirebaseCrashlyticsForceCrash()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsForceCrash", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsForceException()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsForceException", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetUserIdentifier(const FString& Identifier)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring IdentifierFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Identifier));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetUserIdentifier", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, IdentifierFinal);
		Env->DeleteLocalRef(IdentifierFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetUsername(const FString& Username)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring UsernameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Username));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetUsername", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, UsernameFinal);
		Env->DeleteLocalRef(UsernameFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetUserEmail(const FString& Email)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring EmailFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Email));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetUserEmail", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, EmailFinal);
		Env->DeleteLocalRef(EmailFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsWriteLog(const FString& Log)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring LogFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Log));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsWriteLog", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, LogFinal);
		Env->DeleteLocalRef(LogFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsWriteLogWithTagAndPriority(const FString& Log, const FString& Tag, int32 Priority)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring LogFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Log));
		jstring TagFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Tag));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsWriteLogWithTagAndPriority", "(Ljava/lang/String;Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, LogFinal, TagFinal, Priority);
		Env->DeleteLocalRef(LogFinal);
		Env->DeleteLocalRef(TagFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetString(const FString& Key, const FString& Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		jstring ValueFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetString", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyFinal, ValueFinal);
		Env->DeleteLocalRef(KeyFinal);
		Env->DeleteLocalRef(ValueFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetBool(const FString& Key, bool Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetBool", "(Ljava/lang/String;Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyFinal, Value);
		Env->DeleteLocalRef(KeyFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetFloat(const FString& Key, float Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetFloat", "(Ljava/lang/String;F)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyFinal, Value);
		Env->DeleteLocalRef(KeyFinal);
	}
}

void AndroidThunkCpp_FirebaseCrashlyticsSetInteger(const FString& Key, int Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring KeyFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Key));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseCrashlyticsSetInteger", "(Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, KeyFinal, Value);
		Env->DeleteLocalRef(KeyFinal);
	}
}
#endif

FFirebaseCrashlytics::FFirebaseCrashlytics()
{
}

FFirebaseCrashlytics::~FFirebaseCrashlytics()
{
}

void FFirebaseCrashlytics::Init()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Init"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
	bInitialized = true;

	#if PLATFORM_IOS
		// Settings
		const UUltimateMobileKitSettings* DefaultSettings = GetDefault<UUltimateMobileKitSettings>();

		// Debug mode
		if (DefaultSettings->bEnableCrashlyticsDebugMode)
		{
			[Fabric.sharedSDK setDebug : YES];
		}

		dispatch_async(dispatch_get_main_queue(), ^{
			[Fabric with : @[[Crashlytics class]]];
		});
	#endif
#endif

}

void FFirebaseCrashlytics::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Shutdown"));
}

const bool FFirebaseCrashlytics::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseCrashlytics::ForceCrash() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseCrashlyticsForceCrash();
#elif PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		[CrashlyticsKit crash];
	});
#endif
#endif
}

void FFirebaseCrashlytics::ForceException() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseCrashlyticsForceException();
#elif PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		[CrashlyticsKit throwException];
	});
#endif
#endif
}

void FFirebaseCrashlytics::SetUserIdentifier(const FString& Identifier) const
{
	if (Identifier.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set User Identifier: %s"), *Identifier);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetUserIdentifier(Identifier);
#elif PLATFORM_IOS
    NSString* CrashlyticsIdentifierTemp = Identifier.GetNSString();
	dispatch_async(dispatch_get_main_queue(), ^{
		[CrashlyticsKit setUserIdentifier : CrashlyticsIdentifierTemp];
	});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetUserEmail(const FString& Email) const
{
	if (Email.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set User Email: %s"), *Email);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetUserEmail(Email);
#elif PLATFORM_IOS
        NSString* CrashlyticsEmailTemp = Email.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setUserEmail : CrashlyticsEmailTemp];
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetUsername(const FString& Username) const
{
	if (Username.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set Username: %s"), *Username);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetUsername(Username);
#elif PLATFORM_IOS
        NSString* CrashlyticsUsernameTemp = Username.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setUserName : CrashlyticsUsernameTemp];
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::WriteLog(const FString& Log) const
{
	if (Log.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Write Log: %s"), *Log);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsWriteLog(Log);
#elif PLATFORM_IOS
        NSString* CrashlyticsLogTemp = Log.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			CLS_LOG(@"%@", CrashlyticsLogTemp);
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::WriteLogWithTagAndPriority(const FString& Log, const FString& Tag, const int32 Priority) const
{
	if (Log.Len() > 0 && Tag.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Write Log: %s, Tag: %s, Priority: %d"), *Log, *Tag, Priority);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsWriteLogWithTagAndPriority(Log, Tag, Priority);
#elif PLATFORM_IOS
        NSString* CrashlyticsLogTemp = Log.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			CLS_LOG(@"%@", CrashlyticsLogTemp);
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetString(const FString& Key, const FString& Value) const
{
	if (Key.Len() > 0 && Value.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set String: Key: %s, Value: %s"), *Key, *Value);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetString(Key, Value);
#elif PLATFORM_IOS
        NSString* CrashlyticsValueTemp = Value.GetNSString();
        NSString* CrashlyticsKeyTemp = Key.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setObjectValue : CrashlyticsValueTemp forKey : CrashlyticsKeyTemp];
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetBool(const FString& Key, const bool Value) const
{
	if (Key.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set Bool: Key: %s, Value: %d"), *Key, Value);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetBool(Key, Value);
#elif PLATFORM_IOS
        NSString* CrashlyticsKeyTemp = Key.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setBoolValue : Value forKey : CrashlyticsKeyTemp];
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetFloat(const FString& Key, const float Value) const
{
	if (Key.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set Float: Key: %s, Value: %f"), *Key, Value);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetFloat(Key, Value);
#elif PLATFORM_IOS
        NSString* CrashlyticsKeyTemp = Key.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setFloatValue : Value forKey : CrashlyticsKeyTemp];
		});
#endif
#endif
	}
}

void FFirebaseCrashlytics::SetInteger(const FString& Key, const int32 Value) const
{
	if (Key.Len() > 0)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Crashlytics Set Integer: Key: %s, Value: %d"), *Key, Value);

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_CRASHLYTICS
#if PLATFORM_ANDROID
		AndroidThunkCpp_FirebaseCrashlyticsSetInteger(Key, Value);
#elif PLATFORM_IOS
        NSString* CrashlyticsKeyTemp = Key.GetNSString();
		dispatch_async(dispatch_get_main_queue(), ^{
			[CrashlyticsKit setIntValue : Value forKey : CrashlyticsKeyTemp];
		});
#endif
#endif
	}
}
