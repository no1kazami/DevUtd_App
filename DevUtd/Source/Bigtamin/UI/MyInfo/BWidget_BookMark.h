// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_BookMark.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_BookMark : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_BookMark_UMG;
	UPROPERTY( meta = (BindWidget) )
		UScrollBox*  C_ScrollBox_BookMark;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_NoBookMark;

	UWidgetAnimation* _Ani_BookmarkOpen;
	FName _Ani_BookmarkOpenName = "Ani_Bookmark_Open";
	UWidgetAnimation* _Ani_BookmarkClose;
	FName _Ani_BookmarkCloseName = "Ani_Bookmark_Close";

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void InitBookMark();
	void HandleBackInput();
	void PlayBookmarkOpenAni( const bool isBookmarkOpen );

protected:
	virtual bool _OnBackInput() override;
};
