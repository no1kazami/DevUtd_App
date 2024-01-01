#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ResultDetail.generated.h"


class UBWidget_Top;
class UBWidget_MatchItem;

UCLASS()
class BIGTAMIN_API UBWidget_ResultDetail : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_Top* BP_Top_MainResultDetail_UMG;
	UPROPERTY( meta = (BindWidget) ) UBWidget_MatchItem* BP_MatchItem_UMG;
	UPROPERTY( meta = (BindWidget) )   UScrollBox* C_SB_Item;

	UWidgetAnimation* _Ani_ResultDetailOpen;
	FName _Ani_ResultDetailOpenName = "Ani_ResultDetail_Open";
	UWidgetAnimation* _Ani_ResultDetailClose;
	FName _Ani_ResultDetailCloseName = "Ani_ResultDetail_Close";

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( FST_MATCH_DATA matchData );
	void PlayResultDetailOpenAni( const bool isOpen );

protected:
	virtual bool _OnBackInput() override;
	
};
