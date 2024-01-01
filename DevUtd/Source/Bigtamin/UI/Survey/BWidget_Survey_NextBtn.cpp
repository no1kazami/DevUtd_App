// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_Survey_NextBtn.h"
#include "BWidget_Survey.h"
#include "Bigtamin.h"


void UBWidget_Survey_NextBtn::Init()
{
	Super::Init();

	if (C_Btn_Next.IsValid())
		ButtonDelegate_Clicked(this, C_Btn_Next.Get(), &UBWidget_Survey_NextBtn::_OnClickNextBtn);

	FText txtNext = GET_BTEXT(14);
	SetBtnText(txtNext);

	if( C_Text_Error.IsValid() )
	{
		FText txtError = GET_BTEXT( 18 );
		C_Text_Error.Get()->SetText( txtError );
		C_Text_Error.Get()->SetVisibility( ESlateVisibility::Hidden );
	}

	_IsCheckSurvey = false;
	_CheckSurveyTime = 0.5f;
	_CurCheckSurveyTime = 0.f;
}

void UBWidget_Survey_NextBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_Survey_NextBtn::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
{
	Super::NativeTick( MyGeometry, InDeltaTime );

	if( _IsCheckSurvey )
	{
		_CurCheckSurveyTime += InDeltaTime;
		if( _CurCheckSurveyTime > _CheckSurveyTime )
		{
			if( UBWidget_Survey* ownerSurvey = Cast<UBWidget_Survey>( OwnerPannel ) )
			{
				if( ownerSurvey->CheckSurveyPage() )
				{
					if( C_Text_Error.IsValid() )
					{
						C_Text_Error.Get()->SetVisibility( ESlateVisibility::Hidden );
						_IsCheckSurvey = false;
						_CurCheckSurveyTime = 0.f;
					}
				}
			}
		}
	}
}

void UBWidget_Survey_NextBtn::SetBtnText(FText btnText)
{
	if (C_Text_Next.IsValid())
		C_Text_Next.Get()->SetText(btnText);
}

void UBWidget_Survey_NextBtn::_OnClickNextBtn()
{
	if (UBWidget_Survey* ownerSurvey = Cast<UBWidget_Survey>(OwnerPannel))
	{
		bool isSuccess = ownerSurvey->OnClickNextBtn();
		if (isSuccess == false)
		{
			_IsCheckSurvey = true;
			if( C_Text_Error.IsValid() )
			{
				C_Text_Error.Get()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
			}
		}
		else
		{
			_IsCheckSurvey = false;
		}
	}
}
