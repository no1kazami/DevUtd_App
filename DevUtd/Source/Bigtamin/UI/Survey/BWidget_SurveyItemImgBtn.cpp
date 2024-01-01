// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SurveyItemImgBtn.h"
#include "Bigtamin.h"
#include "GameMode/BGameMode_main.h"
#include "BWidget_SurveyItem_Objective.h"
#include "BWidget_SurveyItem_Subjective.h"


void UBWidget_SurveyItemImgBtn::Init()
{
	Super::Init();

	if( C_CheckBox_1.IsValid() )
	{
		C_CheckBox_1.Get()->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged1 );
		C_CheckBox_1.Get()->OnCheckStateChanged.AddDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged1 );
	}
	if( C_CheckBox_2.IsValid() )
	{
		C_CheckBox_2.Get()->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged2 );
		C_CheckBox_2.Get()->OnCheckStateChanged.AddDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged2 );
	}
	if( C_CheckBox_3.IsValid() )
	{
		C_CheckBox_3.Get()->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged3 );
		C_CheckBox_3.Get()->OnCheckStateChanged.AddDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged3 );
	}
	if( C_CheckBox_4.IsValid() )
	{
		C_CheckBox_4.Get()->OnCheckStateChanged.RemoveDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged4 );
		C_CheckBox_4.Get()->OnCheckStateChanged.AddDynamic( this, &UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged4 );
	}

	_IsSuccess = false;
	_CurCheckIndex = 0;
}

void UBWidget_SurveyItemImgBtn::OnClose()
{
	Super::OnClose();
}

void UBWidget_SurveyItemImgBtn::_CheckOtherState()
{
	C_CheckBox_1->SetCheckedState(ECheckBoxState::Unchecked);
	C_CheckBox_2->SetCheckedState(ECheckBoxState::Unchecked);
	C_CheckBox_3->SetCheckedState(ECheckBoxState::Unchecked);
	C_CheckBox_4->SetCheckedState(ECheckBoxState::Unchecked);

	switch (_CurCheckIndex)
	{
	case 1:
		C_CheckBox_1->SetCheckedState(ECheckBoxState::Checked);
		break;
	case 2:
		C_CheckBox_2->SetCheckedState(ECheckBoxState::Checked);
		break;
	case 3:
		C_CheckBox_3->SetCheckedState(ECheckBoxState::Checked);
		break;
	case 4:
		C_CheckBox_4->SetCheckedState(ECheckBoxState::Checked);
		break;
	}
}

void UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged1( bool isChecked )
{
	if (isChecked)
	{
		_CurCheckIndex = 1;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}
}

void UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged2( bool isChecked )
{
	if (isChecked)
	{
		_CurCheckIndex = 2;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}

}

void UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged3( bool isChecked )
{
	if (isChecked)
	{
		_CurCheckIndex = 3;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}

}

void UBWidget_SurveyItemImgBtn::_OnSurveyCheckStateChanged4( bool isChecked )
{
	if (isChecked)
	{
		_CurCheckIndex = 4;
		_CheckOtherState();
	}
	else
	{
		_CurCheckIndex = 0;
	}

}

void UBWidget_SurveyItemImgBtn::SetCurSurveyItem( FST_SURVEY_INFO surveyInfo )
{
	Super::SetCurSurveyItem(surveyInfo);

	_SetTitleText();
	_SetSurveyItemExampleText();
	_SetSurveyItemImgTextureBG();
	_SetSurveyItemImgTextureIcon();

	if( C_Overlay_1.IsValid() )
		C_Overlay_1.Get()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	if( C_Overlay_2.IsValid() )
		C_Overlay_2.Get()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	if( C_Overlay_3.IsValid() )
		C_Overlay_3.Get()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
	if( C_Overlay_4.IsValid() )
		C_Overlay_4.Get()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );

	switch( _SurveyInfo.nExampleNum )
	{
	case 2:
		if( C_Overlay_3.IsValid() )
			C_Overlay_3.Get()->SetVisibility( ESlateVisibility::Collapsed );
		if( C_Overlay_4.IsValid() )
			C_Overlay_4.Get()->SetVisibility( ESlateVisibility::Collapsed );
		break;
	case 3:
		if( C_Overlay_4.IsValid() )
			C_Overlay_4.Get()->SetVisibility( ESlateVisibility::Collapsed );
		break;
	}
}

