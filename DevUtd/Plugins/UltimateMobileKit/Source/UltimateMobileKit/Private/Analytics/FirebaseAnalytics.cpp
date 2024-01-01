// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Analytics/FirebaseAnalytics.h"
#include "UltimateMobileKitSettings.h"
#include "UltimateMobileKit.h"
#include "Analytics/AnalyticsInitialize.h"
#include "Analytics/AnalyticsGetAnalyticsInstanceId.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS && PLATFORM_IOS
#import <FirebaseAnalytics/FIRAnalytics.h>
#endif

FFirebaseAnalytics::FFirebaseAnalytics()
{	
}

FFirebaseAnalytics::~FFirebaseAnalytics()
{
}

void FFirebaseAnalytics::Init(const FOnFirebaseAnalyticsInitializeCompleteDelegate& Delegate /*= FOnFirebaseAnalyticsInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseAnalyticsInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false);
}

void FFirebaseAnalytics::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Analytics Shutdown"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	firebase::analytics::Terminate();
#endif
}

const bool FFirebaseAnalytics::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseAnalytics::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Analytics is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Analytics is not initialized"));
	}
}

void FFirebaseAnalytics::LogEvent(const FString& Name, const TArray<UFirebaseVariant*> Parameters) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		if (Parameters.Num() == 0)
		{
			firebase::analytics::LogEvent(TCHAR_TO_UTF8(*Name));

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Log Event: %s"), *Name);
		}
		else
		{
			firebase::analytics::Parameter* NativeParameters = new firebase::analytics::Parameter[Parameters.Num()];
			std::string* EventNamesRaw = new std::string[Parameters.Num()];
			std::string* EventValuesRaw = new std::string[Parameters.Num()];

			FString ParametersString;

			for (int i = 0; i < Parameters.Num(); i++)
			{
				if (Parameters[i]->GetType() == EFirebaseVariantType::String)
				{
					EventNamesRaw[i] = std::string(TCHAR_TO_UTF8(*Parameters[i]->GetName()));
					EventValuesRaw[i] = std::string(TCHAR_TO_UTF8(*Parameters[i]->GetStringVariant()));

					NativeParameters[i] = firebase::analytics::Parameter(EventNamesRaw[i].c_str(), EventValuesRaw[i].c_str());
					ParametersString += "(" + Parameters[i]->GetName() + ":" + Parameters[i]->GetStringVariant() + ")";
				}
				else if (Parameters[i]->GetType() == EFirebaseVariantType::Integer)
				{
					EventNamesRaw[i] = std::string(TCHAR_TO_UTF8(*Parameters[i]->GetName()));

					NativeParameters[i] = firebase::analytics::Parameter(EventNamesRaw[i].c_str(), Parameters[i]->GetIntegerVariant());
					ParametersString += "(" + Parameters[i]->GetName() + ":" + FString::FromInt(Parameters[i]->GetIntegerVariant()) + ")";
				}
				else if (Parameters[i]->GetType() == EFirebaseVariantType::Boolean)
				{
					EventNamesRaw[i] = std::string(TCHAR_TO_UTF8(*Parameters[i]->GetName()));

					NativeParameters[i] = firebase::analytics::Parameter(EventNamesRaw[i].c_str(), Parameters[i]->GetBooleanVariant());
					ParametersString += "(" + Parameters[i]->GetName() + ":" + (Parameters[i]->GetBooleanVariant() ? "true" : "false") + ")";
				}
				else if (Parameters[i]->GetType() == EFirebaseVariantType::Float)
				{
					EventNamesRaw[i] = std::string(TCHAR_TO_UTF8(*Parameters[i]->GetName()));

					NativeParameters[i] = firebase::analytics::Parameter(EventNamesRaw[i].c_str(), Parameters[i]->GetFloatVariant());
					ParametersString += "(" + Parameters[i]->GetName() + ":" + FString::SanitizeFloat(Parameters[i]->GetFloatVariant()) + ")";
				}
			}

			firebase::analytics::LogEvent(TCHAR_TO_UTF8(*Name), NativeParameters, Parameters.Num());

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Log Event: %s, Parameters: %s"), *Name, *ParametersString);

			delete[] EventNamesRaw;
			EventNamesRaw = NULL;
			delete[] EventValuesRaw;
			EventValuesRaw = NULL;
			delete[] NativeParameters;
			NativeParameters = NULL;
		}
	}
#endif
}

void FFirebaseAnalytics::LogEventString(const FString& Name, const FString& ParameterName, const FString& ParameterValue) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Log Event String: %s, Parameter: (%s:%s)"), *Name, *ParameterName, *ParameterValue);

		firebase::analytics::LogEvent(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ParameterName), TCHAR_TO_UTF8(*ParameterValue));
	}
#endif
}

void FFirebaseAnalytics::LogEventInteger(const FString& Name, const FString& ParameterName, const int32 ParameterValue) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Log Event Integer: %s, Parameter: (%s:%d)"), *Name, *ParameterName, ParameterValue);

		firebase::analytics::LogEvent(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ParameterName), ParameterValue);
	}
#endif
}

void FFirebaseAnalytics::LogEventFloat(const FString& Name, const FString& ParameterName, const float ParameterValue) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Log Event Float: %s, Parameter: (%s:%s)"), *Name, *ParameterName, *FString::SanitizeFloat(ParameterValue));

		firebase::analytics::LogEvent(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*ParameterName), ParameterValue);
	}
#endif
}

void FFirebaseAnalytics::SetUserId(const FString& UserId) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Set User Id: %s"), *UserId);

		firebase::analytics::SetUserId(TCHAR_TO_UTF8(*UserId));
	}
#endif
}

void FFirebaseAnalytics::SetUserProperty(const FString& Name, const FString& Property) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Set User Property. Name: %s, Property: %s"), *Name, *Property);

		firebase::analytics::SetUserProperty(TCHAR_TO_UTF8(*Name), TCHAR_TO_UTF8(*Property));
	}
#endif
}

void FFirebaseAnalytics::SetCurrentScreen(const FString& ScreenName, const FString& ScreenClass) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		FString FinalScreenName = ScreenName;
		FString FinalScreenClass = ScreenClass;

		UE_LOG(LogUltimateMobileKit, Display, TEXT("Set Current Screen. Name: %s, Class: %s"), *FinalScreenName, *FinalScreenClass);

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^ {
		[FIRAnalytics setScreenName : FinalScreenName.GetNSString() screenClass : FinalScreenClass.GetNSString()] ;
	});
#else
	firebase::analytics::SetCurrentScreen(TCHAR_TO_UTF8(*FinalScreenName), TCHAR_TO_UTF8(*FinalScreenClass));
#endif
	}
#endif
}

void FFirebaseAnalytics::ResetAnalyticsData() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Analytics Reset Analytics Data"));

		firebase::analytics::ResetAnalyticsData();
	}
#endif
}

void FFirebaseAnalytics::SetAnalyticsCollectionEnabled(bool bEnabled) const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_ANALYTICS
	if (IsInitialized())
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Analytics Set Analytics Collection Enabled: %d"), bEnabled);

		firebase::analytics::SetAnalyticsCollectionEnabled(bEnabled);
	}
#endif
}

void FFirebaseAnalytics::GetAnalyticsInstanceId(const FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate& Delegate /*= FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate()*/) const
{	
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAnalyticsGetAnalyticsInstanceId(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FString());
}
