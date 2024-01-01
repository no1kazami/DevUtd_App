// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Search.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_Search : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_Search;
	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_Search;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_ScrollBox_Search;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Delete;

	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_SearchText;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_ScrollBox_SearchText;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_NoSearch;

	UPROPERTY( meta = (BindWidget) )
		UWidgetSwitcher* C_WS_SearchResult;

	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch1;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch1;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch2;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch2;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch3;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch3;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch4;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch4;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch5;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch5;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch6;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch6;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch7;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch7;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch8;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch8;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch9;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch9;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_SaveSearch10;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_SaveSearch10;

	UPROPERTY( meta = (BindWidget) )
		TArray<UBButton*>  _BtnSaveSearch;
	UPROPERTY( meta = (BindWidget) )
		TArray<UTextBlock*>  _TxtSaveSearch;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void InitSearch();
	void HandleTopSearch( const FText handleTopText );
	void HandleTopSearchImg();

protected:
	virtual bool _OnBackInput() override;

private:
	UFUNCTION() void _OnClick_Delete();
	UFUNCTION() void _OnClick_Search1();
	UFUNCTION() void _OnClick_Search2();
	UFUNCTION() void _OnClick_Search3();
	UFUNCTION() void _OnClick_Search4();
	UFUNCTION() void _OnClick_Search5();
	UFUNCTION() void _OnClick_Search6();
	UFUNCTION() void _OnClick_Search7();
	UFUNCTION() void _OnClick_Search8();
	UFUNCTION() void _OnClick_Search9();
	UFUNCTION() void _OnClick_Search10();

	void _InitSearchSaveData();
	void _SearchData( const FText searchText );
};
