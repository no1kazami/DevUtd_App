// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Performance/FirebaseTrace.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_IOS
#import <FirebasePerformance/FirebasePerformance.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING && PLATFORM_ANDROID
void AndroidThunkCpp_FirebaseStartPerformanceTrace(const FString& TraceName)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseStartPerformanceTrace", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal);
		Env->DeleteLocalRef(TraceNameFinal);
	}
}

void AndroidThunkCpp_FirebaseStopPerformanceTrace(const FString& TraceName)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseStopPerformanceTrace", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal);
		Env->DeleteLocalRef(TraceNameFinal);
	}
}

void AndroidThunkCpp_FirebaseIncrementPerformanceTraceMetric(const FString& TraceName, const FString& MetricName, int32 IncrementValue)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring MetricNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*MetricName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseIncrementPerformanceTraceMetric", "(Ljava/lang/String;Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, MetricNameFinal, IncrementValue);
		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(MetricNameFinal);
	}
}

void AndroidThunkCpp_FirebasePutPerformanceTraceMetric(const FString& TraceName, const FString& MetricName, int32 Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring MetricNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*MetricName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebasePutPerformanceTraceMetric", "(Ljava/lang/String;Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, MetricNameFinal, Value);
		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(MetricNameFinal);
	}
}

int64 AndroidThunkCpp_FirebaseGetPerformanceTraceMetric(const FString& TraceName, const FString& MetricName)
{
	int64 Result = 0;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring MetricNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*MetricName));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseGetPerformanceTraceMetric", "(Ljava/lang/String;Ljava/lang/String;)J", false);
		Result = (int64) FJavaWrapper::CallLongMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, MetricNameFinal);
		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(MetricNameFinal);
	}
	return Result;
}

void AndroidThunkCpp_FirebasePutPerformanceTraceAttribute(const FString& TraceName, const FString& Attribute, const FString& Value)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring AttributeFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Attribute));
		jstring ValueFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Value));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebasePutPerformanceTraceAttribute", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, AttributeFinal, ValueFinal);
		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(AttributeFinal);
		Env->DeleteLocalRef(ValueFinal);
	}
}

void AndroidThunkCpp_FirebaseRemovePerformanceTraceAttribute(const FString& TraceName, const FString& Attribute)
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring AttributeFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Attribute));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseRemovePerformanceTraceAttribute", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, AttributeFinal);
		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(AttributeFinal);
	}
}

FString AndroidThunkCpp_FirebaseGetPerformanceTraceAttribute(const FString& TraceName, const FString& Attribute)
{
	FString Result = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring TraceNameFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*TraceName));
		jstring AttributeFinal = Env->NewStringUTF(TCHAR_TO_UTF8(*Attribute));
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_FirebaseGetPerformanceTraceAttribute", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", false);
		jstring AttributeValue = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method, TraceNameFinal, AttributeFinal);

		if (AttributeValue != NULL)
		{
			const char* AttributeValueChars = Env->GetStringUTFChars(AttributeValue, 0);
			Result = FString(UTF8_TO_TCHAR(AttributeValueChars));
			Env->ReleaseStringUTFChars(AttributeValue, AttributeValueChars);
			Env->DeleteLocalRef(AttributeValue);
		}

		Env->DeleteLocalRef(TraceNameFinal);
		Env->DeleteLocalRef(AttributeFinal);
	}
	return Result;
}
#endif

UFirebaseTrace::UFirebaseTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceName = FString();
}

UFirebaseTrace* UFirebaseTrace::StartPerformanceTrace(const FString& Name)
{
	UFirebaseTrace* UltimateMobileKitTrace = NewObject<UFirebaseTrace>();
	UltimateMobileKitTrace->TraceName = Name;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject : Name.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[Name.GetNSString()];
					if (Trace)
					{
						[Trace stop];
					}
				}

				TraceDictionary[Name.GetNSString()] = [FIRPerformance startTraceWithName : Name.GetNSString()];
				UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Start Trace: %s"), *Name);
			}
