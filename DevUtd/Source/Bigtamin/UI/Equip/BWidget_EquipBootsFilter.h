// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_EquipBootsFilter.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_EquipBootsFilter : public UBWidget
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam( UBWidget_EquipBootsFilter, FOnClickEquipFilterApply, const FST_BOOTS_FILTER_INFO )
	FOnClickEquipFilterApply OnClickEquipFilterApply;
	DECLARE_EVENT( UBWidget_EquipBootsFilter, FOnClickEquipFilterCancel )
	FOnClickEquipFilterCancel OnClickEquipFilterCancel;

	struct FiterDataInfo
	{
		bool isChecked = false;
		int32 dataCount = 0;

		FiterDataInfo(bool checked, int32 count = 0)
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

	// 브랜드
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Brand;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Brand;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Brand;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Brand;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Brand;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineBrand;

	// Collection(모델명)
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Collection;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Collection;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Collection;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Collection;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Collection;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineCollection;

	// Model(등급명)
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Model;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Model;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Model;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Model;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Model;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineModel;

	// 스터드
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_Ol_Studs;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Studs;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Studs;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Studs;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Studs;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineStuds;

	// 사일로
	UPROPERTY( meta = (BindWidget) )
		UOverlay* C_OL_Silo;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Silo;
	UPROPERTY( meta = (BindWidget) )
		UCheckBox* C_CB_Silo;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Filter_Silo;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Count_Silo;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_LineSilo;

	FST_BOOTS_FILTER_INFO _PrevFilterInfo;
	FST_BOOTS_FILTER_INFO _FilterInfo;

public:
	virtual void Init( UBWidget* OwnerUI ) override;
	virtual void OnClose() override;
	virtual void OnShow() override;

	void ResetFilter();
	void ResetFilter( E_BRAND_TYPE brandType );
	void HandleBackInput();

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
		void _OnClick_Brand();
	UFUNCTION()
		void _OnClick_Collection();
	UFUNCTION()
		void _OnClick_Model();
	UFUNCTION()
		void _OnClick_Studs();
	UFUNCTION()
		void _OnClick_Silo();

	UFUNCTION()
		void _OnBrandCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnCollectionCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnModelCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnStudsCheckStateChanged( bool isChecked );
	UFUNCTION()
		void _OnSiloCheckStateChanged( bool isChecked );

	UFUNCTION()
		void _HandleBrandFilter( const E_BRAND_TYPE bootsBrandType, const bool isCheck );
	UFUNCTION()
		void _HandleCollectionFilter( const E_COLLECTION_TYPE bootsCollectionType, const bool isCheck );
	UFUNCTION()
		void _HandleModelFilter( const E_MODEL_TYPE bootsModelType, const bool isCheck );
	UFUNCTION()
		void _HandleStudsFilter( const E_STUDS_TYPE bootsStudsType, const bool isCheck );
	UFUNCTION()
		void _HandleSiloFilter( const E_SILO_TYPE bootsSiloType, const bool isCheck );

	void _InitEquipBootsFilter();
	void _UpdateEquipBootsFilter( E_BOOTS_FILTER_TYPE filterType );
	void _GetFilteringCategoryData( TArray<E_BRAND_TYPE>& Out_BrandInfo,
									TArray<E_COLLECTION_TYPE>& Out_CollectionInfo,
									TArray<E_MODEL_TYPE>& Out_ModelInfo,
									TArray<E_SILO_TYPE>& Out_SiloInfo,
									TArray<E_STUDS_TYPE>& Out_StudsInfo );
	void _GetFilterType( E_SORT_TYPE& Out_SortType, E_BRAND_TYPE& Out_BrandType);

	void _ResetFilter_Brand( const TArray<E_BRAND_TYPE>& brandInfo );
	void _ResetFilter_Collection( const TArray<E_COLLECTION_TYPE>& collectionInfo );
	void _ResetFilter_Model( const TArray<E_MODEL_TYPE>& modelInfo );
	void _ResetFilter_Studs( const TArray<E_STUDS_TYPE>& studsInfo );
	void _ResetFilter_Silo( const TArray<E_SILO_TYPE>& siloInfo );
};
