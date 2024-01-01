// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "DataBaseInitializeProxy_CKH.generated.h"


UCLASS( MinimalAPI )
class UFirebaseDataBaseInitializeProxy_CKH : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	UPROPERTY( BlueprintAssignable )
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY( BlueprintAssignable )
	FEmptyOnlineDelegate OnFailure;

	/** Initialize the Firebase Config API  */
	UFUNCTION( BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Ultimate Mobile Kit|DataBase", DisplayName = "Firebase DataBase Init" )
	static UFirebaseDataBaseInitializeProxy_CKH* Init();

	virtual void Activate() override;

private:
	void OnQueryCompleted( bool bSuccess );
	
};
