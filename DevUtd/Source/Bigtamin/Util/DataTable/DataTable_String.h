// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTable_String.generated.h"

/** 앱 에서 사용할 String 정보 항목을 정의하는 구조체 */
USTRUCT(BlueprintType)
struct FST_StringInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = StringInfo)			// 사용할 스트링
		FText tStr;

	FST_StringInfoData()
	{

	}

	~FST_StringInfoData()
	{

	}
};

UCLASS()
class BIGTAMIN_API UDataTable_String : public UDataTable
{
	GENERATED_BODY()	
	
	
};
