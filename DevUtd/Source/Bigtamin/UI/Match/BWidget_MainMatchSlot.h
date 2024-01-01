#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_MainMatchSlot.generated.h"

class UBWidget_MatchItem;

UCLASS()
class BIGTAMIN_API UBWidget_MainMatchSlot : public UBWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( meta = (BindWidget) ) UBWidget_MatchItem* BP_MatchItem_UMG;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Title;
	UPROPERTY( meta = (BindWidget) ) UBButton* C_Btn_More;

	E_MATCH_INFO_TYPE _MatchInfoType = E_MATCH_INFO_TYPE::E_MATCH_INFO_TYPE_MAX;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetDataSchedule();
	void SetDataResult();

private:
	UFUNCTION() void _OnClick_MoreBtn();
	
};
