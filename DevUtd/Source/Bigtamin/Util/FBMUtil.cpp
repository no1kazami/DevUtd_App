// Fill out your copyright notice in the Description page of Project Settings.

#include "FBMUtil.h"


FText UFBMUtil::BrandNameText( E_BRAND_TYPE eBrandType )
{
	switch ( eBrandType )
	{
	case E_BRAND_TYPE::E_BRAND_TYPE_ALL:
		return GET_BTEXT( 112 );
	case E_BRAND_TYPE::E_BRAND_TYPE_NIKE:
		return GET_BTEXT(101);
	case E_BRAND_TYPE::E_BRAND_TYPE_ADIDAS:
		return GET_BTEXT( 102 );
	case E_BRAND_TYPE::E_BRAND_TYPE_PUMA:
		return GET_BTEXT( 134 );
	case E_BRAND_TYPE::E_BRAND_TYPE_NB:
		return GET_BTEXT( 103 );
	case E_BRAND_TYPE::E_BRAND_TYPE_UMBRO:
		return GET_BTEXT( 104 );
	case E_BRAND_TYPE::E_BRAND_TYPE_UNDERARMOUR:
		return GET_BTEXT( 105 );
	case E_BRAND_TYPE::E_BRAND_TYPE_MIZUNO:
		return GET_BTEXT( 106 );
	case E_BRAND_TYPE::E_BRAND_TYPE_LOTTO:
		return GET_BTEXT( 107 );
	case E_BRAND_TYPE::E_BRAND_TYPE_DIADORA:
		return GET_BTEXT( 108 );
	case E_BRAND_TYPE::E_BRAND_TYPE_JOMA:
		return GET_BTEXT( 140 );
	case E_BRAND_TYPE::E_BRAND_TYPE_KIKA:
		return GET_BTEXT( 109 );
// 	case E_BRAND_TYPE::E_BRAND_TYPE_ASICS:
// 		return GET_BTEXT( 110 );
//	case E_BRAND_TYPE::E_BRAND_TYPE_PANTOFOLADORO:
//		return GET_BTEXT( 111 );
	case E_BRAND_TYPE::E_BRAND_TYPE_DESPORTE:
		return GET_BTEXT( 133 );
	case E_BRAND_TYPE::E_BRAND_TYPE_ATHLETA:
		return GET_BTEXT( 141 );
	case E_BRAND_TYPE::E_BRAND_TYPE_ETC:
		return GET_BTEXT( 60 );
	}

	return GET_BTEXT( 112 );
}

FText UFBMUtil::ProductNameText( int32 bootsIndex, bool multiLine /*= false*/ )
{
	bool isSuccess = false;
	FST_FootBallBootsData bootsSlotInfo = GInst->GetBootsInfo( bootsIndex, isSuccess );
	if( isSuccess )
	{
		// collection 
		FText collectionText = CollectionText( bootsSlotInfo.eCollectionType );
		// collection Num
		int32 collectionNum = bootsSlotInfo.nCollectionNum;
		// model
		FText modelText = bootsSlotInfo.eModelType == E_MODEL_TYPE::NIKE_ETC || bootsSlotInfo.eModelType == E_MODEL_TYPE::ADIDAS_ETC || bootsSlotInfo.eModelType == E_MODEL_TYPE::MIZUNO_ETC || bootsSlotInfo.eModelType == E_MODEL_TYPE::JOMA_ETC || bootsSlotInfo.eModelType == E_MODEL_TYPE::KIKA_ETC ?
			FText::FromString( "" ) : ModelText( bootsSlotInfo.eModelType );
		// studs
		FText studsText = (bootsSlotInfo.eStudsType == E_STUDS_TYPE::E_STUDS_AS) ? 
			GET_BTEXT( 139 ) : StudsNameText( bootsSlotInfo.eStudsType );

		if (collectionNum > 1)
		{
			if ( multiLine )
			{
				return FText::Format( FText::FromString( "{0}{1}\n{2} {3}" ), collectionText, collectionNum, modelText, studsText );
			}
			else
			{
				return FText::Format( FText::FromString( "{0}{1} {2} {3}" ), collectionText, collectionNum, modelText, studsText );
			}
		}
		else
		{
			if( multiLine )
			{
				return FText::Format( FText::FromString( "{0}\n{1} {2}" ), collectionText, modelText, studsText );
			}
			else
			{
				return FText::Format( FText::FromString( "{0} {1} {2}" ), collectionText, modelText, studsText );
			}
		}
	}

	return FText::FromString( "" );
}

FText UFBMUtil::ProductNameText_DB( int32 bootsIndex, bool multiLine /*= false */ )
{
	const FST_FOOTBALL_BOOTS_DATA* bootsSlotInfo_DB = UFBM_SaveGame::Get().GetBootsInfo_DB( bootsIndex );
	if( bootsSlotInfo_DB != nullptr )
	{
		// collection 
		FText collectionText = CollectionText( bootsSlotInfo_DB->CollectionType );
		// collection Num
		int32 collectionNum = bootsSlotInfo_DB->CollectionNum;
		// model
		FText modelText = bootsSlotInfo_DB->ModelType == E_MODEL_TYPE::NIKE_ETC || bootsSlotInfo_DB->ModelType == E_MODEL_TYPE::ADIDAS_ETC || bootsSlotInfo_DB->ModelType == E_MODEL_TYPE::MIZUNO_ETC || bootsSlotInfo_DB->ModelType == E_MODEL_TYPE::JOMA_ETC || bootsSlotInfo_DB->ModelType == E_MODEL_TYPE::KIKA_ETC ?
			FText::FromString( "" ) : ModelText( bootsSlotInfo_DB->ModelType );
		// studs
		FText studsText = (bootsSlotInfo_DB->StudsType == E_STUDS_TYPE::E_STUDS_AS) ?
			GET_BTEXT( 139 ) : StudsNameText( bootsSlotInfo_DB->StudsType );

		if( collectionNum > 1 )
		{
			if( multiLine )
			{
				return FText::Format( FText::FromString( "{0}{1}\n{2} {3}" ), collectionText, collectionNum, modelText, studsText );
			}
			else
			{
				return FText::Format( FText::FromString( "{0}{1} {2} {3}" ), collectionText, collectionNum, modelText, studsText );
			}
		}
		else
		{
			if( multiLine )
			{
				return FText::Format( FText::FromString( "{0}\n{1} {2}" ), collectionText, modelText, studsText );
			}
			else
			{
				return FText::Format( FText::FromString( "{0} {1} {2}" ), collectionText, modelText, studsText );
			}
		}
	}

	return FText::FromString( "" );
}

