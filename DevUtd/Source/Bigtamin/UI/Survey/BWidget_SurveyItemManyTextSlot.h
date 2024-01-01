// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItemManyTextSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemManyTextSlot : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UCheckBox>	C_CheckBox;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example;

	int32 _SlotIndex;
	bool _IsOnlyOne;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetSlotData( int32 slotIndex, FString exampleTxt );
	void SetCheckOtherState( int32 exceptionCheckIndex, bool isCheck);

private:
	UFUNCTION()
	void _OnSurveyCheckStateChanged(bool isChecked);
};
