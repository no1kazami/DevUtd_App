#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "UI/Base/BWidget_SwipeScroll.h"
#include "UI/Main/BWidget_MainCategory.h"
#include "BWidget_NewMain.generated.h"

class UBWidget_Top;
class UBWidget_MainMatchSlot;
class UBWidget_MainRankingSlot;

UCLASS()
class BIGTAMIN_API UBWidget_NewMain : public UBWidget_SwipeScroll
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner1;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner3;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner4;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner5;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner6;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner7;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner8;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner9;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadImageMainBanner10;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadImageMainBanner;

	UPROPERTY( meta = (BindWidget) ) UBWidget_Top* BP_Top_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainCategory* BP_MainCategory_UMG;

private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainMatchSlot* BP_ScheduleSlot_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainMatchSlot* BP_ResultSlot_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Attendance_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Goal_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Assist_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Point_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Year_Mvp_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MainRankingSlot* BP_Rank_Year_King_UMG;

	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Schedule;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Schedule;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Result;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Result;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_Ranking;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Ranking;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_TeamInfo;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_TeamInfo;

	UWidgetAnimation* _Ani_Quit;
	FName _Ani_QuitName = "Ani_Quit";
	UWidgetAnimation* _Ani_CategoryOpen;
	FName _Ani_CategoryOpenName = "Ani_CategoryOpen";
	UWidgetAnimation* _Ani_CategoryClose;
	FName _Ani_CategoryCloseName = "Ani_CategoryClose";

	E_MAINCATEGORY_TYPE _CurMainCategoryType = E_MAINCATEGORY_TYPE::NONE;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;

	void ChangeMode( E_MODE changeMode );
	void PlayQuit();
	void PlayCategoryAni( const bool isOpen );

	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

protected:
	virtual void _OnClickSwipeScrollItem( int32 itemIndex ) override;

private:
	UFUNCTION()
		void _OnClick_Ranking();
	UFUNCTION()
		void _OnClick_Schedule();
	UFUNCTION()
		void _OnClick_Result();
	UFUNCTION()
		void _OnClick_TeamInfo();

	UFUNCTION()
		void _OnClickCategoryEvent( const E_MAINCATEGORY_TYPE mainCategoryType );

	UFUNCTION()
		void _OnClickMainBanner(const int32 bannerIndex);

	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner1( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner3( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner4( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner5( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner6( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner7( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner8( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner9( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadImageMainBanner10( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadImageMainBanner( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _SetBannerImg( UTexture2DDynamic* texturl, int32 bannerIndex );

	UFUNCTION()
		bool _CheckServerCheckTime();
	UFUNCTION()
		bool _CheckVersion();

	void _InitMainADBanner();

	void _InitSchedule();
	void _InitResult();
	void _InitRankAttendance();
	void _InitRankGoal();
	void _InitRankAssist();
	void _InitRankPoint();
	void _InitRankYearMvp();
	void _InitRankYearKing();
};
