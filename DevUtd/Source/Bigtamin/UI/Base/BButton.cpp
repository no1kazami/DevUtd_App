// Fill out your copyright notice in the Description page of Project Settings.

#include "BButton.h"
#include "Bigtamin.h"
#include "UI/Base/BWidget.h"

#define LOCTEXT_NAMESPACE "UMG"


UBButton::UBButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ButtonPressSound = 0;
}

UBButton::~UBButton()
{

}

void UBButton::PostLoad()
{
	Super::PostLoad();

	NormalStyle = WidgetStyle.Normal;
	PressedStyle = WidgetStyle.Pressed;
	DisabledStyle = WidgetStyle.Disabled;

	IsFocusable = false;
}

void UBButton::RegistDefaultPressSound()
{
	OnPressed.AddUniqueDynamic(this, &UBButton::OnPlayPressSound);
}

void UBButton::UnregistDefaultPressSound()
{
	OnPressed.RemoveDynamic(this, &UBButton::OnPlayPressSound);
}

void UBButton::OnPlayPressSound()
{
	/*
	UWorld* world = GetWorld();
	if (world)
	{
		//static const FString name = TEXT("Ui/Ui_Sound_Sfx_01_Cue");
		//UGGameStatics::PlaySound2D(world, name, 0.f, false);
	}
	*/
}

void UBButton::SetDelegate()
{
	ButtonDelegate_Pressed(this, this, &UBButton::_OnPressed);
	ButtonDelegate_Released(this, this, &UBButton::_OnReleased);
	ButtonDelegate_Clicked(this, this, &UBButton::_OnClicked);
}

void UBButton::_OnPressed()
{
	if (OnGPressed.IsBound())
		OnGPressed.Broadcast(this);

	if (SubIconStateNormal.IsValid())
		SubIconStateNormal.Get()->SetVisibility(ESlateVisibility::Hidden);

	if (SubIconStatePressed.IsValid())
		SubIconStatePressed.Get()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBButton::_OnReleased()
{
	if (OnGReleased.IsBound())
		OnGReleased.Broadcast(this);

	if (SubIconStateNormal.IsValid())
		SubIconStateNormal.Get()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (SubIconStatePressed.IsValid())
		SubIconStatePressed.Get()->SetVisibility(ESlateVisibility::Hidden);
}

void UBButton::_OnClicked()
{
	if (OnGClicked.IsBound())
	{
		OnGClicked.Broadcast(this);
	}
}

#undef LOCTEXT_NAMESPACE