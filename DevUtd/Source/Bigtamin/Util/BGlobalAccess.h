#pragma once

#include "Bigtamin_GameInstance.h"

#define GET_BTEXT(key)	GInst->GetStringByTable(key)
#define B_HUD GInst->GetHUDBase()
#define B_FIREBASE (GInst->GetGlobalAccessUnit<UFireBaseManager>())

#define DB_BOOTS_DATA 1

// Common colors.
const FLinearColor Color_White( 1.f, 1.f, 1.f );
const FLinearColor Color_Black( 0.f, 0.f, 0.f );
const FLinearColor Color_GrayFont( 0.135417f, 0.135417f, 0.135417f );
const FLinearColor Color_SoftGrayFont( 0.364583f, 0.364583f, 0.364583f );
const FLinearColor Color_StarBucksGrayFont( 0.045186f, 0.045186f, 0.045186f );
const FLinearColor Color_FilterGray( 0.880208f, 0.880208f, 0.8802086f );
const FLinearColor Color_BlueFont( 0.026241f, 0.048172f, 0.097587f );
const FLinearColor Color_SortSelectFont( 0.421875f, 0.250763f, 0.060853f );
const FLinearColor Color_Vitamin( 0.003347f, 0.520996f, 0.124772f );
const FLinearColor Color_Mineral( 0.f, 0.254152f, 0.491021f );
const FLinearColor Color_Essentital( 0.337164f, 0.099899f, 0.47932f );
const FLinearColor Color_Accessory( 0.745404f, 0.318547f, 0.009134f );
const FLinearColor Color_BootsSlot_White( 1.f, 1.f, 1.f );
const FLinearColor Color_BootsSlot_Gray( 0.904661f, 0.904661f, 0.887923f );
const FLinearColor Color_BootsCompare_Red( 1.f, 0.078125f, 0.078125f );
const FLinearColor Color_BootsCompare_Blue( 0.026111f, 0.063934f, 1.f );
const FLinearColor Color_TeamOrange( 1.f, 0.068793f, 0.f );
const FLinearColor Color_TeamGreen( 0.012655f, 0.229167f, 0.004914f );
const FLinearColor Color_RankBlue( 0.f, 0.011712f, 0.729167f );
