// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SurveyItemDropDownSLot.generated.h"

/**
 * 
 */
UCLASS()
class BIGTAMIN_API UBWidget_SurveyItemDropDownSLot : public UBWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UBButton> C_Btn_DropDownSlot;
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock>	C_Txt_DropDownSlot;

	int32 _SlotIndex;
	FString _slotText;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetSlotData(int32 slotIndex, FString exampleTxt);

private:
	UFUNCTION()
	void _OnClickDropDownSlotBtn();	
	
};
