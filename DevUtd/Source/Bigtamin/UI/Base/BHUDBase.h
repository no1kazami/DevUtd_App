// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Bigtamin_GameInstance.h"
#include "Util/Bigtamin_Enum.h"
#include "UI/Base/BWidget.h"
#include "UI/Base/BWidgetPaths.h"
#include "Engine/StreamableManager.h"
#include "UObject/ConstructorHelpers.h"

#include "BHUDBase.generated.h"

class UBWidget_Dialog;

USTRUCT(BlueprintType)
struct FWidgetData
{
	GENERATED_USTRUCT_BODY()
public:
	FWidgetData() : bAlwaysView(false), Widget(nullptr) {}

	const bool operator == (const FWidgetData val) { return (this == &val); }
	/**
	AllCloseUI 시에 안닫히게 할 UI를 true로 함.
	Close 또는 Hide시에는 직접 콜함.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BWidget")
	bool bAlwaysView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BWidget")
	EBUIName WidgetName;

	UPROPERTY()
	UBWidget *Widget;

	TSubclassOf<UBWidget> GetWidgetClass(FStreamableManager &LoadManager);
	void Unload(FStreamableManager &LoadManager);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BWidget")
		TAssetSubclassOf<UBWidget> WidgetClass;
};

UCLASS()
class BIGTAMIN_API ABHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	virtual void OnConstruction(const FTransform& Transform) override;
	//virtual void Tick(float DeltaSeconds) override;

	template <typename T>
	T* OpenUI(EBUIName uiName, bool bAlwaysView = false, int32 ZOrder = 0)
	{
		// 만들어졌던 Widget을 확인
		T* widget = GetCreatedWidget<T>(uiName);
		if (!widget)
		{
			widget = CreateGWidget<T>(uiName, false);

			if (widget)
			{
				widget->WidgetUIName = uiName;
				widget->SetPrevMode( GInst->GetCurMode() );

				FWidgetData newData;
				newData.Widget = widget;
				newData.WidgetName = uiName;
				newData.bAlwaysView = bAlwaysView;

				CreatedWidgetDatas.Add(newData);
			}
		}
		else
		{
			widget->Init();
		}

		//G_WidgetMgr->OnHide();		//TopMost 위젯 대상으로 OnShow (ZOrder 무관)

		AddToViewport(widget, ZOrder);

		//G_WidgetMgr->Push(widget);
		//G_WidgetMgr->OnShow();		//TopMost 위젯 대상으로 OnHide (ZOrder 무관)

		return widget;
	}

	void CloseUI(EBUIName UIName);
	void CloseUI(UBWidget *widget);
	void CloseAllUI();
	void ClosePopUI(bool CloseAlwaysViewUI = false);

	FWidgetData* GetWidgetData(const EBUIName UIName);
	FWidgetData* GetWidgetData(const UBWidget *Widget);

	template <typename T>
	T* GetCreatedWidget(EBUIName uiName)
	{
		FWidgetData *widgetData = GetWidgetData(uiName);
		if (!widgetData || !widgetData->Widget)
			return nullptr;

		return Cast<T>(widgetData->Widget);
	}

	template <class T>
	T* GetWidgetInViewport(EBUIName uiName)
	{
		for (auto &It : StackWidgetInViewport)
		{
			if (It->WidgetUIName == uiName)
				return Cast<T>(It);
		}

		return nullptr;
	}

	// 현재 만들어져서 뷰포트에 올라가있는 모든 UI들을 가리거나 보이거나
	UFUNCTION(BlueprintCallable, Category = "GHUDBase")
	void ToggleVisibleShowUI();
	bool IsToggleVisibleShowUI() { return m_bToggleVisibleShowUI; }

	//UGWidgetModal* GetCurrentViewModalWidget() { return CurrentViewModalWidget; }
	//bool IsCurrentViewModalWidget() { return (CurrentViewModalWidget) ? true : false; }

	// Dialog modal
	UBWidget_Dialog* ShowDialogWidget(FString Title, FString Desc, EBUIPopupMessage DialogType, EBUIPopupMessageButton ButtonType);
	UBWidget_Dialog* ShowSystemDialogWidget(FString Title, FString Desc, EBUIPopupMessageButton ButtonType);

	//UGWidget_Notice* ShowNoticeWidget(ENoticeType msgType, FText msg);

	// modal widget
	// 로직은 일반 dynamicwidget과 비슷하지만 용도를 명확히 하기위해 따로 만듬.
	/*
	template<typename T>
	T* ShowModalWidget(EModalPopupWidget modalWidget)
	{
		FString loadPath = WidgetPaths->GetPath(modalWidget);

		if (loadPath.IsEmpty())
		{
			FString uiString = GetEnumValueToString<EModalPopupWidget>("EModalPopupWidget", modalWidget);
			UE_LOG(LogFBM, Error, TEXT("Not Found EModalPopupWidget(%s) In EModalPopupWidget"), *uiString);
		}

		CurrentViewModalWidget = CreateGWidget<T>(loadPath, true, 1);

		if (CurrentViewModalWidget)
			return Cast<T>(CurrentViewModalWidget);
		else
			return nullptr;
	}
	*/

