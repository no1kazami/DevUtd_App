// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/AuthSignInWithGoogle.h"
#include "UltimateMobileKit.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION && PLATFORM_IOS
#import <GoogleSignIn/GoogleSignIn.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION && PLATFORM_ANDROID
void AndroidThunkCpp_FirebaseGoogleSignIn()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseGoogleSignIn", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
}
#endif

FString FFirebaseAuthSignInWithGoogle::ResultIdTokenJava;
FString FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION && PLATFORM_IOS
@interface UltimateMobileKitAuthSignInWithGoogle:UIResponder<UIApplicationDelegate, GIDSignInDelegate, GIDSignInUIDelegate>
@end

@implementation UltimateMobileKitAuthSignInWithGoogle
// Singleton
+ (UltimateMobileKitAuthSignInWithGoogle*)GetDelegate
{
	static UltimateMobileKitAuthSignInWithGoogle * Singleton = [[UltimateMobileKitAuthSignInWithGoogle alloc] init];
	return Singleton;
}

-(void) signIn : (GIDSignIn*) signIn didSignInForUser : (GIDGoogleUser*) user withError : (NSError*) error 
{
	if (error == nil && user != nil && user.authentication != nil) 
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_AuthSignInWithGoogleCompleted"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
				FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString(user.authentication.idToken);
				FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString(user.serverAuthCode);

				UE_LOG(LogUltimateMobileKit, Display, TEXT("Google Sign In is successful. Id Token: %s, Server Auth Code: %s"), *(FFirebaseAuthSignInWithGoogle::ResultIdTokenJava), *(FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava));
			}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted),
			nullptr,
			ENamedThreads::GameThread
		);
	}
	else 
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_AuthSignInWithGoogleCompleted"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
				FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString("FAILURE");
				FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString("FAILURE");
			}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted),
			nullptr,
			ENamedThreads::GameThread
		);
	}
}

-(void) signIn : (GIDSignIn*) signIn didDisconnectWithUser : (GIDGoogleUser*) user withError : (NSError*) error 
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UltimateMobileKit_AuthSignInWithGoogleCompleted"), STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted, STATGROUP_TaskGraphTasks);

	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]() {
			FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString("FAILURE");
			FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString("FAILURE");
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_UltimateMobileKit_AuthSignInWithGoogleCompleted),
		nullptr,
		ENamedThreads::GameThread
	);
}

-(void) signInWillDispatch : (GIDSignIn*) signIn error : (NSError*) error 
{
}

-(void) signIn : (GIDSignIn*) signIn presentViewController : (UIViewController*) viewController
{
}

-(void) signIn : (GIDSignIn*) signIn dismissViewController : (UIViewController*) viewController 
{
}

-(BOOL) application : (UIApplication*) application openURL : (NSURL*) url sourceApplication : (NSString*) sourceApplication annotation : (id) annotation 
{
	return [[GIDSignIn sharedInstance] handleURL:url sourceApplication : sourceApplication annotation : annotation];
}
@end
#endif

FFirebaseAuthSignInWithGoogle::FFirebaseAuthSignInWithGoogle(FUltimateMobileKit* InSubsystem, const FOnFirebaseAuthSignInWithGoogleCompleteDelegate& InDelegate) : FOnlineAsyncTaskBasic(InSubsystem)
	, Delegate(InDelegate)
{
}

void FFirebaseAuthSignInWithGoogle::Start_OnTaskThread()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Executing FirebaseAuthSignInWithGoogle async task..."));

	FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString("PENDING");
	FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString("PENDING");

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#if PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseGoogleSignIn();
#elif PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		[GIDSignIn sharedInstance].clientID = [FIRApp defaultApp].options.clientID;
		[GIDSignIn sharedInstance].serverClientID = [FIRApp defaultApp].options.clientID;
		[GIDSignIn sharedInstance].delegate = [UltimateMobileKitAuthSignInWithGoogle GetDelegate];
		[GIDSignIn sharedInstance].uiDelegate = [UltimateMobileKitAuthSignInWithGoogle GetDelegate];
		[[GIDSignIn sharedInstance] signIn];
	});
#endif
	return;
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}

void FFirebaseAuthSignInWithGoogle::Tick()
{
	if (!bInit)
	{
		Start_OnTaskThread();
		bInit = true;
	}

	if(!FFirebaseAuthSignInWithGoogle::ResultIdTokenJava.Equals("PENDING") && !FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava.Equals("PENDING"))
	{
		bIsComplete = true;

		if(FFirebaseAuthSignInWithGoogle::ResultIdTokenJava.Equals("FAILURE") || FFirebaseAuthSignInWithGoogle::ResultServerAuthCode.Equals("FAILURE"))
		{
			bWasSuccessful = false;
		}
		else
		{
			bWasSuccessful = true;
			ResultIdToken = FFirebaseAuthSignInWithGoogle::ResultIdTokenJava;
			ResultServerAuthCode = FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava;
		}

		FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString("");
		FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString("");
	}
}

void FFirebaseAuthSignInWithGoogle::TriggerDelegates()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("FirebaseAuthSignInWithGoogle async task %s"), bWasSuccessful ? TEXT("finished succesfully") : TEXT("failed"));

	Delegate.ExecuteIfBound(bWasSuccessful, ResultIdToken, ResultServerAuthCode);
}

void FFirebaseAuthSignInWithGoogle::Finalize()
{
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION && PLATFORM_ANDROID
extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnGoogleSignIn(JNIEnv* jenv, jobject thiz, jstring idToken, jstring serverAuthCode)
{
	if (jenv)
	{
		const char* javaCharsIdToken = jenv->GetStringUTFChars(idToken, 0);
		const char* javaCharsServerAuthCode = jenv->GetStringUTFChars(serverAuthCode, 0);

		FFirebaseAuthSignInWithGoogle::ResultIdTokenJava = FString(UTF8_TO_TCHAR(javaCharsIdToken));
		FFirebaseAuthSignInWithGoogle::ResultServerAuthCodeJava = FString(UTF8_TO_TCHAR(javaCharsServerAuthCode));

		jenv->ReleaseStringUTFChars(idToken, javaCharsIdToken);
		jenv->ReleaseStringUTFChars(serverAuthCode, javaCharsServerAuthCode);
	}
}
#endif