FString UFBMUtil::BrandLogoPath( E_BRAND_TYPE eBrandType )
{
	switch( eBrandType )
	{
	case E_BRAND_TYPE::E_BRAND_TYPE_NIKE:
		return TEXT( "Logo/Nike" );
	case E_BRAND_TYPE::E_BRAND_TYPE_ADIDAS:
		return TEXT( "Logo/Adidas" );
	case E_BRAND_TYPE::E_BRAND_TYPE_PUMA:
		return TEXT( "Logo/Puma" );
	case E_BRAND_TYPE::E_BRAND_TYPE_NB:
		return TEXT( "Logo/NewBalance" );
	case E_BRAND_TYPE::E_BRAND_TYPE_UMBRO:
		return TEXT( "Logo/umbro" );
	case E_BRAND_TYPE::E_BRAND_TYPE_UNDERARMOUR:
		return TEXT( "Logo/UnderArmour" );
	case E_BRAND_TYPE::E_BRAND_TYPE_MIZUNO:
		return TEXT( "Logo/Mizuno" );
	case E_BRAND_TYPE::E_BRAND_TYPE_LOTTO:
		return TEXT( "Logo/Lotto" );
	case E_BRAND_TYPE::E_BRAND_TYPE_DIADORA:
		return TEXT( "Logo/Diadora" );
	case E_BRAND_TYPE::E_BRAND_TYPE_JOMA:
		return TEXT( "Logo/Joma" );
	case E_BRAND_TYPE::E_BRAND_TYPE_KIKA:
		return TEXT( "Logo/Kika" );
// 	case E_BRAND_TYPE::E_BRAND_TYPE_ASICS:
// 		return TEXT( "Logo/Asics" );
//	case E_BRAND_TYPE::E_BRAND_TYPE_PANTOFOLADORO:
//		return TEXT( "Logo/Pantofoladoro" );
	case E_BRAND_TYPE::E_BRAND_TYPE_DESPORTE:
		return TEXT( "Logo/Desporte" );
	case E_BRAND_TYPE::E_BRAND_TYPE_ATHLETA:
		return TEXT( "Logo/Athleta" );
	}

	return TEXT( "" );
}

