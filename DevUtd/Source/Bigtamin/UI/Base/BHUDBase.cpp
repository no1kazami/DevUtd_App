// Fill out your copyright notice in the Description page of Project Settings.

#include "BHUDBase.h"
#include "Bigtamin.h"

#include "UI/BWidget_Dialog.h"
//#include "Camera/GGameViewportClient.h"

TSubclassOf<class UBWidget> FWidgetData::GetWidgetClass(FStreamableManager &LoadManager)
{
	if (WidgetClass.IsValid() == false && WidgetClass.ToSoftObjectPath().ToString().Len() > 0)
	{
		LoadManager.LoadSynchronous(WidgetClass.ToSoftObjectPath(), true);
	}
	if (WidgetClass.IsValid() == false)
	{
		return nullptr;
	}
	return WidgetClass.Get();
}

void FWidgetData::Unload(FStreamableManager &LoadManager)
{
	if (WidgetClass.IsValid())
	{
		LoadManager.Unload(WidgetClass.ToSoftObjectPath());
	}
}

void ABHUDBase::OnConstruction(const FTransform& Transform)
{
	SetActorTickEnabled(false);
	Init();
}

void ABHUDBase::Init()
{
	WidgetPaths = NewObject<UBWidgetPaths>();
	WidgetPaths->Init();

	m_bToggleVisibleShowUI = true;
	FadeUIName = EBUIName::None;
}

FWidgetData* ABHUDBase::GetWidgetData(const EBUIName UIName)
{
	for (FWidgetData &WidgetData : CreatedWidgetDatas)
	{
		if (WidgetData.WidgetName == UIName)
			return &WidgetData;
	}

	return nullptr;
}

FWidgetData* ABHUDBase::GetWidgetData(const UBWidget *Widget)
{
	for (FWidgetData &WidgetData : CreatedWidgetDatas)
	{
		if (WidgetData.Widget == Widget)
			return &WidgetData;
	}

	return nullptr;
}

void ABHUDBase::CloseUI(UBWidget *widget)
{
	if (!widget)
	{
		//UE_LOG(LogG, Error, TEXT("CloseUI widget is null"));
		return;
	}

	widget->OnHide();
	//G_WidgetMgr->PopWidget(widget);
	//G_WidgetMgr->OnShow();

	widget->OnClose();
	RemoveFromViewport(widget);
}

void ABHUDBase::CloseUI(EBUIName uiName)
{
	auto widgetData = GetWidgetData(uiName);
	if (!widgetData)
	{
		//UE_LOG(LogG, Error, TEXT("CloseUI CreatedWidgetData is null"));
		return;
	}

	if (!widgetData->Widget)
	{
		//UE_LOG(LogG, Log, TEXT("CloseUI CreatedWidgetData widget is null"));
		return;
	}

	CloseUI(widgetData->Widget);
}


void ABHUDBase::CloseAllUI()
{
	for (auto &widget : StackWidgetInViewport)
	{
		auto widgetData = GetWidgetData(widget);
		if (widgetData && widgetData->Widget)
		{
			if (widgetData->bAlwaysView)
				continue;

			RemoveFromViewport(widget);
		}
	}
}

void ABHUDBase::ClosePopUI(bool CloseAlwaysViewUI /*= false*/)
{
	RemoveFromPop();
}

