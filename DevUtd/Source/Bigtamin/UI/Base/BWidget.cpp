// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget.h"
#include "Bigtamin.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "GameMode/BGameMode.h"
#include "PlayerController/Bigtamin_PlayerController.h"
#include "UI/Base/BButton.h"
#include "UI/Base/BHUDBase.h"
#include "Blueprint/AsyncTaskDownloadImage.h"

#include <time.h>


UBWidget::UBWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bValidWidget(true)
{

}

void UBWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FadeTimeline.TickTimeline(InDeltaTime);
}

void UBWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTree)
	{
		WidgetTree->ForEachWidget([&](UWidget* Widget) {
			if (UBButton* btn = Cast<UBButton>(Widget))
			{
				if (btn->ButtonPressSound >= 0)
					btn->RegistDefaultPressSound();
			}
		});
	}
}

void UBWidget::Init()
{
	SetPrevMode( GInst->GetCurMode() );
}

void UBWidget::Init(UBWidget* OwnerUI)
{
	OwnerPannel = OwnerUI;

	Init();
}

void UBWidget::BeginDestroy()
{
	Super::BeginDestroy();

	if (WidgetTree)
	{
		WidgetTree->ForEachWidget([&](UWidget* Widget) {
			if (UBButton* btn = Cast<UBButton>(Widget))
			{
				btn->UnregistDefaultPressSound();
			}
		});
	}
}

void UBWidget::OpenUI(EBUIName UIName)
{
	if (ABHUDBase* hudBase = GetGHUDBase())
	{
		hudBase->OpenUI<UBWidget>(UIName);
	}
}

void UBWidget::CloseUI()
{
	if (ABHUDBase* hudBase = GetGHUDBase())
	{
		hudBase->CloseUI(this);
	}
}

void UBWidget::OnShow()
{
}

void UBWidget::OnHide()
{
}

ABGameMode* UBWidget::GetGameMode()
{
	ABGameMode* gameMode = Cast<ABGameMode>(GetWorld()->GetAuthGameMode());
	return gameMode;
}

void UBWidget::FadeInit()
{
	// FadeColorCurve 코드상에서 만들 수도 있습니다
}

void UBWidget::FadeInOut(bool isFadeIn, float duration)
{
	// 현재 duration 은 설정할 수 없습니다.

	if (!FadeColorCurve)
	{
		return;
	}

	FOnTimelineLinearColor progressFunction;
	progressFunction.BindUFunction(this, FName("FadeInOutProgress"));

	FadeTimeline.AddInterpLinearColor(FadeColorCurve, progressFunction);
	FadeTimeline.SetLooping(false);

	if (isFadeIn)
		FadeTimeline.PlayFromStart();
	else
		FadeTimeline.ReverseFromEnd();
}

void UBWidget::FadeInOutProgress(FLinearColor value)
{
	SetColorAndOpacity(value);
}

FString UBWidget::LineSafeToString(FString& str)
{
	return str.Replace(TEXT("\\n"), LINE_TERMINATOR);
}

UWidgetAnimation* UBWidget::GetWidgetAnimation(const FName& animationName)
{
	if (UWidgetBlueprintGeneratedClass* BGClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		for (UWidgetAnimation* animation : BGClass->Animations)
		{
			if (animation->MovieScene->GetFName() == animationName)
				return animation;
		}
	}

	return nullptr;
}

UUserWidget* UBWidget::GetChildWidgetWithName(const FName& widgetName)
{
	UUserWidget* childWidget = nullptr;
	TArray<UWidget*> children;

	WidgetTree->GetAllWidgets(children);
	for (int32 i = 0; i < children.Num(); ++i)
	{
		UUserWidget* widget = Cast<UUserWidget>(children[i]);
		if (widget && widget->IsValidLowLevel() && widget->GetFName() == widgetName)
		{
			childWidget = widget;
			break;
		}
	}

	return childWidget;
}

bool UBWidget::CheckViewport(int32 nCheckX, int32 nCheckY)
{
	int32 VIEWPORT_SIZE_X = 0.0f;
	int32 VIEWPORT_SIZE_Y = 0.0f;

	//GInst->GetPlayerController()->GetViewportSize(VIEWPORT_SIZE_X, VIEWPORT_SIZE_Y);
	//UE_LOG(LogG, Log, TEXT("[UBWidget] CheckViewport - %d, %d, Check X - %d, Check Y -%d"), VIEWPORT_SIZE_X, VIEWPORT_SIZE_Y, nCheckX, nCheckY);

	if (nCheckX < 0 || VIEWPORT_SIZE_X < nCheckX)
		return false;

	if (nCheckY < 0 || VIEWPORT_SIZE_Y < nCheckY)
		return false;

	return true;
}

