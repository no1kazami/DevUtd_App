// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItemManyImgSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemManyImgSlot : public UBWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UCheckBox>	C_CheckBox;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_Example;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UImage> C_Img_Slot;

	int32 _SlotIndex;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetSlotData(int32 slotIndex, FString exampleTxt, FString imgUrl);

private:
	UFUNCTION()
	void _OnSlotCheckStateChanged(bool isChecked);
	
};
