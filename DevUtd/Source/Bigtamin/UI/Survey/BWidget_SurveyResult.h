// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyResult.generated.h"


class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_SurveyResult : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
	UBWidget_Top* BP_Top_SurveyResult_UMG;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UScrollBox>  C_ScrollBox_ResultItem;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitSurveyResult();

protected:
	virtual bool _OnBackInput() override;

private:
	void _SetSurveyResulData();
};