FText UFBMUtil::CollectionText( E_COLLECTION_TYPE collectionType )
{
	switch( collectionType )
	{
	case E_COLLECTION_TYPE::NIKE_MERCURIAL_SUPERFLY:
		return GET_BTEXT( 501 );
	case E_COLLECTION_TYPE::NIKE_MERCURIAL_VAPOR:
		return GET_BTEXT( 502 );
	case E_COLLECTION_TYPE::NIKE_PHANTOM_VSN:
		return GET_BTEXT( 503 );
	case E_COLLECTION_TYPE::NIKE_PHANTOM_VNM:
		return GET_BTEXT( 504 );
	case E_COLLECTION_TYPE::NIKE_TIEMPO:
		return GET_BTEXT( 505 );
	case E_COLLECTION_TYPE::NIKE_PREMIER:
		return GET_BTEXT( 506 );
	case E_COLLECTION_TYPE::NIKE_RUNARGATO:
		return GET_BTEXT( 507 );
	case E_COLLECTION_TYPE::NIKE_REACTGATO:
		return GET_BTEXT( 508 );
	case E_COLLECTION_TYPE::NIKE_MAJESTRY:
		return GET_BTEXT( 509 );
	case E_COLLECTION_TYPE::NIKE_MAGISTA:
		return GET_BTEXT( 510 );
	case E_COLLECTION_TYPE::NIKE_PHANTOM_GT:
		return GET_BTEXT( 511 );
	case E_COLLECTION_TYPE::NIKE_ETC:
		return GET_BTEXT( 38 );
	case E_COLLECTION_TYPE::ADIDAS_X:
		return GET_BTEXT( 701 );
	case E_COLLECTION_TYPE::ADIDAS_PREDATOR:
		return GET_BTEXT( 702 );
	case E_COLLECTION_TYPE::ADIDAS_NEMEZIZ:
		return GET_BTEXT( 703 );
	case E_COLLECTION_TYPE::ADIDAS_COPA:
		return GET_BTEXT( 704 );
	case E_COLLECTION_TYPE::ADIDAS_ACE:
		return GET_BTEXT( 705 );
	case E_COLLECTION_TYPE::ADIDAS_SALA:
		return GET_BTEXT( 706 );
	case E_COLLECTION_TYPE::ADIDAS_MUNDIAL:
		return GET_BTEXT( 707 );
	case E_COLLECTION_TYPE::ADIDAS_ETC:
		return GET_BTEXT( 49 );
	case E_COLLECTION_TYPE::PUMA_FUTURE:
		return GET_BTEXT( 708 );
	case E_COLLECTION_TYPE::PUMA_ONE:
		return GET_BTEXT( 709 );
	case E_COLLECTION_TYPE::PUMA_KING:
		return GET_BTEXT( 710 );
	case E_COLLECTION_TYPE::PUMA_ULTRA:
		return GET_BTEXT( 764 );
	case E_COLLECTION_TYPE::PUMA_FUTURE_Z:
		return GET_BTEXT( 765 );
	case E_COLLECTION_TYPE::PUMA_ETC:
		return GET_BTEXT( 50 );
	case E_COLLECTION_TYPE::NB_VISARO:
		return GET_BTEXT( 711 );
	case E_COLLECTION_TYPE::NB_FURON:
		return GET_BTEXT( 712 );
	case E_COLLECTION_TYPE::NB_TEKELA:
		return GET_BTEXT( 713 );
	case E_COLLECTION_TYPE::NB_ETC:
		return GET_BTEXT( 51 );
	case E_COLLECTION_TYPE::UMBRO_VELOCITA:
		return GET_BTEXT( 714 );
	case E_COLLECTION_TYPE::UMBRO_MEDUSAE:
		return GET_BTEXT( 715 );
	case E_COLLECTION_TYPE::UMBRO_UX:
		return GET_BTEXT( 716 );
	case E_COLLECTION_TYPE::UMBRO_SPECIALI:
		return GET_BTEXT( 717 );
	case E_COLLECTION_TYPE::UMBRO_TOCCO:
		return GET_BTEXT( 766 );
	case E_COLLECTION_TYPE::UMBRO_ETC:
		return GET_BTEXT( 50 );
	case E_COLLECTION_TYPE::UNDERARMOUR_MAGNETICO:
		return GET_BTEXT( 718 );
	case E_COLLECTION_TYPE::UNDERARMOUR_SPOTLIGHT:
		return GET_BTEXT( 719 );
	case E_COLLECTION_TYPE::UNDERARMOUR_CLUTCHFIT:
		return GET_BTEXT( 720 );
	case E_COLLECTION_TYPE::UNDERARMOUR_SPEEDFORM:
		return GET_BTEXT( 721 );
	case E_COLLECTION_TYPE::UNDERARMOUR_ETC:
		return GET_BTEXT( 53 );
	case E_COLLECTION_TYPE::MIZUNO_MORELIA_NEO:
		return GET_BTEXT( 722 );
	case E_COLLECTION_TYPE::MIZUNO_MORELIA_NEO_BETA:
		return GET_BTEXT( 723 );
	case E_COLLECTION_TYPE::MIZUNO_MORELIA:
		return GET_BTEXT( 724 );
	case E_COLLECTION_TYPE::MIZUNO_MONARCIDA_NEO:
		return GET_BTEXT( 725 );
	case E_COLLECTION_TYPE::MIZUNO_MONARCIDA:
		return GET_BTEXT( 726 );
	case E_COLLECTION_TYPE::MIZUNO_REBULA:
		return GET_BTEXT( 727 );
	case E_COLLECTION_TYPE::MIZUNO_REBULA_CUP:
		return GET_BTEXT( 728 );
	case E_COLLECTION_TYPE::MIZUNO_ETC:
		return GET_BTEXT( 54 );
	case E_COLLECTION_TYPE::LOTTO_SOLISTA:
		return GET_BTEXT( 729 );
	case E_COLLECTION_TYPE::LOTTO_STADIO:
		return GET_BTEXT( 730 );
	case E_COLLECTION_TYPE::LOTTO_MAESTRO:
		return GET_BTEXT( 731 );
	case E_COLLECTION_TYPE::LOTTO_ETC:
		return GET_BTEXT( 55 );
	case E_COLLECTION_TYPE::DIADORA_BAGGIO:
		return GET_BTEXT( 732 );
	case E_COLLECTION_TYPE::DIADORA_BAGGIO_MATCH_WINNER:
		return GET_BTEXT( 733 );
	case E_COLLECTION_TYPE::DIADORA_BAGGIO_03:
		return GET_BTEXT( 734 );
	case E_COLLECTION_TYPE::DIADORA_BRASIL:
		return GET_BTEXT( 735 );
	case E_COLLECTION_TYPE::DIADORA_ETC:
		return GET_BTEXT( 56 );
	case E_COLLECTION_TYPE::JOMA_TOP_FLEX:
		return GET_BTEXT( 736 );
	case E_COLLECTION_TYPE::JOMA_DRIBLING:
		return GET_BTEXT( 737 );
	case E_COLLECTION_TYPE::JOMA_LIGA:
		return GET_BTEXT( 738 );
	case E_COLLECTION_TYPE::JOMA_AGUILA:
		return GET_BTEXT( 739 );
	case E_COLLECTION_TYPE::JOMA_MUNDIAL:
		return GET_BTEXT( 740 );
	case E_COLLECTION_TYPE::JOMA_SUPER_REGATE:
		return GET_BTEXT( 741 );
	case E_COLLECTION_TYPE::JOMA_ETC:
		return GET_BTEXT( 72 );
	case E_COLLECTION_TYPE::KIKA_AK9:
		return GET_BTEXT( 742 );
	case E_COLLECTION_TYPE::KIKA_TANK_KC:
		return GET_BTEXT( 743 );
	case E_COLLECTION_TYPE::KIKA_K777:
		return GET_BTEXT( 744 );
	case E_COLLECTION_TYPE::KIKA_K600:
		return GET_BTEXT( 745 );
	case E_COLLECTION_TYPE::KIKA_K500:
		return GET_BTEXT( 746 );
	case E_COLLECTION_TYPE::KIKA_R7:
		return GET_BTEXT( 747 );
	case E_COLLECTION_TYPE::KIKA_ZEBRA:
		return GET_BTEXT( 748 );
	case E_COLLECTION_TYPE::KIKA_PREMIER_CF:
		return GET_BTEXT( 749 );
	case E_COLLECTION_TYPE::KIKA_R7_CLS_K:
		return GET_BTEXT( 750 );
	case E_COLLECTION_TYPE::KIKA_R7_CLS_C:
		return GET_BTEXT( 751 );
	case E_COLLECTION_TYPE::KIKA_R7_TANK_KC:
		return GET_BTEXT( 752 );
	case E_COLLECTION_TYPE::KIKA_R7_TANK_C:
		return GET_BTEXT( 753 );
	case E_COLLECTION_TYPE::KIKA_ETC:
		return GET_BTEXT( 57 );
	case E_COLLECTION_TYPE::DESPORTE_SAOLUIS:
		return GET_BTEXT( 755 );
	case E_COLLECTION_TYPE::DESPORTE_CAMPINAS:
		return GET_BTEXT( 756 );
	case E_COLLECTION_TYPE::DESPORTE_SANTOS:
		return GET_BTEXT( 757 );
	case E_COLLECTION_TYPE::DESPORTE_RIO:
		return GET_BTEXT( 758 );
	case E_COLLECTION_TYPE::DESPORTE_BOA_VISTA:
		return GET_BTEXT( 759 );
	case E_COLLECTION_TYPE::DESPORTE_TESSA:
		return GET_BTEXT( 760 );
	case E_COLLECTION_TYPE::DESPORTE_ETC:
		return GET_BTEXT( 73 );
	case E_COLLECTION_TYPE::ATHLETA_O_REI:
		return GET_BTEXT( 761 );
	case E_COLLECTION_TYPE::ATHLETA_CDB:
		return GET_BTEXT( 762 );
	case E_COLLECTION_TYPE::ATHLETA_O_REI_FUTSAL:
		return GET_BTEXT( 763 );
	case E_COLLECTION_TYPE::ATHLETA_ETC:
		return GET_BTEXT( 74 );
	}

	return FText::FromString( "" );
}