void ABHUDBase::ToggleVisibleShowUI()
{
	m_bToggleVisibleShowUI = !m_bToggleVisibleShowUI;

	for (auto &Widget : StackWidgetInViewport)
	{
		if (Widget->IsInViewport())
		{
			if (m_bToggleVisibleShowUI)
				Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			else
				Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ABHUDBase::SetAlwaysViewWidget(const UBWidget* TargetWidget, const bool bAlwaysView)
{
	FWidgetData* widgetData = GetWidgetData(TargetWidget);

	if (widgetData)
	{
		if (widgetData->Widget && widgetData->Widget->IsInViewport())
		{
			widgetData->bAlwaysView = bAlwaysView;
		}
	}
}

void ABHUDBase::SetVirtualJoystickVisibility(bool bVisible)
{
	auto* controller = GetOwningPlayerController();
	if (controller)
	{
		controller->SetVirtualJoystickVisibility(bVisible);

		if (!bVisible)
			controller->ActivateTouchInterface(nullptr);
		else
			controller->CreateTouchInterface();
	}
}

void ABHUDBase::ShowInGameUI(bool bShow)
{
	auto visibility = bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;

	for (auto &Widget : StackWidgetInViewport)
	{
		if (Widget->IsInViewport())
		{
			Widget->SetVisibility(visibility);
		}
	}

	SetVirtualJoystickVisibility(bShow);
}

//////////////////////////////////////////////////////////////////////////
// Private Function


void ABHUDBase::AddToViewport(UBWidget *widget, int32 ZOrder)
{
	if (!widget)
	{
		//UE_LOG(LogG, Error, TEXT("Open Widget is Null"));
		return;
	}

	if (widget->IsInViewport())
	{
		RemoveFromViewport(widget);
	}

	if (!widget->IsInViewport())
	{
		widget->AddToViewport(ZOrder);
		StackWidgetInViewport.Add(widget);
	}
}

bool ABHUDBase::RemoveFromViewport(UBWidget *widget)
{
	if (!widget)
	{
		//UE_LOG(LogG, Error, TEXT("Close Widget is Null"));
		return false;
	}

	if (widget->IsInViewport())
	{
		// Deprecation
#if 0
		widget->RemoveFromViewport();
#endif
		widget->RemoveFromParent();
		StackWidgetInViewport.Remove(widget);
		return true;
	}

	return false;
}

void ABHUDBase::RemoveFromPop()
{
	auto widget = StackWidgetInViewport.Pop();
	RemoveFromViewport(widget);
}

void ABHUDBase::FadeInComplete()
{
	OpenUI<UBWidget>(FadeUIName);
	FadeUIName = EBUIName::None;

	/*
	UGGameViewportClient* gameViewport = GetGameViewport();
	if (gameViewport)
	{
		gameViewport->Fade(false);
	}
	*/
}

void ABHUDBase::FadeOutComplete()
{

}

/*
UGGameViewportClient* ABHUDBase::GetGameViewport()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UGGameViewportClient* gameViewportClient = Cast<UGGameViewportClient>(World->GetGameViewport());
		return gameViewportClient;
	}

	return nullptr;
}
*/

void ABHUDBase::BeginPlay()
{
	OnBeginPlayEvent.Broadcast();
	OnBeginPlayEventFinished = true;

	Super::BeginPlay();
}

UBWidget_Dialog* ABHUDBase::ShowDialogWidget(FString Title, FString Desc, EBUIPopupMessage DialogType, EBUIPopupMessageButton ButtonType)
{
	FString dialogPath = TEXT("/Game/BluePrint/UI/BP_WidgetDialog");
	int32 ZOrder = 1;

	auto* dialogWidget = CreateGWidget<UBWidget_Dialog>(dialogPath, false, ZOrder);
	/*
	if (dialogWidget)
	{
		dialogWidget->ShowDialogWidget(Title, Desc, DialogType, ButtonType);
		AddToViewport(dialogWidget, ZOrder);
	}
	*/

	return dialogWidget;
}

UBWidget_Dialog* ABHUDBase::ShowSystemDialogWidget(FString Title, FString Desc, EBUIPopupMessageButton ButtonType)
{
	/*
	FString dialogPath = TEXT("/Game/BluePrint/UI/BP_WidgetDialog");
	int32 ZOrder = 999999;

	if (SystemDialogWidget == nullptr)
	{
		SystemDialogWidget = CreateGWidget<UBWidget_Dialog>(dialogPath, false, ZOrder);
	}

	if (SystemDialogWidget != nullptr)
	{
		if (SystemDialogWidget->IsVisible() == false)
		{
			SystemDialogWidget->ShowDialogWidget(
				Title,
				Desc,
				EBUIPopupMessage::TitleAndMessage,
				ButtonType);

			SystemDialogWidget->SetInputMode(EInputMode::UIOnly);
			SystemDialogWidget->OnDialogCloseEventDelegate.BindLambda(
				[](UBWidget_Dialog* pDialog)
			{
				pDialog->SetInputMode(EInputMode::GameAndUI);
			});

			AddToViewport(SystemDialogWidget, ZOrder);
			SystemDialogWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
	*/

	return SystemDialogWidget;
}

void ABHUDBase::ShowFadeInOutPannel(float fadeInTime, float fadeOutTime, float fadeDelayTime)
{
	/*
	if (UGWidget_FadeInOut* widget = OpenUI<UGWidget_FadeInOut>(EBUIName::FadeInOut))
	{
		widget->ShowFadeInOut(fadeInTime, fadeOutTime, fadeDelayTime);
	}
	*/
}