// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItem_Subjective.h"
#include "Bigtamin.h"
#include "BWidget_SurveyItemImgBtn.h"

void UBWidget_SurveyItem_Subjective::Init()
{
	Super::Init();

	if( C_EditText_Answer.IsValid() )
	{
		C_EditText_Answer.Get()->OnTextChanged.RemoveDynamic( this, &UBWidget_SurveyItem_Subjective::OnTextAnswerChanged );
		C_EditText_Answer.Get()->OnTextChanged.AddDynamic( this, &UBWidget_SurveyItem_Subjective::OnTextAnswerChanged );
	}
}

void UBWidget_SurveyItem_Subjective::OnClose()
{

}

void UBWidget_SurveyItem_Subjective::SetSurveyItemDetail( int32 nIndex )
{
	if( C_EditText_Answer.IsValid() )
	{
		FText txtHint = GET_BTEXT( nIndex );
		C_EditText_Answer.Get()->SetHintText( txtHint );
	}
}

bool UBWidget_SurveyItem_Subjective::CheckState()
{
	bool isEmpty = false;
	if( C_EditText_Answer.IsValid() )
	{
		isEmpty = C_EditText_Answer.Get()->GetText().IsEmpty();
		if( isEmpty && C_Img_BG.IsValid() )
		{
			FLinearColor linerColor;
			linerColor.R = 1.f;
			linerColor.G = 0.f;
			linerColor.B = 0.f;
			linerColor.A = 1.f;
			FSlateColor slateColor( linerColor );
			C_Img_BG.Get()->SetBrushTintColor( slateColor );
		}		
	}

	return !isEmpty;
}

void UBWidget_SurveyItem_Subjective::OnTextAnswerChanged( const FText& InText )
{
	bool isEmpty = InText.IsEmpty();

	if( !isEmpty && C_Img_BG.IsValid() )
	{
		FLinearColor linerColor;
		linerColor.R = 1.f;
		linerColor.G = 1.f;
		linerColor.B = 1.f;
		linerColor.A = 1.f;
		FSlateColor slateColor( linerColor );
		C_Img_BG.Get()->SetBrushTintColor( slateColor );
	}

	if( OwnerPannel )
	{
		if(UBWidget_SurveyItemImgBtn* ownerSurveyItem = Cast<UBWidget_SurveyItemImgBtn>( OwnerPannel ) )
		{
//			ownerSurveyItem->SetVisibleTextError( isEmpty );
		}
	}
}
