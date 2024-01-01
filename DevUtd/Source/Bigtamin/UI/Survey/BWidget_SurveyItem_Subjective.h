// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItem_Subjective.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItem_Subjective : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UEditableText> C_EditText_Answer;

	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_BG;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;
	
	void SetSurveyItemDetail( int32 nIndex );
	bool CheckState();

	UFUNCTION()
	void OnTextAnswerChanged( const FText& InText );
	
};
