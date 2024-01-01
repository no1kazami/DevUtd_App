// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Survey.generated.h"


class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Survey : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
	UBWidget_Top* BP_Top_Survey_UMG;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UScrollBox>  C_ScrollBox_SurveyItem;

	TArray<FST_SURVEY_INFO> _arSurveyInfo;
	int32 _CurPage;
	int32 _TotalPage;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitSurvey();

	void SendSurveyInfo();
	void RecvSurveyInfo();

	UFUNCTION()
	bool OnClickNextBtn();

	bool CheckSurveyPage();

private:
	void _SetSurveyInfo();
	void _SaveSurveyInfo();
	void _SetPage(int32 nCurPage);
};
