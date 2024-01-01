// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_Top.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_Top : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
	UWidgetSwitcher* C_WidgetSwitcher_Top;
	UPROPERTY( meta = (BindWidget) )
	UWidgetSwitcher* C_WS_TopBtn;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock*	C_Txt_TopTitle1;

	UPROPERTY( meta = (BindWidget) )
	UBButton* C_Btn_Menu;
	UPROPERTY( meta = (BindWidget) )
	UBButton* C_Btn_Back;

	UPROPERTY( meta = (BindWidget) )
	UBButton* C_Btn_MyInfo_Search;
	UPROPERTY( meta = (BindWidget) )
	UTextBlock* C_Txt_TopTitle2;

	UPROPERTY( meta = (BindWidget) )
		UEditableText* C_ET_Search;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Search;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Search;

	E_MODE _CurTopMode = E_MODE::E_MODE_NONE;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void ChangeTopMode( E_MODE changeMode );
	void ChangeTopMode_Lobby( E_LOBBY_MODE changeLobbyMode );

	void SetTopSurvey( int32 nCurPage, int32 nTotalPage );

	UFUNCTION()
		void SetSearchText( FText searchText, bool isEmpty = false );

private:
	UFUNCTION()
		void _OnClick_MenuBtn();
	UFUNCTION()
		void _OnClick_BackBtn();

	UFUNCTION()
		void _OnClick_MyInfoSearchBtn();
	UFUNCTION()
		void _OnClick_SearchBtn();

	UFUNCTION() 
		void _OnClick_SearchImg();

	UFUNCTION()
		void _OnTextChangeSearch( const FText& InText );
	UFUNCTION()
		void _OnTextChangeSearchFocus( const FText& InText, ETextCommit::Type commitMethod );
};
