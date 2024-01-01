// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bigtamin_Enum.h"
#include "FBMUtil.generated.h"


UCLASS()
class BIGTAMIN_API UFBMUtil : public UObject
{
	GENERATED_BODY()

public:
	static FText BrandNameText( E_BRAND_TYPE eBrandType );
	static FText ProductNameText( int32 bootsIndex, bool multiLine = false );
	static FText ProductNameText_DB( int32 bootsIndex, bool multiLine = false );
	static FString BrandLogoPath( E_BRAND_TYPE eBrandType );
	static FText CollectionText( E_COLLECTION_TYPE collectionType );
	static FText ModelText( E_MODEL_TYPE modelType );
	static FText StudsNameText( E_STUDS_TYPE eStudsType );
	static FText UpperNameText( E_UPPER_TYPE eUpperType );
	static FText SiloNameText( E_SILO_TYPE eSiloType );
	static FText GroundNameText( E_GROUND_TYPE eGroundType );
	static FText SizeText( int weightSize );
	static FText BallOfFootText( int weightBallOfFoot );
	static FText HeightOfFootText( int weightHeightOfFoot );
	static FText LengthText( int weightLength );
	static FString ShopLogoPath( E_CRAWLING_WEBPAGE shopType );
	static FText ShopNameText( E_CRAWLING_WEBPAGE shopType );
	static E_CRAWLING_WEBPAGE ShopNameEnum( FString shopName );
	static FString ChartDotPath( bool isPressDown );
	static FString MedalImgPath( E_MEDAL_TYPE eMedalType );
};
