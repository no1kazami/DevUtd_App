// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Upcoming.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Upcoming : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_Upcoming_UMG;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_SB_UpcommingSlot;

	UWidgetAnimation* _Ani_UpcomingOpen;
	FName _Ani_UpcomingOpenName = "Ani_Upcoming_Open";
	UWidgetAnimation* _Ani_UpcomingClose;
	FName _Ani_UpcomingCloseName = "Ani_Upcoming_Close";

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitUpcoming();
	void PlayUpcomingOpenAni( const bool isOpen );

protected:
	virtual bool _OnBackInput() override;
};
