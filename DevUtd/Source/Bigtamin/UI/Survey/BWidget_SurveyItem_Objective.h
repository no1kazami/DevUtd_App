// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItem_Objective.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItem_Objective : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_BG;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UTextBlock>	C_Txt_Name;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UCheckBox>	C_CheckBox_Survey;
		
	int32 _ElementIndex;
	E_SURVEY_TYPE _SurveyType;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetSurveyItemDetail( int32 nIndex, int32 nType, E_SURVEY_TYPE eType );
	void SetSurveyCheckBox( ECheckBoxState state );
	bool IsSurveyChecked();

	UFUNCTION()
	void OnSurveyCheckStateChanged( bool isChecked );

	int32 GetElementIndex()
	{
		return _ElementIndex;
	}
	
};
