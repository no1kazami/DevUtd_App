// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Warning.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_Warning : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UTextBlock*	C_Txt_Warning;

	UWidgetAnimation* _Ani_Warning;
	FName _Ani_WarningName = "Ani_Warning";

	int32 _CurWarningIndex = 0;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	bool PlayWarning( int32 warningIndex );
	
};
