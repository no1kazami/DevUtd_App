// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_UpdateCheck.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_UpdateCheck : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Type;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CurVersion;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_NewVersion;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CheckTime;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Update;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_ServerOK;


	E_UPDATE_CHECK_TYPE _UpdateCheckType = E_UPDATE_CHECK_TYPE::NONE;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitUpdateCheck(const E_UPDATE_CHECK_TYPE updateCheckType);

private:
	void SetUpdate();
	void SetServerCheck();

	UFUNCTION()
		void _OnClick_Update();
	UFUNCTION()
		void _OnClick_ServerCheckOK();
};