FText UFBMUtil::ModelText( E_MODEL_TYPE modelType )
{
	switch( modelType )
	{
	case E_MODEL_TYPE::NIKE_ELITE:
		return GET_BTEXT( 801 );
	case E_MODEL_TYPE::NIKE_PRO:
		return GET_BTEXT( 802 );
	case E_MODEL_TYPE::NIKE_ACADEMY:
		return GET_BTEXT( 803 );
	case E_MODEL_TYPE::NIKE_CLUB:
		return GET_BTEXT( 804 );
	case E_MODEL_TYPE::NIKE_ETC:
		return GET_BTEXT( 38 );
	case E_MODEL_TYPE::ADIDAS_19_PLUS:
		return GET_BTEXT( 901 );
	case E_MODEL_TYPE::ADIDAS_19_1:
		return GET_BTEXT( 902 );
	case E_MODEL_TYPE::ADIDAS_19_2:
		return GET_BTEXT( 903 );
	case E_MODEL_TYPE::ADIDAS_19_3:
		return GET_BTEXT( 904 );
	case E_MODEL_TYPE::ADIDAS_19_4:
		return GET_BTEXT( 905 );
	case E_MODEL_TYPE::ADIDAS_20_PLUS:
		return GET_BTEXT( 906 );
	case E_MODEL_TYPE::ADIDAS_20_1:
		return GET_BTEXT( 907 );
	case E_MODEL_TYPE::ADIDAS_20_1_LOW:
		return GET_BTEXT( 987 );
	case E_MODEL_TYPE::ADIDAS_20_2:
		return GET_BTEXT( 908 );
	case E_MODEL_TYPE::ADIDAS_20_3:
		return GET_BTEXT( 909 );
	case E_MODEL_TYPE::ADIDAS_20_3_LOW:
		return GET_BTEXT( 988 );
	case E_MODEL_TYPE::ADIDAS_20_4:
		return GET_BTEXT( 910 );
	case E_MODEL_TYPE::ADIDAS_GHOSTED_PLUS:
		return GET_BTEXT( 982 );
	case E_MODEL_TYPE::ADIDAS_GHOSTED_1:
		return GET_BTEXT( 983 );
	case E_MODEL_TYPE::ADIDAS_GHOSTED_2:
		return GET_BTEXT( 984 );
	case E_MODEL_TYPE::ADIDAS_GHOSTED_3:
		return GET_BTEXT( 985 );
	case E_MODEL_TYPE::ADIDAS_GHOSTED_4:
		return GET_BTEXT( 986 );
	case E_MODEL_TYPE::ADIDAS_PLUS:
		return GET_BTEXT( 989 );
	case E_MODEL_TYPE::ADIDAS_1:
		return GET_BTEXT( 990 );
	case E_MODEL_TYPE::ADIDAS_2:
		return GET_BTEXT( 991 );
	case E_MODEL_TYPE::ADIDAS_3:
		return GET_BTEXT( 992 );
	case E_MODEL_TYPE::ADIDAS_4:
		return GET_BTEXT( 993 );
	case E_MODEL_TYPE::ADIDAS_FREAK_PLUS:
		return GET_BTEXT( 1008 );
	case E_MODEL_TYPE::ADIDAS_FREAK_1:
		return GET_BTEXT( 1009 );
	case E_MODEL_TYPE::ADIDAS_FREAK_1_LOW:
		return GET_BTEXT( 1010 );
	case E_MODEL_TYPE::ADIDAS_FREAK_2:
		return GET_BTEXT( 1011 );
	case E_MODEL_TYPE::ADIDAS_FREAK_3:
		return GET_BTEXT( 1012 );
	case E_MODEL_TYPE::ADIDAS_FREAK_3_LOW:
		return GET_BTEXT( 1013 );
	case E_MODEL_TYPE::ADIDAS_FREAK_4:
		return GET_BTEXT( 1014 );
	case E_MODEL_TYPE::ADIDAS_SENSE_PLUS:
		return GET_BTEXT( 1015 );
	case E_MODEL_TYPE::ADIDAS_SENSE_1:
		return GET_BTEXT( 1016 );
	case E_MODEL_TYPE::ADIDAS_SENSE_2:
		return GET_BTEXT( 1017 );
	case E_MODEL_TYPE::ADIDAS_SENSE_3:
		return GET_BTEXT( 1018 );
	case E_MODEL_TYPE::ADIDAS_SENSE_4:
		return GET_BTEXT( 1019 );
	case E_MODEL_TYPE::ADIDAS_ETC:
		return GET_BTEXT( 49 );
	case E_MODEL_TYPE::PUMA_1_1:
		return GET_BTEXT( 981 );
	case E_MODEL_TYPE::PUMA_1_2:
		return GET_BTEXT( 1001 );
	case E_MODEL_TYPE::PUMA_5_1:
		return GET_BTEXT( 911 );
	case E_MODEL_TYPE::PUMA_5_1_LOW:
		return GET_BTEXT( 994 );
	case E_MODEL_TYPE::PUMA_5_2:
		return GET_BTEXT( 912 );
	case E_MODEL_TYPE::PUMA_5_3:
		return GET_BTEXT( 913 );
	case E_MODEL_TYPE::PUMA_5_4:
		return GET_BTEXT( 914 );
	case E_MODEL_TYPE::PUMA_6_1:
		return GET_BTEXT( 995 );
	case E_MODEL_TYPE::PUMA_6_1_LOW:
		return GET_BTEXT( 996 );
	case E_MODEL_TYPE::PUMA_6_2:
		return GET_BTEXT( 997 );
	case E_MODEL_TYPE::PUMA_6_3:
		return GET_BTEXT( 998 );
	case E_MODEL_TYPE::PUMA_6_4:
		return GET_BTEXT( 999 );
	case E_MODEL_TYPE::PUMA_20_1:
		return GET_BTEXT( 907 );
	case E_MODEL_TYPE::PUMA_20_2:
		return GET_BTEXT( 908 );
	case E_MODEL_TYPE::PUMA_20_3:
		return GET_BTEXT( 909 );
	case E_MODEL_TYPE::PUMA_20_4:
		return GET_BTEXT( 910 );
	case E_MODEL_TYPE::PUMA_TOP:
		return GET_BTEXT( 915 );
	case E_MODEL_TYPE::PUMA_PLATINUM:
		return GET_BTEXT( 916 );
	case E_MODEL_TYPE::PUMA_PRO:
		return GET_BTEXT( 917 );
	case E_MODEL_TYPE::PUMA_HERO:
		return GET_BTEXT( 918 );
	case E_MODEL_TYPE::PUMA_SL:
		return GET_BTEXT( 1000 );
	case E_MODEL_TYPE::PUMA_2_1:
		return GET_BTEXT( 1002 );
	case E_MODEL_TYPE::PUMA_2_2:
		return GET_BTEXT( 1003 );
	case E_MODEL_TYPE::PUMA_3_1:
		return GET_BTEXT( 1004 );
	case E_MODEL_TYPE::PUMA_3_2:
		return GET_BTEXT( 1005 );
	case E_MODEL_TYPE::PUMA_4_1:
		return GET_BTEXT( 1006 );
	case E_MODEL_TYPE::PUMA_4_2:
		return GET_BTEXT( 1007 );
	case E_MODEL_TYPE::PUMA_ETC:
		return GET_BTEXT( 50 );
	case E_MODEL_TYPE::NB_PRO:
		return GET_BTEXT( 919 );
	case E_MODEL_TYPE::NB_PRO_K_LEATHER:
		return GET_BTEXT( 922 );
	case E_MODEL_TYPE::NB_MIDLEVEL:
		return GET_BTEXT( 920 );
	case E_MODEL_TYPE::NB_CONTROL:
		return GET_BTEXT( 921 );
	case E_MODEL_TYPE::NB_DESTROY:
		return GET_BTEXT( 923 );
	case E_MODEL_TYPE::NB_DISPATCH:
		return GET_BTEXT( 924 );
	case E_MODEL_TYPE::NB_MAGIA:
		return GET_BTEXT( 925 );
	case E_MODEL_TYPE::NB_MAGIQUE:
		return GET_BTEXT( 926 );
	case E_MODEL_TYPE::NB_ETC:
		return GET_BTEXT( 51 );
	case E_MODEL_TYPE::UMBRO_PRO:
		return GET_BTEXT( 927 );
	case E_MODEL_TYPE::UMBRO_PREMIER:
		return GET_BTEXT( 928 );
	case E_MODEL_TYPE::UMBRO_CLUB:
		return GET_BTEXT( 929 );
	case E_MODEL_TYPE::UMBRO_ELITE:
		return GET_BTEXT( 930 );
	case E_MODEL_TYPE::UMBRO_ETC:
		return GET_BTEXT( 50 );
	case E_MODEL_TYPE::UNDERARMOUR_PRO:
		return GET_BTEXT( 931 );
	case E_MODEL_TYPE::UNDERARMOUR_PREMIER:
		return GET_BTEXT( 932 );
	case E_MODEL_TYPE::UNDERARMOUR_SELECT:
		return GET_BTEXT( 933 );
	case E_MODEL_TYPE::UNDERARMOUR_BL:
		return GET_BTEXT( 934 );
	case E_MODEL_TYPE::UNDERARMOUR_DL:
		return GET_BTEXT( 935 );
	case E_MODEL_TYPE::UNDERARMOUR_ETC:
		return GET_BTEXT( 53 );
	case E_MODEL_TYPE::MIZUNO_JP:
		return GET_BTEXT( 936 );
	case E_MODEL_TYPE::MIZUNO_ELETE:
		return GET_BTEXT( 937 );
	case E_MODEL_TYPE::MIZUNO_PRO:
		return GET_BTEXT( 938 );
	case E_MODEL_TYPE::MIZUNO_SELECT:
		return GET_BTEXT( 939 );
	case E_MODEL_TYPE::MIZUNO_CLUB:
		return GET_BTEXT( 940 );
	case E_MODEL_TYPE::MIZUNO_WIDE_JP:
		return GET_BTEXT( 941 );
	case E_MODEL_TYPE::MIZUNO_SW:
		return GET_BTEXT( 942 );
	case E_MODEL_TYPE::MIZUNO_SW_KL:
		return GET_BTEXT( 943 );
	case E_MODEL_TYPE::MIZUNO_SALA_PRO:
		return GET_BTEXT( 944 );
	case E_MODEL_TYPE::MIZUNO_SALA_SELECT:
		return GET_BTEXT( 945 );
	case E_MODEL_TYPE::MIZUNO_SALA_ELITE:
		return GET_BTEXT( 946 );
	case E_MODEL_TYPE::MIZUNO_ETC:
		return GET_BTEXT( 54 );
	case E_MODEL_TYPE::LOTTO_ITALY:
		return GET_BTEXT( 947 );
	case E_MODEL_TYPE::LOTTO_100:
		return GET_BTEXT( 948 );
	case E_MODEL_TYPE::LOTTO_200:
		return GET_BTEXT( 949 );
	case E_MODEL_TYPE::LOTTO_300:
		return GET_BTEXT( 950 );
	case E_MODEL_TYPE::LOTTO_700:
		return GET_BTEXT( 951 );
	case E_MODEL_TYPE::LOTTO_ETC:
		return GET_BTEXT( 55 );
	case E_MODEL_TYPE::DIADORA_ITALY_OG:
		return GET_BTEXT( 952 );
	case E_MODEL_TYPE::DIADORA_ITALY_LT:
		return GET_BTEXT( 953 );
	case E_MODEL_TYPE::DIADORA_ITALY_K_LEATHER:
		return GET_BTEXT( 954 );
	case E_MODEL_TYPE::DIADORA_OG:
		return GET_BTEXT( 955 );
	case E_MODEL_TYPE::DIADORA_LT:
		return GET_BTEXT( 956 );
	case E_MODEL_TYPE::DIADORA_K_LEATHER:
		return GET_BTEXT( 957 );
	case E_MODEL_TYPE::DIADORA_BLUSHIELD:
		return GET_BTEXT( 958 );
	case E_MODEL_TYPE::DIADORA_BRASIL:
		return GET_BTEXT( 959 );
	case E_MODEL_TYPE::DIADORA_ETC:
		return GET_BTEXT( 56 );
	case E_MODEL_TYPE::JOMA_ETC:
		return GET_BTEXT( 72 );
	case E_MODEL_TYPE::KIKA_ETC:
		return GET_BTEXT( 57 );
	case E_MODEL_TYPE::DESPORTE_KT2:
		return GET_BTEXT( 960 );
	case E_MODEL_TYPE::DESPORTE_ST2:
		return GET_BTEXT( 961 );
	case E_MODEL_TYPE::DESPORTE_JTF5:
		return GET_BTEXT( 962 );
	case E_MODEL_TYPE::DESPORTE_TF3:
		return GET_BTEXT( 963 );
	case E_MODEL_TYPE::DESPORTE_TF:
		return GET_BTEXT( 964 );
	case E_MODEL_TYPE::DESPORTE_KT:
		return GET_BTEXT( 965 );
	case E_MODEL_TYPE::DESPORTE_KI2:
		return GET_BTEXT( 966 );
	case E_MODEL_TYPE::DESPORTE_SI2:
		return GET_BTEXT( 967 );
	case E_MODEL_TYPE::DESPORTE_3:
		return GET_BTEXT( 968 );
	case E_MODEL_TYPE::DESPORTE_JP5:
		return GET_BTEXT( 969 );
	case E_MODEL_TYPE::DESPORTE_ID:
		return GET_BTEXT( 970 );
	case E_MODEL_TYPE::DESPORTE_KI:
		return GET_BTEXT( 971 );
	case E_MODEL_TYPE::DESPORTE_ID2:
		return GET_BTEXT( 972 );
	case E_MODEL_TYPE::DESPORTE_ETC:
		return GET_BTEXT( 73 );
	case E_MODEL_TYPE::ATHLETA_A005:
		return GET_BTEXT( 973 );
	case E_MODEL_TYPE::ATHLETA_A004:
		return GET_BTEXT( 974 );
	case E_MODEL_TYPE::ATHLETA_A003:
		return GET_BTEXT( 975 );
	case E_MODEL_TYPE::ATHLETA_A002:
		return GET_BTEXT( 976 );
	case E_MODEL_TYPE::ATHLETA_A001:
		return GET_BTEXT( 977 );
	case E_MODEL_TYPE::ATHLETA_T006:
		return GET_BTEXT( 978 );
	case E_MODEL_TYPE::ATHLETA_ARTHUR:
		return GET_BTEXT( 979 );
	case E_MODEL_TYPE::ATHLETA_RODRIGO:
		return GET_BTEXT( 980 );
	case E_MODEL_TYPE::ATHLETA_ETC:
		return GET_BTEXT( 74 );
	}

	return FText::FromString( "" );
}

