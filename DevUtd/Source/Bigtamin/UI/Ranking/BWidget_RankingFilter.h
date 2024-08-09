// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_RankingFilter.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_RankingFilter : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_RankingFilter, FOnClickRankingFilterApply, const FST_RANKING_FILTER_INFO )
	FOnClickRankingFilterApply OnClickRankingFilterApply;
	DECLARE_EVENT( UBWidget_RankingFilter, FOnClickRankingFilterCancel )
	FOnClickRankingFilterCancel OnClickRankingFilterCancel;

	struct FiterDataInfo
	{
		bool isChecked = false;
		int32 dataCount = 0;

		FiterDataInfo( bool checked, int32 count = 0 )
		{
			isChecked = checked;
			dataCount = count;
		}
	};

private:
	UPROPERTY( meta = (BindWidget) )
		UScrollBox* C_SB_Filter;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Filter_Cancel;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Back;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Apply;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Reset;


	// 구장
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Ground;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Ground;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Ground;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Ground;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Ground;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineGround;

	// 상대팀
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_AwayTeam;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_AwayTeam;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_AwayTeam;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_AwayTeam;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_AwayTeam;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineAwayTeam;

	// 기간
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Month;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Month;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Month;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Month;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Month;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineMonth;

	FST_RANKING_FILTER_INFO _PrevFilterInfo;
	FST_RANKING_FILTER_INFO _FilterInfo;

	FString _CurYear;
	bool bIsExceptionStadium = true;

public:
	virtual void Init( UBWidget* OwnerUI ) override;
	virtual void OnClose() override;
	virtual void OnShow() override;

	void ResetFilter();
	void ResetFilter( E_BRAND_TYPE brandType );
	void HandleBackInput();
	void SetYear(FString InYear);
	void SetExceptionStadium( bool isExceptionStadium );

private:
	UFUNCTION()
		void _OnClick_FilterCancel();
	UFUNCTION()
		void _OnClick_Back();
	UFUNCTION()
		void _OnClick_Apply();
	UFUNCTION()
		void _OnClick_Reset();

	UFUNCTION()
		void _ResetClick( E_BOOTS_FILTER_TYPE clickFilterType );
	UFUNCTION()
		void _OnClick_Stadium();
	UFUNCTION()
		void _OnClick_AwayTeam();
	UFUNCTION()
		void _OnClick_Month();

	UFUNCTION()
		void _OnGroundCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnAwayTeamCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnMonthCheckStateChanged( bool isChecked );

	UFUNCTION()
		void _HandleStadiumFilter( const FString stadiumType, const bool isCheck );
	UFUNCTION()
		void _HandleAwayTeamFilter( const FString AwayTeamType, const bool isCheck );
	UFUNCTION()
		void _HandleMonthFilter( const int32 MonthType, const bool isCheck );

	void _InitRankingFilter();
	void _UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE filterType );
	void _GetFilteringCategoryData( TArray<FString>& Out_StadiumInfo, TArray<FString>& Out_TeamInfo, TArray<int32>& Out_MonthInfo );
	void _GetFilterType( E_SORT_TYPE& Out_SortType );

	void _ResetFilter_Stadium( const TArray<FString>& stadiumInfo );
	void _ResetFilter_AwayTeam( const TArray<FString>& teamInfo );
	void _ResetFilter_Month( const TArray<int32>& monthInfo );
};
