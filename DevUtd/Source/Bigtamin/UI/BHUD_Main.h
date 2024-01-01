// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BHUDBase.h"
#include "BHUD_Main.generated.h"


UCLASS()
class BIGTAMIN_API ABHUD_Main : public ABHUDBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;	
};
