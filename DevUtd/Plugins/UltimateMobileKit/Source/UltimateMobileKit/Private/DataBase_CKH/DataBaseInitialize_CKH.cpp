// Fill out your copyright notice in the Description page of Project Settings.


#include "DataBase_CKH/DataBaseInitialize_CKH.h"
#include "UltimateMobileKit.h"
#include "UltimateMobileKitSettings.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
#include "firebase/database.h"
#include "firebase/util.h"
#include "firebase/future.h"
#endif


FFirebaseDataBaseInitialize_CKH::FFirebaseDataBaseInitialize_CKH( FUltimateMobileKit* InSubsystem, const FOnFirebaseDataBaseInitializeCompleteDelegate& InDelegate )
	: FOnlineAsyncTaskBasic( InSubsystem )
	, Delegate( InDelegate )
{

}

void FFirebaseDataBaseInitialize_CKH::Finalize()
{
	UE_LOG( LogUltimateMobileKit, Display, TEXT( "FirebaseDataBaseInitialize async task %s" ), bWasSuccessful ? TEXT( "finished succesfully" ) : TEXT( "failed" ) );

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if( UltimateMobileKit )
	{
		FFirebaseDataBasePtr FirebaseDataBase = UltimateMobileKit->GetFirebaseDataBase();

		if( FirebaseDataBase.IsValid() )
		{
			if( bWasSuccessful && FirebaseDataBase->RegisterService() )
			{
				FirebaseDataBase->SetInitialized( true );
			}
			else
			{
				FirebaseDataBase->SetInitialized( false );
			}
		}
	}
#endif
}

void FFirebaseDataBaseInitialize_CKH::TriggerDelegates()
{
	UE_LOG( LogUltimateMobileKit, Display, TEXT( "FirebaseDataBaseInitialize async task %s" ), bWasSuccessful ? TEXT( "finished succesfully" ) : TEXT( "failed" ) );
	Delegate.ExecuteIfBound( bWasSuccessful );
}

void FFirebaseDataBaseInitialize_CKH::Tick()
{
	if( !bInit )
	{
		Start_OnTaskThread();
		bInit = true;
	}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	firebase::Future<void> LastResult = Initializer.InitializeLastResult();
	if( LastResult.status() == firebase::kFutureStatusComplete )
	{
		if( LastResult.error() == 0 )
		{
			bWasSuccessful = true;
		}
		else
		{
			bWasSuccessful = false;
			UE_LOG( LogUltimateMobileKit, Error, TEXT( "FirebaseDataBaseInitialize Error: %s" ), *FString( LastResult.error_message() ) );
		}
		bIsComplete = true;
	}

	if( Initializer.InitializeLastResult().status() == firebase::kFutureStatusInvalid )
	{
		bWasSuccessful = false;
		bIsComplete = true;
	}
	LastResult.Release();
#endif
}

void FFirebaseDataBaseInitialize_CKH::Start_OnTaskThread()
{
	UE_LOG( LogUltimateMobileKit, Display, TEXT( "Executing FirebaseDataBaseInitialize async task..." ) );

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_DATABASE_CKH
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if( UltimateMobileKit )
	{
		FFirebaseAppPtr FirebaseApp = UltimateMobileKit->GetFirebaseApp();

		if( FirebaseApp.IsValid() && FirebaseApp->IsInitialized() )
		{
			FFirebaseNativeAppPtr NativeApp = FirebaseApp->GetFirebaseNativeApp();

			if( NativeApp.IsValid() )
			{
				Initializer.Initialize( NativeApp.Get(), nullptr, []( firebase::App* app, void* )
				{										
					firebase::InitResult init_result;
					firebase::database::Database::GetInstance( app, &init_result );
					return init_result;
				} );

				return;
			}
		}
	}
#endif

	bWasSuccessful = false;
	bIsComplete = true;
}
