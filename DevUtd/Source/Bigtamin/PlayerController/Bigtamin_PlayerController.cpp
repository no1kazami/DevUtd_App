// Fill out your copyright notice in the Description page of Project Settings.

#include "Bigtamin_PlayerController.h"


void ABigtamin_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//_BootsDetailUMG = nullptr;
	_NewMainlUMG = nullptr;
}

bool ABigtamin_PlayerController::InputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex )
{
	_SwipeScrollWidgetInputTouch( Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);

	bool bResult = Super::InputTouch( Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex );
	return bResult;
}

void ABigtamin_PlayerController::BackKeyInput()
{
	GInst->BackInput();
}

void ABigtamin_PlayerController::_SwipeScrollWidgetInputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex )
{
	switch( GInst->GetCurMode() )
	{
	case E_MODE::E_MODE_MAIN:
		{
			if( _NewMainlUMG == nullptr )
			{
				_NewMainlUMG = B_HUD->GetWidgetInViewport<UBWidget_NewMain>( EBUIName::Main );
			}

			if( _NewMainlUMG != nullptr && _NewMainlUMG->IsVisible() )
			{
				_NewMainlUMG->Swipe_InputTouch( Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex );
			}
		}
		break;
		/*
	case E_MODE::E_MODE_BOOTS_DETAIL:
		{
			if( _BootsDetailUMG == nullptr )
			{
				_BootsDetailUMG = B_HUD->GetWidgetInViewport<UBWidget_BootsDetail>( EBUIName::BootsDetail );
			}

			if( _BootsDetailUMG != nullptr && _BootsDetailUMG->IsVisible() )
			{
				_BootsDetailUMG->Swipe_InputTouch( Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex );
			}
		}
		break;
		*/
	default:
		break;
	}
}
