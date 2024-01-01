// Fill out your copyright notice in the Description page of Project Settings.

#include "BGameMode.h"


ABGameMode::ABGameMode()
{

}

ABGameMode::~ABGameMode()
{

}

void ABGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABGameMode::StartPlay()
{
	Super::StartPlay();
}

void ABGameMode::BeginPlay()
{
	Super::BeginPlay();
}
