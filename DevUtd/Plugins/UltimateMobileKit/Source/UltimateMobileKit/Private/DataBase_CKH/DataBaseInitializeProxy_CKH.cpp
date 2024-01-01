// Fill out your copyright notice in the Description page of Project Settings.


#include "DataBase_CKH/DataBaseInitializeProxy_CKH.h"
#include "UltimateMobileKit.h"

UFirebaseDataBaseInitializeProxy_CKH::UFirebaseDataBaseInitializeProxy_CKH( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
}

UFirebaseDataBaseInitializeProxy_CKH* UFirebaseDataBaseInitializeProxy_CKH::Init()
{
	UFirebaseDataBaseInitializeProxy_CKH* Proxy = NewObject<UFirebaseDataBaseInitializeProxy_CKH>();
	return Proxy;
}

void UFirebaseDataBaseInitializeProxy_CKH::Activate()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if( UltimateMobileKit )
	{
		FFirebaseDataBasePtr FirebaseDataBase = UltimateMobileKit->GetFirebaseDataBase();

		if( FirebaseDataBase.IsValid() )
		{
			FOnFirebaseDataBaseInitializeCompleteDelegate InitializeCompleteDelegate = FOnFirebaseDataBaseInitializeCompleteDelegate::CreateUObject( this, &ThisClass::OnQueryCompleted );

			FirebaseDataBase->Init( InitializeCompleteDelegate );

			return;
		}
	}

	OnFailure.Broadcast();
}

void UFirebaseDataBaseInitializeProxy_CKH::OnQueryCompleted( bool bSuccess )
{
	if( bSuccess )
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
}
