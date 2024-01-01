// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Survey/BWidget_SurveyItemBase.h"
#include "BWidget_SurveyItemImgBtn.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemImgBtn : public UBWidget_SurveyItemBase
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UOverlay> C_Overlay_1;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UCheckBox>	C_CheckBox_1;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_1;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example_1;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UOverlay> C_Overlay_2;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UCheckBox>	C_CheckBox_2;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_2;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example_2;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UOverlay> C_Overlay_3;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UCheckBox>	C_CheckBox_3;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_3;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example_3;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UOverlay> C_Overlay_4;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UCheckBox>	C_CheckBox_4;
	UPROPERTY( meta = (BindWidget) )
	TWeakObjectPtr<UImage> C_Img_4;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example_4;

	bool _IsSuccess;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void SetCurSurveyItem(FST_SURVEY_INFO surveyInfo) override;

private:
	UFUNCTION()
	void _OnSurveyCheckStateChanged1(bool isChecked);
	UFUNCTION()
	void _OnSurveyCheckStateChanged2(bool isChecked);
	UFUNCTION()
	void _OnSurveyCheckStateChanged3(bool isChecked);
	UFUNCTION()
	void _OnSurveyCheckStateChanged4(bool isChecked);

	void _SetSurveyItemExampleText();
	void _SetSurveyItemImgTextureBG();
	void _SetSurveyItemImgTextureIcon();
	void _CheckOtherState();
};
