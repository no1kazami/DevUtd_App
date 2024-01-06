#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MatchItem.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_MatchItem : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadHomeTeamLogoImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadHomeTeamLogoImage;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadAwayTeamLogoImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadAwayTeamLogoImage;

private:
	UPROPERTY( meta = (BindWidget) ) 
		UBButton* C_Btn_Match;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Comment;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Change;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_MatchDate;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Time;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Home;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Away;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Home;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Away;
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_UnderLine;

	FString _HomeTeamName;
	FString _AwayTeamName;
	E_MATCH_INFO_TYPE _MatchInfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_MAX;
	FST_MATCH_DATA _MatchData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetMainDataSchedule();
	void SetMainDataResult();
	void SetMatchItem(FST_MATCH_DATA matchData);
	void SetMatchInfoType( E_MATCH_INFO_TYPE matchInfoType );

private:
	UFUNCTION()
		void _OnSuccessDownLoadHomeTeamLogoImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadHomeTeamLogoImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadAwayTeamLogoImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadHomeAwayLogoImage( UTexture2DDynamic* texturl );

	UFUNCTION() void _OnClick_ItemBtn();
};
