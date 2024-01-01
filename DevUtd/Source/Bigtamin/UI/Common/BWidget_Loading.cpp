// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_Loading.h"

void UBWidget_Loading::Init()
{
	Super::Init();

	SetVisibility( ESlateVisibility::Collapsed );
}

void UBWidget_Loading::OnClose()
{
	Super::OnClose();
}

void UBWidget_Loading::PlayLoading( const bool isLoading )
{
	if (isLoading)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		SetVisibility( ESlateVisibility::Collapsed);
	}
}
