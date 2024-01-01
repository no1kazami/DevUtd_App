// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalAccessMgr.generated.h"

class UGlobalAccessUnit;

UCLASS()
class BIGTAMIN_API UGlobalAccessMgr : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		TMap<UClass*, UGlobalAccessUnit*> _GlobalAccessUnits;

public:
	void Startup();
	void Shutdown();
	void LogOut();

	void OnLoadedWorld();
	void OnExitWorld();

	void Tick( float deltaSeconds );

	template<class T>
	T* Get() const;

protected:
	template<class T>
	T* _Create();
};

template<class T>
T* UGlobalAccessMgr::Get() const
{
	if( !_GlobalAccessUnits.Contains( T::StaticClass() ) )
		return nullptr;

	return Cast<T>( _GlobalAccessUnits[T::StaticClass()] );
}

template<class T>
T* UGlobalAccessMgr::_Create()
{
	_GlobalAccessUnits.Emplace( T::StaticClass(), NewObject<T>( this ) );

	return Cast<T>( _GlobalAccessUnits[T::StaticClass()] );
}