FText UFBMUtil::StudsNameText( E_STUDS_TYPE eStudsType )
{
	switch( eStudsType )
	{
	case E_STUDS_TYPE::E_STUDS_FG:
		return GET_BTEXT( 114 );
	case E_STUDS_TYPE::E_STUDS_AG:
		return GET_BTEXT( 115 );
	case E_STUDS_TYPE::E_STUDS_SG:
		return GET_BTEXT( 116 );
	case E_STUDS_TYPE::E_STUDS_HG:
		return GET_BTEXT( 117 );
	case E_STUDS_TYPE::E_STUDS_MG:
		return GET_BTEXT( 118 );
	case E_STUDS_TYPE::E_STUDS_TF:
		return GET_BTEXT( 119 );
	case E_STUDS_TYPE::E_STUDS_ID:
		return GET_BTEXT( 120 );
	case E_STUDS_TYPE::E_STUDS_AS:
		return GET_BTEXT( 119 );
	case E_STUDS_TYPE::E_STUDS_MAX:
		return GET_BTEXT( 112 );
	}

	return GET_BTEXT( 60 );
}

FText UFBMUtil::UpperNameText( E_UPPER_TYPE eUpperType )
{
	switch( eUpperType )
	{
	case E_UPPER_TYPE::E_UPPER_TYPE_NATURAL_LEATHER:
		return GET_BTEXT( 121 );
	case E_UPPER_TYPE::E_UPPER_TYPE_ARTIFICIAL_LEATHER:
		return GET_BTEXT( 122 );
	case E_UPPER_TYPE::E_UPPER_TYPE_KNIT:
		return GET_BTEXT( 123 );
	case E_UPPER_TYPE::E_UPPER_TYPE_MAX:
		return GET_BTEXT( 112 );
	}

	return GET_BTEXT( 60 );
}

