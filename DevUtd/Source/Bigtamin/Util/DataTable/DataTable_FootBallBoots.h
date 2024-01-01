// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Util/Bigtamin_Enum.h"
#include "DataTable_FootBallBoots.generated.h"

/** 축구화 항목을 정의하는 구조체 */
USTRUCT( BlueprintType )
struct FST_FootBallBootsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nIndex;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	FText BootsName;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	FText IconPath;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_BRAND_TYPE eBrandType;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_GENDER_TYPE eGenderType;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
		E_COLLECTION_TYPE eCollectionType;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
		int32 nCollectionNum;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
		E_MODEL_TYPE eModelType;

	// 사일로 타입
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_SILO_TYPE eSiloType;

	// 스터드 타입
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_STUDS_TYPE eStudsType;

	// 어퍼(외피) 타입
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_UPPER_TYPE eUpperType;

	// 가능한 그라운드 타입
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	TArray<E_GROUND_TYPE> arGroundType;

	// 무게
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeight;

	// 길이 가중치(짧음, 보통, 김)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightLength;

	// Fit 가중치(느슨함, 보통:정사이즈, 피트함)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightSize;

	// 힐컵 가중치(소프트, 하드)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightHeelCup;

	// 발볼 가중치(좁음, 보통, 넓음)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightBallOfFoot;

	// 발등 가중치(좁은, 보통, 넓음)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightHeightOfFoot;

	// 가격
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nPrice;

	// 출시일
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nReleaseDate;

	// 품번
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	FText ProductID;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	TArray<FText> Other_ProductID;


	FST_FootBallBootsData()
	{

	}

	~FST_FootBallBootsData()
	{

	}
};

UCLASS()
class BIGTAMIN_API UDataTable_FootBallBoots : public UDataTable
{
	GENERATED_BODY()
	
	
	
	
};
