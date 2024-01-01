// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Util/DataTable/DataTable_String.h"
#include "Util/DataTable/DataTable_Survey.h"
#include "Util/DataTable/DataTable_FootBallBoots.h"
#include "Util/Bigtamin_Enum.h"
#include "UI/Base/BWidget.h"
#include "GlobalAccessMgr.h"
#include "Firebase/FireBaseManager.h"
#include "Bigtamin_GameInstance.generated.h"

#define SIZE_WIDGET_STACK	30

class ABHUDBase;
class UBWidget_Warning;
class UBWidget_Loading;
class UFBM_SaveGame;

UCLASS()
class BIGTAMIN_API UBigtamin_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		bool bIsPermissionSuccess = false;
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		bool bIsSaveFileSuccess = false;
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		UFBM_SaveGame* DevUtdSaveGame = nullptr;

protected:
	UPROPERTY( Category = "CurInfo", BlueprintReadOnly, VisibleAnywhere )
		E_MODE _CurMode;
	UPROPERTY( Category = "CurInfo", BlueprintReadOnly, VisibleAnywhere )
		int32 _CurSelectBootsIndex;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		int32 _CompareBootsIndex1 = 0;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		int32 _CompareBootsIndex2 = 0;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		int32 _CompareBootsIndex3 = 0;

	UPROPERTY( Category = "CurInfo", BlueprintReadOnly, VisibleAnywhere )
		FString _CurSelectPlayerName;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		FString _ComparePlayerName1;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		FString _ComparePlayerName2;
	UPROPERTY( Category = "CompareInfo", BlueprintReadOnly, VisibleAnywhere )
		FString _ComparePlayerName3;

private:
	UPROPERTY( EditDefaultsOnly, Category = B_GameInstance )
		TSubclassOf<class UGlobalAccessMgr> _GlobalAccessMgrClass;
	UPROPERTY()
		class UGlobalAccessMgr* _GlobalAccessMgr;

	UPROPERTY()
		UDataTable* _StringInfoTable;
	UPROPERTY()
		UDataTable* _SurveyInfoTable;
	UPROPERTY()
		UDataTable* _BootsInfoTable;

	UPROPERTY() 
		TArray<UBWidget*> _BackInputStack;

	UPROPERTY()
		UBWidget_Warning* _WarningUMG;
	UPROPERTY()
		UBWidget_Loading* _LoadingUMG;

	UPROPERTY()
		TMap<FString, UTexture2DDynamic*> _DownLoadBootsImage;

	UPROPERTY()
		TMap<FString, UTexture2DDynamic*> _DownLoadLogoImage;

	UPROPERTY()
		TMap<FString, UTexture2DDynamic*> _DownLoadPlayerImage;

