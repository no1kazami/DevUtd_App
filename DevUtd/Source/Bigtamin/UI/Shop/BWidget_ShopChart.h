// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ShopChart.generated.h"

class UBWidget_EquipFilterItem;

UCLASS()
class BIGTAMIN_API UBWidget_ShopChart : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_EquipFilterItem* BP_Day_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_EquipFilterItem* BP_Week_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_EquipFilterItem* BP_Month_UMG;
	UPROPERTY( meta = (BindWidget) ) USizeBox* C_SizeBox_Chart;

	UPROPERTY( meta = (BindWidget) ) USpacer* C_Spacer_TopLeft;
	UPROPERTY( meta = (BindWidget) ) USpacer* C_Spacer_DownLeft;
	UPROPERTY( meta = (BindWidget) ) USpacer* C_Spacer_DownRight;

	UPROPERTY( meta = (BindWidget) ) UImage* C_Img_UnderLine;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_LowPrice;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_ClickPrice;

	UPROPERTY( meta = (BindWidget) ) UWidgetSwitcher* C_WidgetSwitcher_DateText;
	UPROPERTY( meta = (BindWidget) ) UHorizontalBox* C_HB_DateDay;
	UPROPERTY( meta = (BindWidget) ) UHorizontalBox* C_HB_DateWeek;
	UPROPERTY( meta = (BindWidget) ) UHorizontalBox* C_HB_DateMonth;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day1;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day2;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day3;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day4;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day5;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day6;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Day7;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Week1;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Week2;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Week3;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Week4;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month1;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month2;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month3;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month4;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month5;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Month6;

	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day1;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day2;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day3;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day4;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day5;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day6;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Day7;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Week1;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Week2;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Week3;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Week4;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month1;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month2;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month3;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month4;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month5;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Month6;

	UPROPERTY( meta = (BindWidget) ) UImage* C_Img_DotOver;

	float _MinY = 0.f;
	float _MaxY = 0.f;
	float _MinX = 0.f;
	float _MaxX = 0.f;
	float _PriceGap = 0.f;

	UPROPERTY()	FString _ShopProductID;
	UPROPERTY()	TArray<FST_LOW_PRICE_INFO_DATA> _DayPriceData;
	UPROPERTY()	TArray<FST_LOW_PRICE_INFO_DATA> _WeekPriceData;
	UPROPERTY()	TArray<FST_LOW_PRICE_INFO_DATA> _MonthPriceData;
	UPROPERTY()	TArray<FVector2D> _DatePoints;
	UPROPERTY()	E_FILTER_ITEM_TYPE _PeriodFilterType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_NONE;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual int32 NativePaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;

	UFUNCTION()	void SetShopData( const FString shopProductID);
	UFUNCTION()	void SetChartDay();
	UFUNCTION()	void SetChartWeek();
	UFUNCTION()	void SetChartMonth();
	UFUNCTION()	void OnClickPeriodFilter( const E_FILTER_ITEM_TYPE infoFilterType, bool isForce = true );

private:
	UFUNCTION() void _OnClick_Day1();
	UFUNCTION() void _OnClick_Day2();
	UFUNCTION() void _OnClick_Day3();
	UFUNCTION() void _OnClick_Day4();
	UFUNCTION() void _OnClick_Day5();
	UFUNCTION() void _OnClick_Day6();
	UFUNCTION() void _OnClick_Day7();

	UFUNCTION() void _OnClick_Week1();
	UFUNCTION() void _OnClick_Week2();
	UFUNCTION() void _OnClick_Week3();
	UFUNCTION() void _OnClick_Week4();

	UFUNCTION() void _OnClick_Month1();
	UFUNCTION() void _OnClick_Month2();
	UFUNCTION() void _OnClick_Month3();
	UFUNCTION() void _OnClick_Month4();
	UFUNCTION() void _OnClick_Month5();
	UFUNCTION() void _OnClick_Month6();

	UFUNCTION() void _CalcChartBaseData();
	UFUNCTION()	void _DrawChartDay( FPaintContext& Context ) const;
	UFUNCTION() void _CalcCurPriceTextPosition( UBButton* btn, int32 dataIndex );
	UFUNCTION() void _SetPointBtnText( UTextBlock* dateText, UBButton* dateBtn, FString& dateString, FVector2D& btnPosition );
	UFUNCTION() void _SetVisiblePointBtnText();
	UFUNCTION() void _TestData();

};
