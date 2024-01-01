// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Version.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Version : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_Version_UMG;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CurVersion;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_NewVersion;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitVersion();

protected:
	virtual bool _OnBackInput() override;
};