#elif PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseStartPerformanceTrace(Name);
#endif
		}
	}
#endif

	return UltimateMobileKitTrace;
}

void UFirebaseTrace::Stop() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						[Trace stop];
						[TraceDictionary removeObjectForKey : TraceName.GetNSString()];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Stop Trace: %s"), *TraceName);
						return;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseStopPerformanceTrace(TraceName);
#endif
		}
	}
#endif
}

void UFirebaseTrace::IncrementMetric(const FString& MetricName, int32 IncrementValue) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						[Trace incrementMetric:MetricName.GetNSString() byInt : IncrementValue];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Increment Metric: %s, Metric Name: %s, Increment Value: %d"), *TraceName, *MetricName, IncrementValue);
						return;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
	AndroidThunkCpp_FirebaseIncrementPerformanceTraceMetric(TraceName, MetricName, IncrementValue);
#endif
		}
	}
#endif
}

void UFirebaseTrace::PutMetric(const FString& MetricName, int32 Value) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						[Trace setIntValue : Value forMetric: MetricName.GetNSString()];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Put Metric: %s, Metric Name: %s, Value: %d"), *TraceName, *MetricName, Value);
						return;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
			AndroidThunkCpp_FirebasePutPerformanceTraceMetric(TraceName, MetricName, Value);
#endif
		}
	}
#endif
}

const int32 UFirebaseTrace::GetMetric(const FString& MetricName) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						int32 MetricValue = (int32) ([Trace valueForIntMetric : MetricName.GetNSString()]);
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Get Metric: %s, Metric Name: %s, Value: %d"), *TraceName, *MetricName, MetricValue);
						return MetricValue;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
			return AndroidThunkCpp_FirebaseGetPerformanceTraceMetric(TraceName, MetricName);
#endif
		}
	}
#endif

	return 0;
}

void UFirebaseTrace::PutAttribute(const FString& Attribute, const FString& Value) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						[Trace setValue : Value.GetNSString() forAttribute : Attribute.GetNSString()];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Put Attribute: %s, Attribute: %s, Value: %s"), *TraceName, *Attribute, *Value);
						return;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
			AndroidThunkCpp_FirebasePutPerformanceTraceAttribute(TraceName, Attribute, Value);
#endif
		}
	}
#endif
}

void UFirebaseTrace::RemoveAttribute(const FString& Attribute) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						[Trace removeAttribute : Attribute.GetNSString()];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Remove Attribute: %s, Attribute: %s"), *TraceName, *Attribute);
						return;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
			AndroidThunkCpp_FirebaseRemovePerformanceTraceAttribute(TraceName, Attribute);
#endif
		}
	}
#endif
}

const FString UFirebaseTrace::GetAttribute(const FString& Attribute) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebasePerformancePtr FirebasePerformance = UltimateMobileKit->GetFirebasePerformance();
		if (FirebasePerformance.IsValid() && FirebasePerformance->IsInitialized())
		{
#if PLATFORM_IOS
			NSMutableDictionary* TraceDictionary = FirebasePerformance->GetTraceDictionary();
			if (TraceDictionary)
			{
				if ([[TraceDictionary allKeys] containsObject:TraceName.GetNSString()])
				{
					FIRTrace* Trace = TraceDictionary[TraceName.GetNSString()];
					if (Trace)
					{
						FString AttributeValue = [Trace valueForAttribute : Attribute.GetNSString()];
						UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Get Attribute: %s, Attribute: %s, Value: %s"), *TraceName, *Attribute, *AttributeValue);
						return AttributeValue;
					}
				}
			}
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Performance Monitoring Trace not initialized: %s"), *TraceName);
#elif PLATFORM_ANDROID
			return AndroidThunkCpp_FirebaseGetPerformanceTraceAttribute(TraceName, Attribute);
#endif
		}
	}
#endif

	return FString();
}
