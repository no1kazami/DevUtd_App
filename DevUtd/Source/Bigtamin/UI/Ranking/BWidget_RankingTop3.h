#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_RankingTop3.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_RankingTop3 : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Top3_Title;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Medal1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Val1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Medal2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Val2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Medal3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Team3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Val3;

	FString _NowYear;
	
public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( const E_RANKING_TYPE rankingType, FString nowYear );

private:
	void _SetDataGoal( FString nowYear );
	void _SetDataAssist( FString nowYear );
	void _SetDataPoint( FString nowYear );
	void _SetDataGame( FString nowYear );
};
