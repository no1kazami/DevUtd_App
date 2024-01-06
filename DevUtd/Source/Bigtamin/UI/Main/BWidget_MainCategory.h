// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MainCategory.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_MainCategory : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_MainCategory, FOnClickMainCategory, const E_MAINCATEGORY_TYPE )
	FOnClickMainCategory OnClickMainCategory;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Home;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Schedule;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Result;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Ranking;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Player;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Stadium;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Noti;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Faq;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Idea;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Rule;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Share;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Review;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Support;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Partnership;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Version;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Cancel;

public:
	virtual void Init( UBWidget* OwnerUI ) override;
	virtual void OnClose() override;

private:
	UFUNCTION()
		void _OnClick_Home();
	UFUNCTION()
		void _OnClick_Schedule();
	UFUNCTION()
		void _OnClick_Result();
	UFUNCTION()
		void _OnClick_Ranking();
	UFUNCTION()
		void _OnClick_Player();
	UFUNCTION()
		void _OnClick_Stadium();
	UFUNCTION()
		void _OnClick_Noti();
	UFUNCTION()
		void _OnClick_Faq();
	UFUNCTION()
		void _OnClick_Idea();
	UFUNCTION()
		void _OnClick_Rule();
	UFUNCTION()
		void _OnClick_Share();
	UFUNCTION()
		void _OnClick_Review();
	UFUNCTION()
		void _OnClick_Support();
	UFUNCTION()
		void _OnClick_Partnership();
	UFUNCTION()
		void _OnClick_Version();
	UFUNCTION()
		void _OnClick_Cancel();	
};
