#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_StadiumInfoSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_StadiumInfoSlot : public UBWidget
{
	GENERATED_BODY()	

public:
	DECLARE_EVENT_OneParam( UBWidget_StadiumInfoSlot, FOnClickStadiumInfoSlot, const FST_STADIUM_INFO_DATA )
	FOnClickStadiumInfoSlot OnClickStadiumInfoSlot;

private:
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_StadiumInfoSlot;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Title;

	FST_STADIUM_INFO_DATA _StadiumInfoData;

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetStadiumInfoSlotData( FST_STADIUM_INFO_DATA stadiumInfoSlotData );

private:
	UFUNCTION()
		void _OnClick_StadiumInfoSlot();
};