void UBWidget::SetInputMode(EInputMode eMode)
{
	switch (eMode)
	{
	case EInputMode::UIOnly:
	{
		FInputModeUIOnly Mode;
		if (GetPlayerController())
			GetPlayerController()->SetInputMode(Mode);
	}
	break;
	case EInputMode::GameOnly:
	{
		FInputModeGameOnly Mode;
		if (GetPlayerController())
			GetPlayerController()->SetInputMode(Mode);
	}
	break;
	case EInputMode::GameAndUI:
	{
		FInputModeGameAndUI Mode;
		if (GetPlayerController())
			GetPlayerController()->SetInputMode(Mode);
	}
	break;
	}
}

void UBWidget::SetPrevMode( E_MODE ePrevMode )
{
	_PrevMode = ePrevMode;
}

E_MODE UBWidget::GetPrevMode()
{
	return _PrevMode;
}

FString UBWidget::ChangeTimeUnit_ExcludeInSeconds(int64 nTime)
{
	FString strTime;

	int64 nMinutes = nTime / 60;
	int64 nHours = nMinutes / 60;
	int64 nDays = nHours / 24;

	/*
	if (nDays > 0)
	{
		strTime = FString::FromInt(nDays) + GLOCSTRING(1000120);
	}
	else if (nHours > 0)
	{
		strTime = FString::FromInt(nHours) + GLOCSTRING(1000121);
	}
	else if (nMinutes > 0)
	{
		strTime = FString::FromInt(nMinutes) + GLOCSTRING(1000122);
	}
	else
	{
		strTime = FString::FromInt(1) + GLOCSTRING(1000122);
	}
	*/

	return strTime;
}

FString UBWidget::ChangeTimeUnit(int64 nTime, bool bUntilDays)
{
	FString strTime;

	int64 nMinutes = nTime / 60;
	int64 nHours = nMinutes / 60;
	int64 nDays = nHours / 24;

	/*
	if (true == bUntilDays && nDays)
	{
		strTime = FString::FromInt(nDays) + GLOCSTRING(1000120);
		return strTime;
	}

	if (nHours)
	{
		strTime = FString::FromInt(nHours) + GLOCSTRING(1000121);
	}
	else if (nMinutes)
	{
		strTime = FString::FromInt(nMinutes) + GLOCSTRING(1000122); // 분
	}
	else
	{
		strTime = FString::FromInt(nTime) + GLOCSTRING(1000074);	// 초
	}

	*/

	// UE_LOG(LogG, Log, TEXT("[UGWidget_WorldMap] ChaneTimeUnit() %s"), *strTime);
	return strTime;
}

FString UBWidget::ChangeForTimeRecord(int64 nTime, bool bUntilDays)
{
	FString strColon = ":";
	FString strRemain1, strRemain2;
	FString strTime;

	int64 nMinutes = nTime / 60;
	int32 nMinutesRemain = nTime % 60;

	int64 nHours = nMinutes / 60;
	int32 nHoursRemain = nMinutes % 60;

	int64 nDays = nHours / 24;
	int32 nDaysRemain = nHours % 24;

	/*
	if (true == bUntilDays && nDays)
	{
		strTime = FString::FromInt(nDays) + GLOCSTRING(1000120);
		return strTime;
	}

	// 시:남은분:남은초
	if (nHours)
	{
		strRemain1 = 0 < nHoursRemain ? GetStringTime(nHoursRemain) : GetStringTime(0);
		strRemain2 = 0 < nMinutesRemain ? GetStringTime(nMinutesRemain) : GetStringTime(0);
		strTime = GetStringTime(nHours) + strColon + strRemain1 + strColon + strRemain2;
	}
	// 분:남은초
	else if (nMinutes)
	{
		strRemain2 = 0 < nMinutesRemain ? GetStringTime(nMinutesRemain) : GetStringTime(0);
		strTime = GetStringTime(nMinutes) + strColon + strRemain2;
	}
	// 00:초
	else
	{
		strTime = GetStringTime(0) + strColon + GetStringTime(nTime);
	}

	//UE_LOG(LogG, Log, TEXT("[UGWidget_WorldMap] ChaneTimeUnit() %s"), *strTime);

	*/
	return strTime;
}

FString UBWidget::GetStringTime(int32 nTime)
{
	return FString::Printf(TEXT("%02d"), nTime);
}

