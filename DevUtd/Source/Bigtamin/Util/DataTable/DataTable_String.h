// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTable_String.generated.h"

/** �� ���� ����� String ���� �׸��� �����ϴ� ����ü */
USTRUCT(BlueprintType)
struct FST_StringInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = StringInfo)			// ����� ��Ʈ��
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