FText UFBMUtil::SiloNameText( E_SILO_TYPE eSiloType )
{
	switch( eSiloType )
	{
	case E_SILO_TYPE::E_SILO_TYPE_SPEED:
		return GET_BTEXT( 124 );
	case E_SILO_TYPE::E_SILO_TYPE_POWER:
		return GET_BTEXT( 125 );
	case E_SILO_TYPE::E_SILO_TYPE_CONTROL:
		return GET_BTEXT( 126 );
	case E_SILO_TYPE::E_SILO_TYPE_TOUCH:
		return GET_BTEXT( 127 );
	case E_SILO_TYPE::E_SILO_TYPE_AGILITY:
		return GET_BTEXT( 128 );
	case E_SILO_TYPE::E_SILO_TYPE_COMFORT:
		return GET_BTEXT( 138 );
	case E_SILO_TYPE::E_SILO_TYPE_MAX:
		return GET_BTEXT( 112 );
	}

	return GET_BTEXT( 60 );
}

FText UFBMUtil::GroundNameText( E_GROUND_TYPE eGroundType )
{
	switch( eGroundType )
	{
	case E_GROUND_TYPE::E_GROUND_NATURAL:
		return GET_BTEXT( 129 );
	case E_GROUND_TYPE::E_GROUND_ARTIFICIAL:
		return GET_BTEXT( 130 );
	case E_GROUND_TYPE::E_GROUND_HARD:
		return GET_BTEXT( 131 );
	case E_GROUND_TYPE::E_GROUND_INDOOR:
		return GET_BTEXT( 132 );
	}

	return GET_BTEXT( 112 );
}

