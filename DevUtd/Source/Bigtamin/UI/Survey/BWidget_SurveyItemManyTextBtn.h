// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Survey/BWidget_SurveyItemBase.h"
#include "BWidget_SurveyItemManyTextBtn.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemManyTextBtn : public UBWidget_SurveyItemBase
{
	GENERATED_BODY()	

private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UUniformGridPanel> C_UGP_Slots;

	bool _IsCurOnlyOne;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void SetCurSurveyItem(FST_SURVEY_INFO surveyInfo) override;
	void SetOverLapCheckIndex(int32 checkIndex, bool isChecked, bool isOnlyOne);

private:
	void _AddSurveySlot();
	void _CheckOtherState( int32 exceptionCheckIndex, bool isChecked);
};
