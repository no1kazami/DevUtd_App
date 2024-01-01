// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGameMode.h"
#include "Util/DataTable/DataTable_Survey.h"
#include "BGameMode_Main.generated.h"


UCLASS()
class BIGTAMIN_API ABGameMode_Main : public ABGameMode
{
	GENERATED_BODY()
private:
	bool _IsStart = false;

public:
	virtual void InitGame( const FString& MapName, const FString& Options, FString& ErrorMessage ) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	void ChangeMode(E_MODE eChangeMode);
};
