#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_PlayerCompare.generated.h"

class UBWidget_Top;

UCLASS()
class BIGTAMIN_API UBWidget_PlayerCompare : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadCompareImage3;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadCompareImage3;
	
private:
	UPROPERTY( meta = (BindWidget) )
		UBWidget_Top* BP_Top_PlayerCompare_UMG;

	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Product3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Goal1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Goal2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Goal3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareGoal2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareGoal3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Goal_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Goal_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Assist1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Assist2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Assist3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareAssist2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareAssist3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Assist_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Assist_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_TotalPoint1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_TotalPoint2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_TotalPoint3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareTotalPoint2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareTotalPoint3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_TotalPoint_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_TotalPoint_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Attendance1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Attendance2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Attendance3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareAttendance2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareAttendance3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Attendance_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Attendance_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Mvp1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Mvp2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Mvp3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareMvp2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareMvp3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Mvp_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Mvp_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Goal1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Goal2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Goal3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankGoal2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankGoal3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Goal_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Goal_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Assist1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Assist2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Assist3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankAssist2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankAssist3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Assist_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Assist_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Attendance1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Attendance2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_Attendance3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankAttendance2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankAttendance3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Attendance_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_Attendance_Arrow3;

	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_TotalPoint1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_TotalPoint2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Rank_TotalPoint3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankTotalPoint2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_CompareRankTotalPoint3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_TotalPoint_Arrow2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Rank_TotalPoint_Arrow3;


	UWidgetAnimation* _Ani_CompareOpen;
	FName _Ani_CompareOpenName = "Ani_Compare_Open";
	UWidgetAnimation* _Ani_CompareClose;
	FName _Ani_CompareCloseName = "Ani_Compare_Close";

	FString _ProductID1;
	FString _ProductID2;
	FString _ProductID3;

	int32 _GoalValue = 0;
	int32 _AssistValue = 0;
	int32 _TotalPointValue = 0;
	int32 _AttendanceValue = 0;
	int32 _MvpValue = 0;
	int32 _RankGoalValue = 0;
	int32 _RankAssistValue = 0;
	int32 _RankTotalPointValue = 0;
	int32 _RankAttendanceValue = 0;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void OnAnimationFinished_Implementation( const UWidgetAnimation* Animation ) override;

	void PlayCompareOpenAni( const bool isOpen );

protected:
	virtual bool _OnBackInput() override;
	void _InitPlayerCompare();
	void _ClearPlayerCompareUI();
	void _SetPlayerCompareUI();

	UFUNCTION()
		void _OnSuccessDownLoadCompareImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadCompareImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage2( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnSuccessDownLoadCompareImage3( UTexture2DDynamic* texturl );
	UFUNCTION()
		void _OnFailDownLoadCompareImage3( UTexture2DDynamic* texturl );
};
