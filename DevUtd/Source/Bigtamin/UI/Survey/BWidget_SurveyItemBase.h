// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItemBase.generated.h"

/**
 * 
 */
UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemBase : public UBWidget
{
	GENERATED_BODY()

protected:
	FST_SURVEY_INFO _SurveyInfo;
	int32 _CurCheckIndex;
	int32 _CurDownCheckIndex;

	TArray<int32> _CurOverLapCheckIndex;

private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Title;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;
	bool IsCheckSelected() const;

protected:
	virtual void SetCurSurveyItem( FST_SURVEY_INFO surveyInfo );
	void _SetTitleText();
	
	
};
