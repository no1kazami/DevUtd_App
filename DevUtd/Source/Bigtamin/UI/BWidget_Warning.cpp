// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_Warning.h"


void UBWidget_Warning::Init()
{
	Super::Init();

	_Ani_Warning = GetWidgetAnimation( _Ani_WarningName );
}

void UBWidget_Warning::OnClose()
{

}

bool UBWidget_Warning::PlayWarning( int32 warningIndex )
{
	C_Txt_Warning->SetText( GET_BTEXT( warningIndex ) );

	if( _Ani_Warning != nullptr )
	{
		if( IsAnimationPlaying( _Ani_Warning ) )
		{
			if (_CurWarningIndex == warningIndex)
			{
				return false;
			}

			StopAnimation( _Ani_Warning );
		}

		PlayAnimation( _Ani_Warning );
		_CurWarningIndex = warningIndex;
		return true;
	}

	return false;
}
