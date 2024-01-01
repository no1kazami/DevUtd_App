// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WidgetLayoutLibrary.h"

#include "Util/Bigtamin_Enum.h"
#include "Util/Bigtamin_Struct.h"

#include "BButton.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/TimelineComponent.h"
#include "Components/EditableTextBox.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/CheckBox.h"
#include "Components/Overlay.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/SizeBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Spacer.h"
#include "Components/ScaleBox.h"
#include "BWidget.generated.h"

#ifdef Bind_Pressed_Function_Button
#undef Bind_Pressed_Function_Button
#endif // Bind_Pressed_Function_Button
#define Bind_Pressed_Function_Button(Object, FuncName)			\
		if (Object.IsValid())									\
		{														\
			ButtonDelegate_Pressed(this, Object, FuncName);		\
		};

#ifdef Bind_Released_Function_Button
#undef Bind_Released_Function_Button
#endif // Bind_Released_Function_Button
#define Bind_Released_Function_Button(Object, FuncName)			\
		if (Object.IsValid())									\
		{														\
			ButtonDelegate_Released(this, Object, FuncName);	\
		};

#ifdef Bind_Clicked_Function_Button
#undef Bind_Clicked_Function_Button
#endif // Bind_Clicked_Function_Button
#define Bind_Clicked_Function_Button(Object, FuncName)			\
		if (Object.IsValid())									\
		{														\
			ButtonDelegate_Clicked(this, Object, FuncName);		\
		};


UCLASS(BlueprintType, Blueprintable)
class BIGTAMIN_API UBWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	EBUIName WidgetUIName;
	int32 constructCount;

	UPROPERTY()
	UBWidget* OwnerPannel;

protected:
	FTimeline FadeTimeline;

	UPROPERTY(EditAnywhere, Category = B)
	UCurveLinearColor* FadeColorCurve;

	bool bValidWidget;

	E_MODE _PrevMode;

public:
	UBWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

	virtual void Init();
	virtual void Init(UBWidget* OwnerUI);
	virtual void OnShow();
	virtual void OnHide();
	virtual void OnClose() {}
	virtual bool _OnBackInput()
	{
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = G)
	virtual void OpenUI(EBUIName UIName);

	UFUNCTION(BlueprintCallable, Category = G)
	virtual void CloseUI();

	UTexture2D* GetTexture( FString strAddress );
	void DownLoadTexture_URL( FString textureURL, const TScriptDelegate<FWeakObjectPtr>& successDelegate, const TScriptDelegate<FWeakObjectPtr>& failDelegate );

	class ABGameMode* GetGameMode();
	class ABigtamin_PlayerController* GetPlayerController();
	static UClass* CreateUserWidgetClass(const FString& path);
	class ABHUDBase* GetGHUDBase();
	void SetAlwaysViewWidget(const bool bAlwaysView);

	UWidgetAnimation* GetWidgetAnimation(const FName& animationName);
	UUserWidget* GetChildWidgetWithName(const FName& widgetName);

	bool CheckViewport(int32 nCheckX, int32 nCheckY);

	void SetInputMode(EInputMode eMode);
	void SetPrevMode( E_MODE ePrevMode );
	E_MODE GetPrevMode();

	FString ChangeTimeUnit_ExcludeInSeconds(int64 nTime);
	FString ChangeTimeUnit(int64 nTime, bool bUntilDays);				// 남은시간표시(큰단위절삭)
	FString ChangeForTimeRecord(int64 nTime, bool bUntilDays);			// 시간표시(00:00)
	FString GetStringTime(int32 nTime);

	FText GetChatDate(int64 ChatTime);									// 시간표시(00:00pm->어제->00일전)
	bool IsLeapYearCount(int32 nYear);									// 윤년이냐?

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void FadeInit();
	void FadeInOut(bool isFadeIn, float duration);
	FString LineSafeToString(FString& str);

	template<class T>
	T* GetWidgetFromName_(FString InWidgetName)
	{
		T* Widget = Cast<T>(GetWidgetFromName(FName(*InWidgetName)));
		if (!Widget)
		{
			bValidWidget = false;
		}
		return Widget;
	}

public:
	template<class T>
	T *LoadTextureFromPath( const FString& texturePath )
	{
		if( texturePath.IsEmpty() )
			return nullptr;

		const FString textureFullPath = GetUIDirectoryPath( texturePath );
		return Cast<T>( StaticLoadObject( T::StaticClass(), nullptr, *(textureFullPath) ) );
	}

	const FString GetUIDirectoryPath( )
	{
		return TEXT( "/Game/Texture/UI/" );
	}
	const FString GetUIDirectoryPath( FString AddPath )
	{
		return GetUIDirectoryPath() + AddPath;
	}

private:
	UFUNCTION()
	void FadeInOutProgress(FLinearColor value);
};

template<class T>
T* CreateUserWidget(UWorld* world, FString& path)
{
	UClass* widgetClass = UBWidget::CreateUserWidgetClass(path);
	if (!widgetClass)
	{
		return nullptr;
	}

	T* newWidget = CreateWidget<T>(world, widgetClass);
	if (!newWidget)
	{
		//UE_LOG( LogFBM, Error, TEXT("%s : widget Create Fail"), *path);
		return nullptr;
	}

	return newWidget;
}