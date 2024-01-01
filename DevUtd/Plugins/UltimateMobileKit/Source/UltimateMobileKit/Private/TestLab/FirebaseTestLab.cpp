// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "TestLab/FirebaseTestLab.h"
#include "UltimateMobileKitComponent.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
void AndroidThunkCpp_FirebaseTestLabTakeScreenshot(const FString& Label)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring LabelFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Label));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseTestLabTakeScreenshot", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, LabelFinal);
		Env->DeleteLocalRef(LabelFinal);
	}
}

void AndroidThunkCpp_FirebaseTestLabFinishTest()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseTestLabFinishTest", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}

int32 AndroidThunkCpp_FirebaseTestLabGetGameLoopScenario()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseTestLabGetGameLoopScenario", "()I", false);
		return FJavaWrapper::CallIntMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}

	return 0;
}
#endif

FFirebaseTestLab::FFirebaseTestLab()
{
}

FFirebaseTestLab::~FFirebaseTestLab()
{
}

void FFirebaseTestLab::Init()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab Init"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
	bInitialized = true;
#endif
}

void FFirebaseTestLab::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab Shutdown"));
}

const bool FFirebaseTestLab::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseTestLab::TakeScreenshot(const FString& Label) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab Take Screenshot with label: %s"), *Label);

	AndroidThunkCpp_FirebaseTestLabTakeScreenshot(Label);
#else
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab available only on Android platform"));
#endif
}

void FFirebaseTestLab::FinishTest() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab Finish Test"));

	AndroidThunkCpp_FirebaseTestLabFinishTest();
#else
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab available only on Android platform"));
#endif
}


int32 FFirebaseTestLab::GetGameLoopScenario() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_TESTLAB && PLATFORM_ANDROID
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Get Game Loop Scenario"));

	return AndroidThunkCpp_FirebaseTestLabGetGameLoopScenario();
#else
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Test Lab available only on Android platform"));
#endif

	return 0;
}
