// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "InstanceId/FirebaseInstanceId.h"
#include "InstanceId/InstanceIdInitialize.h"
#include "InstanceId/InstanceIdGetToken.h"
#include "InstanceId/InstanceIdGetId.h"
#include "InstanceId/InstanceIdDeleteToken.h"
#include "InstanceId/InstanceIdDeleteId.h"

FFirebaseInstanceId::FFirebaseInstanceId()
{
}

FFirebaseInstanceId::~FFirebaseInstanceId()
{
}

void FFirebaseInstanceId::Init(const FOnFirebaseInstanceIdInitializeCompleteDelegate& Delegate /*= FOnFirebaseInstanceIdInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true, EFirebaseInstanceIdError::None);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseInstanceIdInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false, EFirebaseInstanceIdError::Unknown);
}

void FFirebaseInstanceId::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Instance Id Shutdown"));
}

const bool FFirebaseInstanceId::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseInstanceId::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Instance Id is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Instance Id is not initialized"));
	}
}

const bool FFirebaseInstanceId::RegisterService()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FirebaseNativeInstanceIdPtr = MakeShareable(firebase::instance_id::InstanceId::GetInstanceId(UltimateMobileKit->GetFirebaseApp()->GetFirebaseNativeApp().Get()));

		if (FirebaseNativeInstanceIdPtr.IsValid())
		{
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Native Instance Id service registered"));

			return true;
		}
	}
#endif

	return false;
}

void FFirebaseInstanceId::GetToken(const FOnFirebaseInstanceIdGetTokenCompleteDelegate& Delegate /*= FOnFirebaseInstanceIdGetTokenCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInstanceIdGetToken(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseInstanceIdError::None, FString());
}

void FFirebaseInstanceId::GetId(const FOnFirebaseInstanceIdGetIdCompleteDelegate& Delegate /*= FOnFirebaseInstanceIdGetIdCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInstanceIdGetId(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseInstanceIdError::None, FString());
}

void FFirebaseInstanceId::DeleteToken(const FOnFirebaseInstanceIdDeleteTokenCompleteDelegate& Delegate /*= FOnFirebaseInstanceIdDeleteTokenCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInstanceIdDeleteToken(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseInstanceIdError::None);
}

void FFirebaseInstanceId::DeleteId(const FOnFirebaseInstanceIdDeleteIdCompleteDelegate& Delegate /*= FOnFirebaseInstanceIdDeleteIdCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseInstanceIdDeleteId(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseInstanceIdError::None);
}


#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_INSTANCEID
EFirebaseInstanceIdError FFirebaseInstanceId::FirebaseErrorFromNative(const firebase::instance_id::Error& NativeError)
{
	switch (NativeError)
	{
	case 0:
		return EFirebaseInstanceIdError::None;
	case firebase::instance_id::kErrorUnknown:
		return EFirebaseInstanceIdError::Unknown;
	case firebase::instance_id::kErrorAuthentication:
		return EFirebaseInstanceIdError::Authentication;
	case firebase::instance_id::kErrorNoAccess:
		return EFirebaseInstanceIdError::NoAccess;
	case firebase::instance_id::kErrorTimeout:
		return EFirebaseInstanceIdError::Timeout;
	case firebase::instance_id::kErrorNetwork:
		return EFirebaseInstanceIdError::Network;
	case firebase::instance_id::kErrorOperationInProgress:
		return EFirebaseInstanceIdError::OperationInProgress;
	case firebase::instance_id::kErrorInvalidRequest:
		return EFirebaseInstanceIdError::InvalidRequest;
	default:
		return EFirebaseInstanceIdError::Unknown;
	}
}
#endif
