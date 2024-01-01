// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItem_Objective.h"
#include "Bigtamin.h"
#include "BWidget_SurveyItemImgBtn.h"

void UBWidget_SurveyItem_Objective::Init()
{
	Super::Init();

	if( C_CheckBox_Survey.IsValid() )
	{
		C_CheckBox_Survey.Get()->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_SurveyItem_Objective::OnSurveyCheckStateChanged );
		C_CheckBox_Survey.Get()->OnCheckStateChanged.AddDynamic( this, &UBWidget_SurveyItem_Objective::OnSurveyCheckStateChanged );
	}
}

void UBWidget_SurveyItem_Objective::OnClose()
{

}

void UBWidget_SurveyItem_Objective::SetSurveyCheckBox( ECheckBoxState state )
{
	if( C_CheckBox_Survey.IsValid() )
	{
		C_CheckBox_Survey.Get()->SetCheckedState( state );
	}
}

bool UBWidget_SurveyItem_Objective::IsSurveyChecked()
{
	bool bIsChecked = false;

	if( C_CheckBox_Survey.IsValid() )
	{
		bIsChecked = C_CheckBox_Survey.Get()->IsChecked();
	}

	return bIsChecked;
}

void UBWidget_SurveyItem_Objective::SetSurveyItemDetail( int32 nIndex, int32 nType, E_SURVEY_TYPE eType )
{
	_ElementIndex = nIndex;
	_SurveyType = eType;

	if( C_Txt_Name.IsValid() )
	{
		FText txtName = GET_BTEXT( _ElementIndex );
		C_Txt_Name.Get()->SetText( txtName );
	}

	FString pathString;
	switch ( nType )
	{
	case 0:
		pathString = TEXT( "Survey/Top_Only" );
		break;
	case 1:
		pathString = TEXT( "Survey/Center" );
		break;
	case 2:
		pathString = TEXT( "Survey/Down" );
		break;
	}

	UTexture2D* textureBG = GetTexture( pathString );
	if( C_Img_BG.IsValid() && textureBG )
	{
		FSlateBrush brush;
		brush.ImageSize.X = 32.f;
		brush.ImageSize.Y = 32.f;
		brush.SetResourceObject( textureBG );
		C_Img_BG.Get()->SetBrush( brush );
	}
}

void UBWidget_SurveyItem_Objective::OnSurveyCheckStateChanged( bool isChecked )
{
	/*
	if( OwnerPannel )
	{
		if(UBWidget_SurveyItemImgBtn* ownerSurveyItem = Cast<UBWidget_SurveyItemImgBtn>( OwnerPannel ) )
		{
			ownerSurveyItem->CheckBoxSurveyState( _ElementIndex, isChecked, _SurveyType );
		}
	}
	*/
}
