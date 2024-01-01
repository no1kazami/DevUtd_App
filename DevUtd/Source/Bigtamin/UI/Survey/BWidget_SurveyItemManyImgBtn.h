// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Survey/BWidget_SurveyItemBase.h"
#include "BWidget_SurveyItemManyImgBtn.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemManyImgBtn : public UBWidget_SurveyItemBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UImage> C_Img_Frame;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_SlotTitle;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UImage> C_Img_DownArrow;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UCheckBox>	C_CheckBox_Down;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<USizeBox>	C_SizeBox_DropDownList;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UUniformGridPanel> C_UGP_DropDownList;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void SetCurSurveyItem(FST_SURVEY_INFO surveyInfo) override;

	void SetOverLapCheckIndex(int32 checkIndex, bool isChecked);

private:
	UFUNCTION()
	void _OnDropDownCheckStateChanged(bool isChecked);
	
	void _AddDropDownSlot();
	
};