FText UFBMUtil::SizeText( int weightSize )
{
	if( weightSize < 4 )
	{
		return GET_BTEXT( 25 );
	}
	else if( weightSize < 8 )
	{
		return GET_BTEXT( 23 );
	}

	return GET_BTEXT( 24 );
}

FText UFBMUtil::BallOfFootText( int weightBallOfFoot )
{
	if( weightBallOfFoot < 4 )
	{
		return GET_BTEXT( 26 );
	}
	else if( weightBallOfFoot < 8 )
	{
		return GET_BTEXT( 27 );
	}

	return GET_BTEXT( 28 );
}

FText UFBMUtil::HeightOfFootText( int weightHeightOfFoot )
{
	if( weightHeightOfFoot < 4 )
	{
		return GET_BTEXT( 26 );
	}
	else if( weightHeightOfFoot < 8 )
	{
		return GET_BTEXT( 27 );
	}

	return GET_BTEXT( 28 );
}

FText UFBMUtil::LengthText( int weightLength )
{
	if( weightLength < 4 )
	{
		return GET_BTEXT( 31 );
	}
	else if( weightLength < 8 )
	{
		return GET_BTEXT( 27 );
	}

	return GET_BTEXT( 32 );
}

FString UFBMUtil::ShopLogoPath( E_CRAWLING_WEBPAGE shopType )
{
	switch( shopType )
	{
	case E_CRAWLING_WEBPAGE::HMALL:
		return TEXT( "Shop/Shop_Hmall" );
	case E_CRAWLING_WEBPAGE::GMARKET:
		return TEXT( "Shop/Shop_GMarket" );
	case E_CRAWLING_WEBPAGE::AUCTION:
		return TEXT( "Shop/Shop_Auction" );
	case E_CRAWLING_WEBPAGE::ST11:
		return TEXT( "Shop/Shop_11st" );
	case E_CRAWLING_WEBPAGE::SSG:
		return TEXT( "Shop/Shop_SSG" );
	case E_CRAWLING_WEBPAGE::LOTTE:
		return TEXT( "Shop/Shop_Lotte" );
	case E_CRAWLING_WEBPAGE::NSMALL:
		return TEXT( "Shop/Shop_NSMall" );
	case E_CRAWLING_WEBPAGE::AKMALL:
		return TEXT( "Shop/Shop_AKMall" );
	case E_CRAWLING_WEBPAGE::GSSHOP:
		return TEXT( "Shop/Shop_GSShop" );
	case E_CRAWLING_WEBPAGE::HIMART:
		return TEXT( "Shop/Shop_HIMart" );
	case E_CRAWLING_WEBPAGE::HALFCLUB:
		return TEXT( "Shop/Shop_HalfClub" );
	case E_CRAWLING_WEBPAGE::WMP:
		return TEXT( "Shop/Shop_WMP" );
	case E_CRAWLING_WEBPAGE::PDS:
		return TEXT( "Shop/Shop_PDS" );
	case E_CRAWLING_WEBPAGE::PDS_US:
		return TEXT( "Shop/Shop_PDS_US" );
	case E_CRAWLING_WEBPAGE::SOCCER:
		return TEXT( "Shop/Shop_SOCCER" );
	case E_CRAWLING_WEBPAGE::UNI:
		return TEXT( "Shop/Shop_UNI" );
	default:
		break;
	}

	return TEXT( "" );
}

