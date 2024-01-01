// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Util/Bigtamin_Enum.h"
#include "DataTable_FootBallBoots.generated.h"

/** �౸ȭ �׸��� �����ϴ� ����ü */
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

	// ���Ϸ� Ÿ��
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_SILO_TYPE eSiloType;

	// ���͵� Ÿ��
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_STUDS_TYPE eStudsType;

	// ����(����) Ÿ��
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	E_UPPER_TYPE eUpperType;

	// ������ �׶��� Ÿ��
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	TArray<E_GROUND_TYPE> arGroundType;

	// ����
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeight;

	// ���� ����ġ(ª��, ����, ��)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightLength;

	// Fit ����ġ(������, ����:��������, ��Ʈ��)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightSize;

	// ���� ����ġ(����Ʈ, �ϵ�)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightHeelCup;

	// �ߺ� ����ġ(����, ����, ����)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightBallOfFoot;

	// �ߵ� ����ġ(����, ����, ����)
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nWeightHeightOfFoot;

	// ����
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nPrice;

	// �����
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category = FootBallBootsInfo )
	int32 nReleaseDate;

	// ǰ��
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
