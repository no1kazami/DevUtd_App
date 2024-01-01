#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_PlayerSlot.generated.h"


UCLASS()
class BIGTAMIN_API UBWidget_PlayerSlot : public UBWidget
{
	GENERATED_BODY()
public:
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage1;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage1;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage2;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage2;
	TScriptDelegate <FWeakObjectPtr> OnSuccessDownLoadPlayerImage3;
	TScriptDelegate <FWeakObjectPtr> OnFailDownLoadPlayerImage3;

private:
	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Player1;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person1;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name1;

	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Player2;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person2;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name2;

	UPROPERTY( meta = (BindWidget) )
		UVerticalBox* C_VB_Player3;
	UPROPERTY( meta = (BindWidget) )
		UImage* C_Img_Person3;
	UPROPERTY( meta = (BindWidget) )
		UTextBlock* C_Txt_Name3;

	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Player1;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Player2;
	UPROPERTY( meta = (BindWidget) )
		UBButton* C_Btn_Player3;

	FString _PlayerName1;
	FString _PlayerName2;
	FString _PlayerName3;	

public:
	virtual void Init() override;
	virtual void OnClose() override;

	void SetData( TArray<FString> PlayerNames );
	void OpenPlayerDetail( FString playerName );
	FString GetPlayerName( FString inNamne );

private:
	UFUNCTION() void _OnSuccessDownLoadPlayerImage1( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage1( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnSuccessDownLoadPlayerImage2( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage2( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnSuccessDownLoadPlayerImage3( UTexture2DDynamic* texturl );
	UFUNCTION() void _OnFailDownLoadPlayerImage3( UTexture2DDynamic* texturl );

	UFUNCTION() void _OnClick_PlayerSlot1();
	UFUNCTION() void _OnClick_PlayerSlot2();
	UFUNCTION() void _OnClick_PlayerSlot3();
};