void UBWidget_SurveyItemImgBtn::_SetSurveyItemImgTextureBG()
{
	FString pathNormalString;
	FString pathDownString;

	if (_SurveyInfo.eSurveyType == E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_RECT_BTN)
	{
		pathNormalString = TEXT("Survey/Btn_Normal");
		pathDownString = TEXT("Survey/Btn_Down");
	}
	else
	{
		pathNormalString = TEXT("Survey/Btn_Circle_Normal");
		pathDownString = TEXT("Survey/Btn_Circle_Down");
	}

	UTexture2D* textureNolmal = GetTexture(pathNormalString);
	if (textureNolmal != nullptr)
	{
		FSlateBrush normalBrush;
		normalBrush.ImageSize.X = textureNolmal->GetSizeX();
		normalBrush.ImageSize.Y = textureNolmal->GetSizeY();
		normalBrush.SetResourceObject(textureNolmal);

		C_CheckBox_1->WidgetStyle.SetUncheckedImage(normalBrush);
		C_CheckBox_1->WidgetStyle.SetUncheckedPressedImage(normalBrush);
		C_CheckBox_1->WidgetStyle.SetUncheckedHoveredImage(normalBrush);

		C_CheckBox_2->WidgetStyle.SetUncheckedImage(normalBrush);
		C_CheckBox_2->WidgetStyle.SetUncheckedPressedImage(normalBrush);
		C_CheckBox_2->WidgetStyle.SetUncheckedHoveredImage(normalBrush);

		C_CheckBox_3->WidgetStyle.SetUncheckedImage(normalBrush);
		C_CheckBox_3->WidgetStyle.SetUncheckedPressedImage(normalBrush);
		C_CheckBox_3->WidgetStyle.SetUncheckedHoveredImage(normalBrush);

		C_CheckBox_4->WidgetStyle.SetUncheckedImage(normalBrush);
		C_CheckBox_4->WidgetStyle.SetUncheckedPressedImage(normalBrush);
		C_CheckBox_4->WidgetStyle.SetUncheckedHoveredImage(normalBrush);
	}

	UTexture2D* textureDown = GetTexture(pathDownString);
	if (textureDown != nullptr)
	{
		FSlateBrush downBrush;
		downBrush.ImageSize.X = textureDown->GetSizeX();
		downBrush.ImageSize.Y = textureDown->GetSizeY();
		downBrush.SetResourceObject(textureDown);

		C_CheckBox_1->WidgetStyle.SetCheckedImage(downBrush);
		C_CheckBox_1->WidgetStyle.SetCheckedPressedImage(downBrush);
		C_CheckBox_1->WidgetStyle.SetCheckedHoveredImage(downBrush);

		C_CheckBox_2->WidgetStyle.SetCheckedImage(downBrush);
		C_CheckBox_2->WidgetStyle.SetCheckedPressedImage(downBrush);
		C_CheckBox_2->WidgetStyle.SetCheckedHoveredImage(downBrush);

		C_CheckBox_3->WidgetStyle.SetCheckedImage(downBrush);
		C_CheckBox_3->WidgetStyle.SetCheckedPressedImage(downBrush);
		C_CheckBox_3->WidgetStyle.SetCheckedHoveredImage(downBrush);

		C_CheckBox_4->WidgetStyle.SetCheckedImage(downBrush);
		C_CheckBox_4->WidgetStyle.SetCheckedPressedImage(downBrush);
		C_CheckBox_4->WidgetStyle.SetCheckedHoveredImage(downBrush);
	}
}

void UBWidget_SurveyItemImgBtn::_SetSurveyItemImgTextureIcon()
{
	UTexture2D* textureIcon;

	for (int32 index = 0; index < _SurveyInfo.arExampleBtnAddress.Num(); index++)
	{
		textureIcon = GetTexture(_SurveyInfo.arExampleBtnAddress[index]);
		if (textureIcon != nullptr)
		{
			if (index == 0)
			{
				C_Img_1->SetBrushFromTexture(textureIcon, true);
			}
			else if (index == 1)
			{
				C_Img_2->SetBrushFromTexture(textureIcon, true);
			}
			else if (index == 2)
			{
				C_Img_3->SetBrushFromTexture(textureIcon, true);
			}
			else if (index == 3)
			{
				C_Img_4->SetBrushFromTexture(textureIcon, true);
			}
		}
		else
		{
			if (index == 0)
			{
				C_Img_1->SetVisibility(ESlateVisibility::Hidden);
			}
			else if (index == 1)
			{
				C_Img_2->SetVisibility(ESlateVisibility::Hidden);
			}
			else if (index == 2)
			{
				C_Img_3->SetVisibility(ESlateVisibility::Hidden);
			}
			else if (index == 3)
			{
				C_Img_4->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UBWidget_SurveyItemImgBtn::_SetSurveyItemExampleText()
{
	for (int32 index = 0; index < _SurveyInfo.arExampleBtnText.Num(); index++)
	{
		if (index == 0 && C_Txt_Example_1.IsValid())
		{
			C_Txt_Example_1.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
			C_Txt_Example_1.Get()->SetVisibility(ESlateVisibility::Visible);
		}
		else if (index == 1 && C_Txt_Example_2.IsValid())
		{
			C_Txt_Example_2.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
			C_Txt_Example_2.Get()->SetVisibility(ESlateVisibility::Visible);
		}
		else if (index == 2 && C_Txt_Example_3.IsValid())
		{
			C_Txt_Example_3.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
			C_Txt_Example_3.Get()->SetVisibility(ESlateVisibility::Visible);
		}
		else if (index == 3 && C_Txt_Example_4.IsValid())
		{
			C_Txt_Example_4.Get()->SetText(FText::FromString(_SurveyInfo.arExampleBtnText[index]));
			C_Txt_Example_4.Get()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
