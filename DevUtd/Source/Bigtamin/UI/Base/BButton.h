// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "BButton.generated.h"

#ifdef ButtonDelegate_Pressed
#undef ButtonDelegate_Pressed
#endif // ButtonDelegate_Pressed
#define ButtonDelegate_Pressed(Target, Object, FuncName)			\
		{															\
			Object->OnPressed.RemoveDynamic(Target, FuncName);		\
			Object->OnPressed.AddDynamic(Target, FuncName);			\
		}

#ifdef ButtonDelegate_Released
#undef ButtonDelegate_Released
#endif // ButtonDelegate_Released
#define ButtonDelegate_Released(Target, Object, FuncName)			\
		{															\
			Object->OnReleased.RemoveDynamic(Target, FuncName);		\
			Object->OnReleased.AddDynamic(Target, FuncName);		\
		}

#ifdef ButtonDelegate_Clicked
#undef ButtonDelegate_Clicked
#endif // ButtonDelegate_Clicked
#define ButtonDelegate_Clicked(Target, Object, FuncName)			\
		{															\
			Object->OnClicked.RemoveDynamic(Target, FuncName);		\
			Object->OnClicked.AddDynamic(Target, FuncName);			\
		}




// 자기자신을 파라미터로 델리게이트 이벤트를 받고싶을때
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGButtonPressedEvent, const UBButton *, Sender);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGButtonReleasedEvent, const UBButton *, Sender);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGButtonClickedEvent, const UBButton *, Sender);

#define SafeBind_GDelegate_OnPressed(Target, Object, FuncName)	\
{															\
	Object->SetDelegate();									\
	Object->OnGPressed.RemoveDynamic(Target, FuncName);		\
	Object->OnGPressed.AddDynamic(Target, FuncName);		\
}
#define SafeBind_GDelegate_OnReleased(Target, Object, FuncName)	\
{															\
	Object->SetDelegate();									\
	Object->OnGReleased.RemoveDynamic(Target, FuncName);	\
	Object->OnGReleased.AddDynamic(Target, FuncName);		\
}
#define SafeBind_GDelegate_OnClicked(Target, Object, FuncName)	\
{															\
	Object->SetDelegate();									\
	Object->OnGClicked.RemoveDynamic(Target, FuncName);		\
	Object->OnGClicked.AddDynamic(Target, FuncName);		\
}

class UBWidget;

enum class EButtonWidgetStyle : uint8
{
	Normal = 0x0,
	Hovered,
	Pressed,
	Disabled,
};

UCLASS(meta = (DisplayName = "BButton"))
class BIGTAMIN_API UBButton : public UButton
{
	GENERATED_BODY()
public:
	// mute -1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GButton")
	int32 ButtonPressSound;

	FOnGButtonPressedEvent		OnGPressed;
	FOnGButtonReleasedEvent		OnGReleased;
	FOnGButtonClickedEvent		OnGClicked;


protected:
	TWeakObjectPtr<UImage> SubIconStateNormal;
	TWeakObjectPtr<UWidget> SubIconStatePressed;
	TWeakObjectPtr<UWidget> SubIconStateDisabled;

private:
	UBWidget *ParentWidget;

	bool ButtonDisabled;

	FSlateBrush NormalStyle;
	FSlateBrush PressedStyle;
	FSlateBrush DisabledStyle;
	
public:
	UBButton(const FObjectInitializer& ObjectInitializer);
	virtual ~UBButton();

public:	
	virtual void PostLoad() override;

	UFUNCTION()
	void RegistDefaultPressSound();
	UFUNCTION()
	void UnregistDefaultPressSound();
	UFUNCTION()
	void OnPlayPressSound();

	// Widget은 하나인데 특정값에 따라 이미지가 바뀔때 사용하자.
	// ex skill icon.. etc..
	bool SetButtonWidgetResource(EButtonWidgetStyle EventStyle, UObject *SrcObj)
	{
		if (SrcObj == nullptr)
			return false;

		switch (EventStyle)
		{
		case EButtonWidgetStyle::Normal:
			WidgetStyle.Normal.SetResourceObject(SrcObj);
			NormalStyle = WidgetStyle.Normal;
			break;
		case EButtonWidgetStyle::Hovered:
			WidgetStyle.Hovered.SetResourceObject(SrcObj);
			break;
		case EButtonWidgetStyle::Pressed:
			WidgetStyle.Pressed.SetResourceObject(SrcObj);
			PressedStyle = WidgetStyle.Pressed;
			break;
		case EButtonWidgetStyle::Disabled:
			WidgetStyle.Disabled.SetResourceObject(SrcObj);
			DisabledStyle = WidgetStyle.Disabled;
			break;
		}

		return true;
	}

	const bool IsDisabled() { return ButtonDisabled; }

	void SetDisabled(const bool bDisabled)
	{
		ButtonDisabled = bDisabled;

		SetIsEnabled(!ButtonDisabled);

		if (ButtonDisabled)
		{
			WidgetStyle.SetNormal(DisabledStyle);
			WidgetStyle.SetHovered(DisabledStyle);
			WidgetStyle.SetPressed(DisabledStyle);

			if (SubIconStateNormal.IsValid()) SubIconStateNormal.Get()->SetVisibility(ESlateVisibility::Hidden);
			if (SubIconStatePressed.IsValid()) SubIconStatePressed.Get()->SetVisibility(ESlateVisibility::Hidden);
			if (SubIconStateDisabled.IsValid()) SubIconStateDisabled.Get()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			WidgetStyle.SetNormal(NormalStyle);
			WidgetStyle.SetHovered(NormalStyle);
			WidgetStyle.SetPressed(PressedStyle);

			if (SubIconStateNormal.IsValid()) SubIconStateNormal.Get()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			if (SubIconStatePressed.IsValid()) SubIconStatePressed.Get()->SetVisibility(ESlateVisibility::Hidden);
			if (SubIconStateDisabled.IsValid()) SubIconStateDisabled.Get()->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	void SetDelegate();

	// 아이콘을 차일드로 가지고 변환시켜줄시에 일반 버튼이벤트 델리게이트가 아닌
	// SafeBind_GDelegate를 사용하자...
	void SetSubIcons(const TWeakObjectPtr<UImage> normalIcon, const TWeakObjectPtr<UImage> pressedIcon, const TWeakObjectPtr<UImage> DisabledIcon = nullptr)
	{
		SubIconStateNormal = normalIcon;
		SubIconStatePressed = pressedIcon;
		SubIconStateDisabled = DisabledIcon;
	}

private:

	UFUNCTION()		void _OnPressed();
	UFUNCTION()		void _OnReleased();
	UFUNCTION()		void _OnClicked();

};