	template<typename T>
	T* CreateGWidget(FString& widgetPath, bool isAddToViewport, int32 ZOrder = 0)
	{
		if (widgetPath.IsEmpty())
		{
			//UE_LOG(LogG, Error, TEXT("widgetPath is Empty"));
			return nullptr;
		}
		UClass *widgetClass = ConstructorHelpersInternal::FindOrLoadClass(widgetPath, UBWidget::StaticClass());
		if (!widgetClass)
		{
			//UE_LOG(LogG, Error, TEXT("Not Found Widget : %s"), *widgetPath);
			return nullptr;
		}

		T *dynamicWidget = ::CreateWidget<T>(GetWorld(), widgetClass);
		if (!dynamicWidget)
		{
			//UE_LOG(LogG, Error, TEXT("Cast Fail Widget : %s"), *widgetPath);
		}

		if (isAddToViewport)
			dynamicWidget->AddToViewport(ZOrder);
		dynamicWidget->Init();

		return dynamicWidget;
	}

	template<typename T>
	T* CreateGWidget(EBUIName uiName, bool isAddToViewport, int32 ZOrder = 0)
	{
		FString loadPath = WidgetPaths->GetPath(uiName);
		if (loadPath.IsEmpty())
		{
			//FString uiString = GetEnumValueToString<EBUIName>("EBUIName", uiName);
			//UE_LOG(LogG, Error, TEXT("Not Found Widget(%s) In WidgetPaths"), *uiString);
		}

		T* dynamicWidget = CreateGWidget<T>(loadPath, isAddToViewport, ZOrder);
		return dynamicWidget;
	}

	template<typename T>
	T* CreateDynamicWidget(FString& widgetPath, bool bPutStack = true, int32 ZOrder = 0)
	{
		T* dynamicWidget = CreateGWidget<T>(widgetPath, !bPutStack, ZOrder);
		if (dynamicWidget && true == bPutStack)
			AddToViewport(dynamicWidget, ZOrder);

		return dynamicWidget;
	}

	template<typename T>
	T* CreateDynamicWidget(EDynamicWidgetParts parts, bool bPutStack = true, int32 ZOrder = 0)
	{
		FString loadPath = WidgetPaths->GetPath(parts);
		if (loadPath.IsEmpty())
		{
			FString uiString = GetEnumValueToString<EDynamicWidgetParts>("EDynamicWidgetParts", parts);
			//UE_LOG(LogG, Error, TEXT("Not Found DynamicWidget(%s) In DynamicWidgetPaths"), *uiString);
		}

		return CreateDynamicWidget<T>(loadPath, bPutStack, ZOrder);
	}

	void SetAlwaysViewWidget(const UBWidget* TargetWidget, const bool bAlwaysView);

	void SetVirtualJoystickVisibility(bool bVisible);


	UFUNCTION(BlueprintCallable, Category = "GHUDBase")
	void ShowInGameUI(bool bVisible);

	UFUNCTION(BlueprintCallable, Category = "GHUDBase")
	void ShowFadeInOutPannel(float fadeInTime, float fadeOutTime, float fadeDelayTime);

protected:
	virtual void BeginPlay() override;

	void AddToViewport(UBWidget *widget, int32 ZOrder = 0);
	bool RemoveFromViewport(UBWidget *widget);
	void RemoveFromPop();

private:
	void FadeInComplete();
	void FadeOutComplete();

	class UGGameViewportClient* GetGameViewport();

public:
	DECLARE_EVENT(AGHUDBase, FGHUDBeginPlayEvent);
	FGHUDBeginPlayEvent OnBeginPlayEvent;
	bool OnBeginPlayEventFinished;

private:
	//UPROPERTY()
	//UGWidgetModal*	CurrentViewModalWidget;

	UPROPERTY()
	UBWidgetPaths* WidgetPaths;

	UPROPERTY()
	TArray<UBWidget*> StackWidgetInViewport;

	UPROPERTY()
	TArray<FWidgetData> CreatedWidgetDatas;

	bool m_bToggleVisibleShowUI;

	EBUIName FadeUIName;

	UPROPERTY()
	UBWidget_Dialog* SystemDialogWidget;
	
	
};