FText UFBMUtil::ShopNameText( E_CRAWLING_WEBPAGE shopType )
{
	switch( shopType )
	{
	case E_CRAWLING_WEBPAGE::HMALL:
		return GET_BTEXT( 201 );
	case E_CRAWLING_WEBPAGE::GMARKET:
		return GET_BTEXT( 202 );
	case E_CRAWLING_WEBPAGE::AUCTION:
		return GET_BTEXT( 203 );
	case E_CRAWLING_WEBPAGE::ST11:
		return GET_BTEXT( 204 );
	case E_CRAWLING_WEBPAGE::SSG:
		return GET_BTEXT( 205 );
	case E_CRAWLING_WEBPAGE::LOTTE:
		return GET_BTEXT( 206 );
	case E_CRAWLING_WEBPAGE::NSMALL:
		return GET_BTEXT( 207 );
	case E_CRAWLING_WEBPAGE::AKMALL:
		return GET_BTEXT( 208 );
	case E_CRAWLING_WEBPAGE::GSSHOP:
		return GET_BTEXT( 209 );
	case E_CRAWLING_WEBPAGE::HIMART:
		return GET_BTEXT( 210 );
	case E_CRAWLING_WEBPAGE::HALFCLUB:
		return GET_BTEXT( 211 );
	case E_CRAWLING_WEBPAGE::WMP:
		return GET_BTEXT( 212 );
	case E_CRAWLING_WEBPAGE::PDS:
		return GET_BTEXT( 213 );
	case E_CRAWLING_WEBPAGE::PDS_US:
		return GET_BTEXT( 214 );
	case E_CRAWLING_WEBPAGE::UNI:
		return GET_BTEXT( 215 );
	case E_CRAWLING_WEBPAGE::SOCCER:
		return GET_BTEXT( 216 );
	default:
		break;
	}

	return GET_BTEXT( 135 );
}

E_CRAWLING_WEBPAGE UFBMUtil::ShopNameEnum( FString shopName )
{
	if( shopName.Compare( "HMall" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::HMALL;
	}
	else if( shopName.Compare( "GMarket" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::GMARKET;
	}
	else if( shopName.Compare( "Auction" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::AUCTION;
	}
	else if( shopName.Compare( "ST11" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::ST11;
	}
	else if( shopName.Compare( "SSG" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::SSG;
	}
	else if( shopName.Compare( "Lotte" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::LOTTE;
	}
	else if( shopName.Compare( "NSMall" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::NSMALL;
	}
	else if( shopName.Compare( "AKMall" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::AKMALL;
	}
	else if( shopName.Compare( "GSShop" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::GSSHOP;
	}
	else if( shopName.Compare( "HIMart" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::HIMART;
	}
	else if( shopName.Compare( "HalfClub" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::HALFCLUB;
	}
	else if( shopName.Compare( "WMP" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::WMP;
	}
	else if( shopName.Compare( "PDS" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::PDS;
	}
	else if( shopName.Compare( "PDS_US" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::PDS_US;
	}
	else if( shopName.Compare( "UNI" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::UNI;
	}
	else if( shopName.Compare( "SOCCER" ) == 0 )
	{
		return E_CRAWLING_WEBPAGE::SOCCER;
	}

	return E_CRAWLING_WEBPAGE::NONE;
}

FString UFBMUtil::ChartDotPath( bool isPressDown )
{
	return isPressDown ? TEXT( "Shop/Chart_DotOver" ) : TEXT( "Shop/Chart_Dot" );
}

FString UFBMUtil::MedalImgPath( E_MEDAL_TYPE eMedalType )
{
	switch( eMedalType )
	{
	case E_MEDAL_TYPE::E_MEDAL_TYPE_GOLD:
		return TEXT( "Etc/Medal1" );
	case E_MEDAL_TYPE::E_MEDAL_TYPE_SILVER:
		return TEXT( "Etc/Medal2" );
	case E_MEDAL_TYPE::E_MEDAL_TYPE_BRONZE:
		return TEXT( "Etc/Medal3" );
	}

	return TEXT( "" );
}
