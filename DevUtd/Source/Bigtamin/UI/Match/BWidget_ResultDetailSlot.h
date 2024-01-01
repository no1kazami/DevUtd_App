#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_ResultDetailSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_ResultDetailSlot : public UBWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Name_Home;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Stat_Home;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Name_Away;
	UPROPERTY( meta = (BindWidget) ) UTextBlock* C_Txt_Stat_Away;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( FString strHomeName, int32 homeGoal, int32 homeAssist, FString strAwayName, int32 awayGoal, int32 awayAssist );
	
};
