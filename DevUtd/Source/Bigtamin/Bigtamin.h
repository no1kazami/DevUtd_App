// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#if UE_BUILD_SHIPPING
//BIGTAMIN_API DECLARE_LOG_CATEGORY_EXTERN( LogFBM, Log, NoLogging );
BIGTAMIN_API DECLARE_LOG_CATEGORY_EXTERN( LogFBM, Log, Warning );
#else
BIGTAMIN_API DECLARE_LOG_CATEGORY_EXTERN( LogFBM, Log, All );
#endif

#define FBM_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define FBM_LOG_FUNCTION_INFO_ONLY(Verbosity) UE_LOG(LogFBM, Verbosity, TEXT("%s"), *FBM_LOG_CALLINFO)
#define FBM_LOG_FUNCTION_INFO(Verbosity, Format, ...) UE_LOG(LogFBM, Verbosity, TEXT("%s %s"), *FBM_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) 

//#include "CoreMinimal.h"

// Base
#include "Util/BGlobalAccess.h"
#include "Util/Bigtamin_Enum.h"
//#include "Util/Bigtamin_Struct.h"
#include "Util/FBMUtil.h"

#include "UI/Base/BHUDBase.h"