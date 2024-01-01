// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Survey_NextBtn.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_Survey_NextBtn : public UBWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Text_Next;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UBButton> C_Btn_Next;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UTextBlock>	C_Text_Error;

	bool _IsCheckSurvey;
	float _CheckSurveyTime;
	float _CurCheckSurveyTime;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;

	void SetBtnText(FText btnText);

private:
	UFUNCTION()
	void _OnClickNextBtn();
};
