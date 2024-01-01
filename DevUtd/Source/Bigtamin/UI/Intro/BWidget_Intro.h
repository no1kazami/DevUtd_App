// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Intro.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_Intro : public UBWidget
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnClose() override;
	
};
