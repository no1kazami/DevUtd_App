// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalAccessUnit.generated.h"

/**
 * 
 */
UCLASS()
class BIGTAMIN_API UGlobalAccessUnit : public UObject
{
	GENERATED_BODY()
public:
	virtual void Startup() {}
	virtual void Shutdown()	{}
	virtual void LogOut() {}
	virtual void Tick( float deltaSeconds )	{}

	virtual void OnExitWorld() {}
	virtual void OnLoadedWorld() {}
};
