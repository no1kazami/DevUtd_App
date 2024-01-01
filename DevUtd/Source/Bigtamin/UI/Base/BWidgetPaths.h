// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Util/Bigtamin_Enum.h"

#include "BWidgetPaths.generated.h"

/**
 * 
 */
UCLASS()
class BIGTAMIN_API UBWidgetPaths : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	static const FString GetWidgetDirectoryPath() { return TEXT("/Game/BP/UMG/"); }
	static const FString GetWidgetDirectoryPath(FString AddPath) { return GetWidgetDirectoryPath() + AddPath; }

	const FString GetPath(const EBUIName UIName)
	{
		if (WidgetPathMap.Contains(UIName))
			return WidgetPathMap[UIName];

		return TEXT("");
	}

	const FString GetPath(const EDynamicWidgetParts PartsName)
	{
		if (DynamicWidgetPathMap.Contains(PartsName))
			return DynamicWidgetPathMap[PartsName];

		return TEXT("");
	}

	/*
	const FString GetPath(const EModalPopupWidget ModalName)
	{
		if (ModalWidgetPathMap.Contains(ModalName))
			return ModalWidgetPathMap[ModalName];

		return TEXT("");
	}
	*/

private:

	void _InitWidgetPath();
	void _InitDynamicWidgetPartsPath();
	void _InitModalWidgetPath();

private:
	TMap<EBUIName, FString> WidgetPathMap;
	TMap<EDynamicWidgetParts, FString> DynamicWidgetPathMap;
	//TMap<EModalPopupWidget, FString> ModalWidgetPathMap;
	
	
};
