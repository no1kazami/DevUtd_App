// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Util/Bigtamin_Enum.h"
//#include "Util/Bigtamin_Struct.h"
#include "BGameMode.generated.h"


UCLASS()
class BIGTAMIN_API ABGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABGameMode();
	virtual ~ABGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
};