public:
	UBigtamin_GameInstance(const FObjectInitializer& ObjectInitializer);
	~UBigtamin_GameInstance();

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	ABHUDBase* GetHUDBase();
	class ABGameMode* GetGameMode();
	class ABigtamin_PlayerController* GetPlayerController();

	template<class T>
	T* GetGlobalAccessUnit() const
	{
		if( _GlobalAccessMgr )
			return _GlobalAccessMgr->Get<T>();

		return nullptr;
	}

	void InitDataTable();
	void BackInput();
	void AddBackInput( UBWidget* widget );
	UBWidget* GetBackInput( UBWidget* widget );
	int32 BackInputStackCount();
	bool IsPermissionSuccess() const;

	UFUNCTION( BlueprintCallable, Category = "StringInfo" )
		FST_StringInfoData GetStringInfoRowByName( FName pName, bool& bResult );

	UFUNCTION( BlueprintCallable, Category = "StringInfo" )
		FText GetStringByTable( int32 nStrIndex );

	UFUNCTION( BlueprintCallable, Category = "SurveyInfo" )
		FST_SurveyInfoData GetSurveyInfoRowByName( int32 nSurveyIndex, bool& bResult );

	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		FST_FootBallBootsData GetBootsInfo( int32 bootsIndex, bool& bResult );
	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		void SearchBootsInfo( FText searchText, TArray<int>& OUT_BootsInexInfoByBrand );

	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		void GetBootsIndexInfoByBrand( E_BRAND_TYPE brandType, TArray<int>& OUT_BootsInexInfoByBrand );

	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		void GetBootsIndexInfoByBrandSort( TArray<E_BRAND_TYPE> brandType, E_SORT_TYPE sortType, TArray<int>& OUT_BootsInexInfoByBrandSort );

	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		void GetAllBootsBrand( TArray<E_BRAND_TYPE>& OUT_BootsBrand );

	UFUNCTION( BlueprintCallable, Category = "footBallBootsInfo" )
		void GetBootsIndexInfoByFiltering( TArray<int>& OUT_BootsInexInfoByFiltering, FST_BOOTS_FILTER_INFO filterData, E_SORT_TYPE sortType = E_SORT_TYPE::E_SORT_TYPE_NONE, E_BRAND_TYPE curBrandType = E_BRAND_TYPE::E_BRAND_TYPE_ALL );

	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		void SetCurMode( E_MODE eCurMode );
	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		E_MODE GetCurMode();

	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		void SetCurSelectBootsIndex( int32 selectBootsIndex );
	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		int32 GetCurSelectBootsIndex();

	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		void InitCompareBootsIndex();
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool AddCompareBootsIndex( const int32 bootsIndex );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool RemoveCompareBootsSlot( const int32 slotIndex );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		int32 GetCompareBootsIndex( const int32 slotIndex );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		int32 GetCompareBootsSlotCount();
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool IsAlReadyAddSlot( const int32 bootsIndex );

	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		void SetCurSelectPlayerName( FString selectPlayerName );
	UFUNCTION( BlueprintCallable, Category = "CurInfo" )
		FString GetCurSelectPlayerName();

	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		void InitComparePlayerName();
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool AddComparePlayerName( const FString PlayerName );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool RemoveComparePlayerNameSlot( const int32 slotIndex );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		FString GetComparePlayerName( const int32 slotIndex );
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		int32 GetComparePlayerNameSlotCount();
	UFUNCTION( BlueprintCallable, Category = "CompareInfo" )
		bool IsAlReadyAddPlayerNameSlot( const FString PlayerName );

	UFUNCTION( BlueprintCallable, Category = "Warning" )
		bool PlayWarningUI( const int32 warningIndex );

	UFUNCTION( BlueprintCallable, Category = "Loading" )
		void PlayLoadingUI( const bool isLoading );

	UFUNCTION()
		void SetDownLoadBootsImage(FString bootsID, UTexture2DDynamic* downloadTextrure );

	UFUNCTION()
		UTexture2DDynamic* GetDownLoadBootsImage( FString bootsID );

	UFUNCTION()
		void SetDownLoadTeamLogoImage( FString teamName, UTexture2DDynamic* downloadTextrure );
	UFUNCTION()
		UTexture2DDynamic* GetDownLoadTeamLogoImage( FString teamName );
	UFUNCTION()
		void SetDownLoadPlayerImage( FString playerName, UTexture2DDynamic* downloadTextrure );
	UFUNCTION()
		UTexture2DDynamic* GetDownLoadPlayerImage( FString playerName );
};

class UGameInstanceProxy
{
public:

	UGameInstanceProxy() :
		GameInstance(NULL)
	{}

	inline UBigtamin_GameInstance* operator->()
	{
		// GInst is changed often on the game thread when in PIE, accessing on any other thread is going to be a race condition
		// In general, the rendering thread should not dereference UObjects, unless there is a mechanism in place to make it safe	
		//checkSlow(IsInGameThread());
		return GameInstance;
	}

	inline const UBigtamin_GameInstance* operator->() const
	{
		//checkSlow(IsInGameThread());
		return GameInstance;
	}

	inline UBigtamin_GameInstance& operator*()
	{
		//checkSlow(IsInGameThread());
		return *GameInstance;
	}

	inline const UBigtamin_GameInstance& operator*() const
	{
		//checkSlow(IsInGameThread());
		return *GameInstance;
	}

	inline UGameInstanceProxy& operator=(UBigtamin_GameInstance* InWorld)
	{
		GameInstance = InWorld;
		return *this;
	}

	inline UGameInstanceProxy& operator=(const UGameInstanceProxy& InProxy)
	{
		GameInstance = InProxy.GameInstance;
		return *this;
	}

	inline bool operator==(const UGameInstanceProxy& Other) const
	{
		return GameInstance == Other.GameInstance;
	}

	inline operator UBigtamin_GameInstance*() const
	{
		//checkSlow(IsInGameThread());
		return GameInstance;
	}

	inline UBigtamin_GameInstance* GetReference()
	{
		//checkSlow(IsInGameThread());
		return GameInstance;
	}

private:
	UBigtamin_GameInstance* GameInstance;
};


extern BIGTAMIN_API class UGameInstanceProxy GInst;
