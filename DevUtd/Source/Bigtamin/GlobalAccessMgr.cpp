// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalAccessMgr.h"
#include "Firebase/FireBaseManager.h"

void UGlobalAccessMgr::Startup()
{
	_Create<UFireBaseManager>()->Startup();
}

void UGlobalAccessMgr::Shutdown()
{
	for( const auto& pair : _GlobalAccessUnits )
	{
		pair.Value->Shutdown();
	}
}

void UGlobalAccessMgr::LogOut()
{
	for( const auto& pair : _GlobalAccessUnits )
	{
		pair.Value->LogOut();
	}
}

void UGlobalAccessMgr::OnExitWorld()
{
	for( const auto& pair : _GlobalAccessUnits )
	{
		pair.Value->OnExitWorld();
	}
}

void UGlobalAccessMgr::OnLoadedWorld()
{
	for( const auto& pair : _GlobalAccessUnits )
	{
		pair.Value->OnLoadedWorld();
	}
}

void UGlobalAccessMgr::Tick( float deltaSeconds )
{
	for( const auto& pair : _GlobalAccessUnits )
	{
		pair.Value->Tick( deltaSeconds );
	}
}