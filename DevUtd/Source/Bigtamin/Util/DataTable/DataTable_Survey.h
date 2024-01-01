// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Util/Bigtamin_Enum.h"
#include "DataTable_Survey.generated.h"

/** 설문 정보 항목을 정의하는 구조체 */
USTRUCT(BlueprintType)
struct FST_SurveyInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = SurveyInfo )
	int32 nSurveyIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = SurveyInfo )
	E_SURVEY_TYPE eSurveyType;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = SurveyInfo )
	int32 nTitleIndex;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = SurveyInfo )
	TArray<int32> arExampleIndex;

	FST_SurveyInfoData()
	{

	}

	~FST_SurveyInfoData()
	{

	}
};

UCLASS()
class BIGTAMIN_API UDataTable_Survey : public UDataTable
{
	GENERATED_BODY()
	
	
	
	
};