FText UBWidget::GetChatDate(int64 ChatTime)
{
	// 현재 시간
	time_t timer;
	timer = time(NULL);    // 현재 시각을 초 단위로 얻기

	tm convertToday{ 0, };
#ifdef _WIN64
	localtime_s(&convertToday, &timer);
#else
	localtime_r(&timer, &convertToday);
#endif

	int32 TodayYear = convertToday.tm_year + 1900;
	int32 TodayYDay = convertToday.tm_yday;

	// 채팅 시간
	time_t chattimer;
	chattimer = static_cast<time_t>(ChatTime); // time(NULL);    // 현재 시각을 초 단위로 얻기

	tm convertChatTime{ 0, };
#ifdef _WIN64
	localtime_s(&convertChatTime, &chattimer);
#else
	localtime_r(&chattimer, &convertChatTime);
#endif
	int32 ChatTimeYear = convertChatTime.tm_year + 1900;
	int32 ChatTimeYDay = convertChatTime.tm_yday;
	int32 ChatTimeHour = convertChatTime.tm_hour;
	int32 ChatTimeMinute = convertChatTime.tm_min;

	//convertChatTime.

	FText txtDay;
	int32 nStringIndex = 0;
	/*
	// ChatTimeYear이 같은 해일때
	if (ChatTimeYear == TodayYear)
	{
		// 오늘
		if (ChatTimeYDay == TodayYDay)
		{
			if (0 <= ChatTimeHour && ChatTimeHour <= 12)
			{
				nStringIndex = 1007010;
			}
			else
			{
				ChatTimeHour -= 12;
				nStringIndex = 1007011;
			}

			FString strMinute = GetStringTime(ChatTimeMinute);
			txtDay = GLOCTEXTFMT(1007009, ChatTimeHour, FText::FromString(strMinute), GLOCTEXT(nStringIndex));
		}
		// 어제
		else if (ChatTimeYDay + 1 == TodayYDay)
		{
			txtDay = GLOCTEXT(1007007);
		}
		// 00일전
		else if (ChatTimeYDay + 1 < TodayYDay)
		{
			int32 nFewDaysAgo = TodayYDay - ChatTimeYDay;
			FString strTime = FString::FromInt(nFewDaysAgo) + GLOCSTRING(1007006);
			txtDay = FText::FromString(strTime);
		}
	}
	// ChatTimeYear이 작년 일때
	else if (ChatTimeYear + 1 == TodayYear)
	{
		int32 NUM_365 = IsLeapYearCount(ChatTimeYear) ? 366 : 365;
		int32 nCalChatTime = (NUM_365 - ChatTimeYDay) + TodayYDay;

		if (1 == nCalChatTime)
		{
			txtDay = GLOCTEXT(1007007);
		}
		else
		{
			int32 nFewDaysAgo = nCalChatTime;
			FString strTime = FString::FromInt(nFewDaysAgo) + GLOCSTRING(1007006);
			txtDay = FText::FromString(strTime);
		}
	}
	// 2년 이상은 -ㅅ- 나중에 생각하자
	else
	{
	}

	//UE_LOG(LogG, Log, TEXT("[UGWidget_ChatLine] SetChatDate() txtDay - %s"), *txtDay.ToString());
	*/
	return txtDay;
}

// https://blog.naver.com/kj9966/220981503290
bool UBWidget::IsLeapYearCount(int32 nYear)
{
	if ((nYear % 400 == 0) || (nYear % 4 == 0 && nYear % 100 != 0))
	{
		return true;
	}

	return false;
}

void UBWidget::SetAlwaysViewWidget(const bool bAlwaysView)
{
	if (ABHUDBase* hudBase = GetGHUDBase())
		hudBase->SetAlwaysViewWidget(this, bAlwaysView);
}

UClass* UBWidget::CreateUserWidgetClass(const FString& path)
{
	FString outPath = path;
	UClass* widgetClass = ConstructorHelpersInternal::FindOrLoadClass(outPath, UBWidget::StaticClass());
	if (!widgetClass)
	{
		//UE_LOG(LogG, Error, TEXT("%s : Not found widget"), *outPath);
		return nullptr;
	}

	return widgetClass;
}

ABigtamin_PlayerController * UBWidget::GetPlayerController()
{
	APlayerController* playerController = GetOwningPlayer();
	if (playerController)
		return Cast<ABigtamin_PlayerController>(playerController);

	return nullptr;
}

class ABHUDBase* UBWidget::GetGHUDBase()
{
	ABHUDBase* gHud = nullptr;

	APlayerController* playerController = GetOwningPlayer();
	if (playerController)
	{
		AHUD* hud = playerController->GetHUD();
		if (hud)
			gHud = Cast<ABHUDBase>(hud);
	}

	return gHud;
}

UTexture2D* UBWidget::GetTexture( FString strAddress )
{
	//FString pathPrefix = TEXT( "_OriginalTex_/Ingame/" );
	//FString texturepath = pathPrefix + strAddress;
	return LoadTextureFromPath<UTexture2D>( strAddress );
}

void UBWidget::DownLoadTexture_URL( FString textureURL, const TScriptDelegate<FWeakObjectPtr>& successDelegate, const TScriptDelegate<FWeakObjectPtr>& failDelegate )
{
	UAsyncTaskDownloadImage* taskDownLoadImage = UAsyncTaskDownloadImage::DownloadImage( textureURL );
	if( taskDownLoadImage != nullptr )
	{
		if( taskDownLoadImage->OnSuccess.IsBound() == false )
		{
			taskDownLoadImage->OnSuccess.Add( successDelegate );
		}
		if( taskDownLoadImage->OnFail.IsBound() == false )
		{
			taskDownLoadImage->OnFail.Add( failDelegate );
		}
	}
}
