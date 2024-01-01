// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "UI/Boots/BWidget_BootsDetail.h"
#include "UI/BWidget_NewMain.h"
#include "Bigtamin_PlayerController.generated.h"


UCLASS()
class BIGTAMIN_API ABigtamin_PlayerController : public APlayerController
{
	GENERATED_BODY()
private:
// 	UPROPERTY()
// 		TWeakObjectPtr<UBWidget_BootsDetail> _BootsDetailUMG;
	UPROPERTY()
		TWeakObjectPtr<UBWidget_NewMain> _NewMainlUMG;
	
public:
	virtual void BeginPlay() override;	
	virtual bool InputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex ) override;

	UFUNCTION( BlueprintCallable, Category = "KeyInput" )
	void BackKeyInput();
	
private:
	void _SwipeScrollWidgetInputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex );
};
