// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Survey/BWidget_SurveyItemBase.h"
#include "BWidget_SurveyItemDropDown.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemDropDown : public UBWidget_SurveyItemBase
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UCheckBox>	C_CheckBox_Down;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_DropDownSelect;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UImage> C_Img_DownArrow;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UOverlay> C_OL_DropDownList;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UScrollBox>  C_SB_DropDownList;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void SetCurSurveyItem(FST_SURVEY_INFO surveyInfo) override;

	void OnClickDropDownSlot(int32 checkIndex, FString slotString);

private:
	UFUNCTION()
	void _OnDropDownCheckStateChanged(bool isChecked);

	void _SetDropDownListInfo();
	
	
};
