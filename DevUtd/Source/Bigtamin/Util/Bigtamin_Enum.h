#pragma once

#include "Bigtamin_Enum.generated.h"

// 크롤링항 사이트
UENUM( BlueprintType )
enum class E_CRAWLING_WEBPAGE : uint8
{
	NONE,
	HMALL,
	GMARKET,
	AUCTION,
	ST11,
	SSG,
	LOTTE,
	NSMALL,
	AKMALL,
	GSSHOP,
	HIMART,
	HALFCLUB,
	WMP,
	PDS,
	PDS_US,
	UNI,
	SOCCER,
	MAX
};

// Mode
UENUM(BlueprintType)
enum class E_MODE : uint8
{
	E_MODE_NONE,
	E_MODE_MAIN,
	E_MODE_SURVEY,
	E_MODE_SURVEY_RESULT,
	E_MODE_LOBBY,
	E_MODE_SET,
	E_MODE_BOOTS_DETAIL,
	E_MODE_EQUIP_MAIN,
	E_MODE_BOOTS_COMPARE,
	E_MODE_BOOKMARK,
	E_MODE_NOTICE,
	E_MODE_VERSION,
	E_MODE_SEARCH,
	E_MODE_UPCOMING,
	E_MODE_INTRO,
	E_MODE_FAQ,
	E_MODE_RANKING_MAIN,
	E_MODE_SCHEDULE_MAIN,
	E_MODE_RESULT_MAIN,
	E_MODE_RESULT_DETAIL,
	E_MODE_PLAYER_DETAIL,
	E_MODE_PLAYER_COMPARE,
	E_MODE_PLAYER_MAIN,
	E_MODE_MAX
};

UENUM( BlueprintType )
enum class E_FILTER_ITEM_TYPE : uint8
{
	E_FILTER_ITEM_TYPE_NONE,
	E_FILTER_ITEM_TYPE_MAIN_BOOTS,
	E_FILTER_ITEM_TYPE_MAIN_EQUIP,
	E_FILTER_ITEM_TYPE_SUB_BOOTS_BRAND,
	E_FILTER_ITEM_TYPE_PRODUCT_INFO,
	E_FILTER_ITEM_TYPE_SHOP_INFO,
	E_FILTER_ITEM_TYPE_SHOP_DAY,
	E_FILTER_ITEM_TYPE_SHOP_WEEK,
	E_FILTER_ITEM_TYPE_SHOP_MONTH,
	E_FILTER_ITEM_TYPE_REVIEW_INFO,
	E_FILTER_ITEM_TYPE_RANKING_ALL,
	E_FILTER_ITEM_TYPE_RANKING_A_MATCH,
	E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH,
	E_FILTER_ITEM_TYPE_PLAYER_TEAM_A,
	E_FILTER_ITEM_TYPE_PLAYER_TEAM_B,
	E_FILTER_ITEM_TYPE_PLAYER_COACH,
	E_FILTER_ITEM_TYPE_PLAYER_FRONT,
	E_FILTER_ITEM_TYPE_MAX
};

UENUM( BlueprintType )
enum class E_SORT_TYPE : uint8
{
	E_SORT_TYPE_NONE,
	E_SORT_TYPE_NEW,
	E_SORT_TYPE_PRICE_LOW,
	E_SORT_TYPE_PRICE_HIGH,
	E_SORT_TYPE_WEIGHT_LOW,
	E_SORT_TYPE_WEIGHT_HIGH,
	E_SORT_TYPE_ABC,
	E_SORT_TYPE_ABC_REVERS,
	E_SORT_TYPE_GOAL,
	E_SORT_TYPE_ASSIST,
	E_SORT_TYPE_POINT,
	E_SORT_TYPE_ATTENDANCE,
	E_SORT_TYPE_MAX
};

UENUM( BlueprintType )
enum class E_BOOTS_FILTER_TYPE : uint8
{
	NONE,
	BRAND,
	COLLECTION,
	MODEL,
	STUDS,
	SILO,
	STADIUM,
	AWAY_TEAM,
	MAX
};

// SurveyType
UENUM(BlueprintType)
enum class E_SURVEY_TYPE : uint8
{
	E_SURVEY_TYPE_NONE,
	E_SURVEY_TYPE_IMG_RECT_BTN,             // 이미지 버튼(네모)
	E_SURVEY_TYPE_IMG_CIRCLE_BTN,           // 이미지 버튼(써클)
	E_SURVEY_TYPE_TEXT_TWO_BTN,             // 텍스트 투버튼
	E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN,        // 하위 버튼 있는 텍스트 투버튼
	E_SURVEY_TYPE_TEXT_MANY_BTN,            // 다수 텍스트 버튼
	E_SURVEY_TYPE_TEXT_DROPDOWN,            // 스크롤 선택
	E_SURVEY_TYPE_IMG_MANY_BTN,             // 다수 이미지 선택
	E_SURVEY_TYPE_OBJECTIVE,
	E_SURVEY_TYPE_SUBJECTIVE,
	E_SURVEY_TYPE_OBJECTIVE_MULTIPLE,
	E_SURVEY_TYPE_MAX
};

// Brand Type
UENUM( BlueprintType )
enum class E_COMMON_ITEM_SLOT_TYPE : uint8
{
	NONE,
	BOOTS,
	EQUIP,
	MAX
};

// Brand Type
UENUM( BlueprintType )
enum class E_BRAND_TYPE : uint8
{
	E_BRAND_TYPE_ALL,
	E_BRAND_TYPE_NIKE,
	E_BRAND_TYPE_ADIDAS,
	E_BRAND_TYPE_PUMA,
	E_BRAND_TYPE_NB,
	E_BRAND_TYPE_UMBRO,
	E_BRAND_TYPE_UNDERARMOUR,
	E_BRAND_TYPE_MIZUNO,
	E_BRAND_TYPE_LOTTO,
	E_BRAND_TYPE_DIADORA,
	E_BRAND_TYPE_JOMA,         // 10
	E_BRAND_TYPE_KIKA,
	//E_BRAND_TYPE_ASICS,
	//E_BRAND_TYPE_PANTOFOLADORO,
	E_BRAND_TYPE_DESPORTE,
	E_BRAND_TYPE_ATHLETA,
	E_BRAND_TYPE_ETC,
	E_BRAND_TYPE_MAX
};

// Collection Type
UENUM( BlueprintType )
enum class E_COLLECTION_TYPE : uint8
{
	NONE,
	NIKE_MERCURIAL_SUPERFLY,
	NIKE_MERCURIAL_VAPOR,
	NIKE_PHANTOM_VSN,
	NIKE_PHANTOM_VNM,
	NIKE_TIEMPO,
	NIKE_PREMIER,
	NIKE_RUNARGATO,
	NIKE_REACTGATO,
	NIKE_MAJESTRY,
	NIKE_MAGISTA,        //  10
	NIKE_ETC,
	ADIDAS_X,
	ADIDAS_PREDATOR,
	ADIDAS_NEMEZIZ,
	ADIDAS_COPA,
	ADIDAS_ACE,
	ADIDAS_SALA,
	ADIDAS_MUNDIAL,
	ADIDAS_ETC,
	PUMA_FUTURE,    // 20
	PUMA_ONE,
	PUMA_KING,
	PUMA_ETC,
	NB_VISARO,
	NB_FURON,
	NB_TEKELA,
	NB_ETC,
	UMBRO_VELOCITA,
	UMBRO_MEDUSAE,
	UMBRO_UX,       // 30
	UMBRO_SPECIALI,
	UMBRO_ETC,
	UNDERARMOUR_MAGNETICO,
	UNDERARMOUR_SPOTLIGHT,
	UNDERARMOUR_CLUTCHFIT,
	UNDERARMOUR_SPEEDFORM,
	UNDERARMOUR_ETC,
	MIZUNO_MORELIA_NEO,
	MIZUNO_MORELIA_NEO_BETA,
	MIZUNO_MORELIA,           // 40
	MIZUNO_MONARCIDA_NEO,
	MIZUNO_MONARCIDA,
	MIZUNO_REBULA,
	MIZUNO_REBULA_CUP,
	MIZUNO_ETC,
	LOTTO_SOLISTA,
	LOTTO_STADIO,
	LOTTO_MAESTRO,
	LOTTO_ETC,
	DIADORA_BAGGIO,    // 50
	DIADORA_BAGGIO_MATCH_WINNER,
	DIADORA_BAGGIO_03,
	DIADORA_BRASIL,
	DIADORA_ETC,
	JOMA_TOP_FLEX,
	JOMA_DRIBLING,
	JOMA_LIGA,
	JOMA_AGUILA,
	JOMA_MUNDIAL,
	JOMA_SUPER_REGATE,   // 60
	JOMA_ETC,
	KIKA_AK9,
	KIKA_TANK_KC,
	KIKA_K777,
	KIKA_K600,
	KIKA_K500,
	KIKA_R7_CLS_K,
	KIKA_R7_CLS_C,
	KIKA_R7_TANK_KC,
	KIKA_R7_TANK_C,     // 70
	KIKA_R7,
	KIKA_ZEBRA,
	KIKA_PREMIER_CF,
	KIKA_ETC,
	DESPORTE_SAOLUIS,
	DESPORTE_CAMPINAS,
	DESPORTE_SANTOS,
	DESPORTE_RIO,
	DESPORTE_BOA_VISTA,
	DESPORTE_TESSA,      // 80
	DESPORTE_ETC,
	ATHLETA_O_REI,
	ATHLETA_CDB,
	ATHLETA_O_REI_FUTSAL,
	ATHLETA_ETC,
	NIKE_PHANTOM_GT,
	PUMA_ULTRA,
	PUMA_FUTURE_Z,
	UMBRO_TOCCO,
	MAX
};

// Model Type
UENUM( BlueprintType )
enum class E_MODEL_TYPE : uint8
{
	NONE,
	NIKE_ELITE,
	NIKE_PRO,
	NIKE_ACADEMY,
	NIKE_CLUB,
	NIKE_ETC,
	ADIDAS_19_PLUS,
	ADIDAS_19_1,
	ADIDAS_19_2,
	ADIDAS_19_3,
	ADIDAS_19_4,        // 10
	ADIDAS_20_PLUS,
	ADIDAS_20_1,
	ADIDAS_20_2,
	ADIDAS_20_3,
	ADIDAS_20_4,
	ADIDAS_ETC,
	PUMA_5_1,
	PUMA_5_2,
	PUMA_5_3,
	PUMA_5_4,   // 20
	PUMA_20_1,
	PUMA_20_2,
	PUMA_20_3,
	PUMA_20_4,
	PUMA_TOP,
	PUMA_PLATINUM,
	PUMA_PRO,
	PUMA_HERO,
	PUMA_ETC,
	NB_PRO,     // 30
	NB_PRO_K_LEATHER,
	NB_MIDLEVEL,
	NB_CONTROL,
	NB_DESTROY,
	NB_DISPATCH,
	NB_MAGIA,
	NB_MAGIQUE,
	NB_ETC,
	UMBRO_PRO,
	UMBRO_PREMIER,  //40
	UMBRO_CLUB,
	UMBRO_ELITE,
	UMBRO_ETC,
	UNDERARMOUR_PRO,
	UNDERARMOUR_PREMIER,
	UNDERARMOUR_SELECT,
	UNDERARMOUR_BL,
	UNDERARMOUR_DL,
	UNDERARMOUR_ETC,
	MIZUNO_JP,      // 50
	MIZUNO_ELETE,
	MIZUNO_PRO,
	MIZUNO_SELECT,
	MIZUNO_CLUB,
	MIZUNO_WIDE_JP,
	MIZUNO_SW,
	MIZUNO_SW_KL,
	MIZUNO_SALA_PRO,
	MIZUNO_SALA_SELECT,
	MIZUNO_SALA_ELITE, // 60
	MIZUNO_ETC,
	LOTTO_ITALY,
	LOTTO_100,
	LOTTO_200,
	LOTTO_300,
	LOTTO_700,
	LOTTO_ETC,
	DIADORA_ITALY_OG,
	DIADORA_ITALY_LT,
	DIADORA_ITALY_K_LEATHER,   // 70
	DIADORA_OG,
	DIADORA_LT,
	DIADORA_K_LEATHER,
	DIADORA_BLUSHIELD,
	DIADORA_BRASIL,
	DIADORA_ETC,
	JOMA_ETC,
	KIKA_ETC,
	DESPORTE_KT2,
	DESPORTE_ST2,         // 80
	DESPORTE_JTF5,
	DESPORTE_TF3,
	DESPORTE_TF,
	DESPORTE_KT,
	DESPORTE_KI2,
	DESPORTE_SI2,
	DESPORTE_3,
	DESPORTE_JP5,
	DESPORTE_ID,
	DESPORTE_KI,          // 90
	DESPORTE_ID2,
	DESPORTE_ETC,
	ATHLETA_A005,
	ATHLETA_A004,
	ATHLETA_A003,
	ATHLETA_A002,
	ATHLETA_A001,
	ATHLETA_T006,
	ATHLETA_ARTHUR,
	ATHLETA_RODRIGO,    // 100
	ATHLETA_ETC,
	PUMA_1_1,
	ADIDAS_GHOSTED_PLUS,
	ADIDAS_GHOSTED_1,
	ADIDAS_GHOSTED_2,
	ADIDAS_GHOSTED_3,
	ADIDAS_GHOSTED_4,
	ADIDAS_20_1_LOW,
	ADIDAS_20_3_LOW,
	ADIDAS_PLUS,       // 110
	ADIDAS_1,
	ADIDAS_2,
	ADIDAS_3,
	ADIDAS_4,
	PUMA_5_1_LOW,
	PUMA_6_1,
	PUMA_6_1_LOW,
	PUMA_6_2,
	PUMA_6_3,
	PUMA_6_4,         // 120
	PUMA_SL,
	PUMA_1_2,
	PUMA_2_1,
	PUMA_2_2,
	PUMA_3_1,
	PUMA_3_2,
	PUMA_4_1,
	PUMA_4_2,
	ADIDAS_FREAK_PLUS,
	ADIDAS_FREAK_1,       // 130
	ADIDAS_FREAK_1_LOW,
	ADIDAS_FREAK_2,
	ADIDAS_FREAK_3,
	ADIDAS_FREAK_3_LOW,
	ADIDAS_FREAK_4,
	ADIDAS_SENSE_PLUS,
	ADIDAS_SENSE_1,
	ADIDAS_SENSE_2,
	ADIDAS_SENSE_3,
	ADIDAS_SENSE_4,      // 140
	MAX
};

// Gender Type
UENUM( BlueprintType )
enum class E_GENDER_TYPE : uint8
{
	E_GENDER_TYPE_NONE,
	E_GENDER_TYPE_MALE,
	E_GENDER_TYPE_FEMALE,
	E_GENDER_TYPE_MAX
};

// Silo Type
UENUM( BlueprintType )
enum class E_SILO_TYPE : uint8
{
	E_SILO_TYPE_NONE,
	E_SILO_TYPE_SPEED,
	E_SILO_TYPE_POWER,
	E_SILO_TYPE_CONTROL,
	E_SILO_TYPE_TOUCH,
	E_SILO_TYPE_AGILITY,
	E_SILO_TYPE_COMFORT,
	E_SILO_TYPE_MAX
};

UENUM( BlueprintType )
enum class E_STUDS_TYPE : uint8
{
	E_STUDS_NONE,
	E_STUDS_FG,
	E_STUDS_AG,
	E_STUDS_SG,
	E_STUDS_HG,
	E_STUDS_MG,
	E_STUDS_TF,
	E_STUDS_ID,
	E_STUDS_AS,
	E_STUDS_MAX
};

// Ground Type
UENUM( BlueprintType )
enum class E_GROUND_TYPE : uint8
{
	E_GROUND_NONE,
	E_GROUND_NATURAL,      // 천연 잔디
	E_GROUND_ARTIFICIAL,   // 인조 잔디
	E_GROUND_HARD,         // 맨땅
	E_GROUND_INDOOR,       // 실내 구장
	E_GROUND_MAX
};

// Upper Type
UENUM( BlueprintType )
enum class E_UPPER_TYPE : uint8
{
	E_UPPER_TYPE_NONE,
	E_UPPER_TYPE_NATURAL_LEATHER,
	E_UPPER_TYPE_ARTIFICIAL_LEATHER,
	E_UPPER_TYPE_KNIT,
	E_UPPER_TYPE_MAX
};

UENUM( BlueprintType )
enum class E_MAINCATEGORY_TYPE : uint8
{
	NONE,
	NOTICE,
	IDEA,
	REVIEW,
	SUPPORT,
	PARTNERSHIP,
	VERSION,
	BOOTS,
	SCRAP,
	UPCOMING,
	FAQ,
	SCHEDULE,
	RESULT,
	RANKING,
	PLAYER,
	MAX
};

UENUM( BlueprintType )
enum class E_UPDATE_CHECK_TYPE : uint8
{
	NONE,
	UPDATE,
	SERVER_CHECK,
	MAX
};

UENUM( BlueprintType )
enum class E_BANNER_TYPE : uint8
{
	NONE,
	URL,
	PRODUCT,
	MAX
};

UENUM( BlueprintType )
enum class E_LOBBY_MODE : uint8
{
	E_LOBBY_MODE_NONE,
	E_LOBBY_MODE_MYINFO,
	E_LOBBY_MODE_DAILY,
	E_LOBBY_MODE_SEARCH,
	E_LOBBY_MODE_NEWS,
	E_LOBBY_MODE_MAX
};

// Medal Type
UENUM( BlueprintType )
enum class E_MEDAL_TYPE : uint8
{
	E_MEDAL_TYPE_GOLD,
	E_MEDAL_TYPE_SILVER,
	E_MEDAL_TYPE_BRONZE,
	E_MEDAL_TYPE_MAX
};

// Match Type
UENUM( BlueprintType )
enum class E_MATCH_TYPE : uint8
{
	E_MATCH_TYPE_A_MATCH,
	E_MATCH_TYPE_OWN_MATCH,
	E_MATCH_TYPE_ETC,
	E_MATCH_TYPE_MAX
};

// Match Info Type
UENUM( BlueprintType )
enum class E_MATCH_INFO_TYPE : uint8
{
	E_MATCH_INFO_TYPE_SCHEDULE,
	E_MATCH_INFO_TYPE_RESULT,
	E_MATCH_INFO_TYPE_MAX
};

// Ranking Info Type
UENUM( BlueprintType )
enum class E_RANKING_TYPE : uint8
{
	E_RANKING_TYPE_GOAL,
	E_RANKING_TYPE_ASSIST,
	E_RANKING_TYPE_POINT,
	E_RANKING_TYPE_ATTENDANCE,
	E_RANKING_TYPE_YEAR_MVP,
	E_RANKING_TYPE_YEAR_KING,
	E_RANKING_TYPE_MAX
};

UENUM()
enum class EBUIName : uint8
{
	None = 0,

	Main		        UMETA( DisplayName = "Main" ),
	Survey		        UMETA( DisplayName = "Survey" ),
	SurveyResult		UMETA( DisplayName = "SurveyResult" ),
	BootsDetail		    UMETA( DisplayName = "BootsDetail" ),
	EquipMain		    UMETA( DisplayName = "EquipMain" ),
	BootsCompare		UMETA( DisplayName = "BootsCompare" ),
	BookMark		    UMETA( DisplayName = "BookMark" ),
	Notice		        UMETA( DisplayName = "Notice" ),
	Version		        UMETA( DisplayName = "Version" ),
	Search		        UMETA( DisplayName = "Search" ),
	Upcoming		    UMETA( DisplayName = "Upcoming" ),
	Intro		        UMETA( DisplayName = "Intro" ),
	Faq		            UMETA( DisplayName = "Faq" ),
	Ranking			    UMETA( DisplayName = "Ranking" ),
	Schedule			UMETA( DisplayName = "Schedule" ),
	Result			    UMETA( DisplayName = "Result" ),
	ResultDetail	    UMETA( DisplayName = "ResultDetail" ),
	PlayerDetail	    UMETA( DisplayName = "PlayerDetail" ),
	PlayerCompare		UMETA( DisplayName = "PlayerCompare" ),
	PlayerMain			UMETA( DisplayName = "PlayerMain" ),
	Max,
};

// 동적생성 위젯 (Modaless)
UENUM()
enum class EDynamicWidgetParts : uint8
{
	None = 0,

	SurveyItemImgBtn			UMETA( DisplayName = "SurveyItemImgBtn" ),
	SurveyItemTwoTextBtn		UMETA( DisplayName = "SurveyItemTwoTextBtn" ),
	SurveyItemTwoTextDownBtn	UMETA( DisplayName = "SurveyItemTwoTextDownBtn" ),
	SurveyItemManyTextBtn		UMETA( DisplayName = "SurveyItemManyTextBtn" ),
	SurveyItemManyTextSlot		UMETA( DisplayName = "SurveyItemManyTextSlot" ),
	SurveyItemDropDown			UMETA( DisplayName = "SurveyItemDropDown" ),
	SurveyItemDropDownSlot		UMETA( DisplayName = "SurveyItemDropDownSlot" ),
	SurveyItemManyImgBtn		UMETA( DisplayName = "SurveyItemManyImgBtn" ),
	SurveyItemManyImgBtnSlot	UMETA( DisplayName = "SurveyItemManyImgBtnSlot" ),
	SurveyNextBtn				UMETA( DisplayName = "SurveyNextBtn" ),
	BootsSlot			        UMETA( DisplayName = "BootsSlot" ),
	EquipFilterItem			    UMETA( DisplayName = "EquipFilterItem" ),
	Warning			            UMETA( DisplayName = "Warning" ),
	CommonItemSlot			    UMETA( DisplayName = "CommonItemSlot" ),
	EquipBootsFilterItem	    UMETA( DisplayName = "EquipBootsFilterItem" ),
	ShopSlot			        UMETA( DisplayName = "ShopSlot" ),
	ShopChart			        UMETA( DisplayName = "ShopChart" ),
	CommonItemSlot2			    UMETA( DisplayName = "CommonItemSlot2" ),
	NoticeSlot			        UMETA( DisplayName = "NoticeSlot" ),
	UpdateCheck			        UMETA( DisplayName = "UpdateCheck" ),
	UpcomingSlot			    UMETA( DisplayName = "UpcomingSlot" ),
	ReviewSlot			        UMETA( DisplayName = "ReviewSlot" ),
	FaqSlot			            UMETA( DisplayName = "FaqSlot" ),
	Loading			            UMETA( DisplayName = "Loading" ),
	MatchItemSlot			    UMETA( DisplayName = "MatchItemSlot" ),
	MainRankingSlot			    UMETA( DisplayName = "MainRankingSlot" ),
	RankingSlot			        UMETA( DisplayName = "RankingSlot" ),
	ResultDetailSlot			UMETA( DisplayName = "ResultDetailSlot" ),
	PlayerChart			        UMETA( DisplayName = "PlayerChart" ),
	PlayerSlot			    UMETA( DisplayName = "PlayerSlot" ),
	Max,
};

UENUM()
enum class EBUIPopupMessage : uint8
{
	SimpleMessage = 0,
	TitleAndMessage,
	IconAndTitleAndMessage,
};

UENUM()
enum class EBUIPopupMessageButton : uint8
{
	Confirm = 0,
	ConfirmOrCancel,
	YesOrNo,
	LoginFail,
	Reconnect,
	ReLogin,
	DuplicateLogin,
};


UENUM()
enum class EBButtonEventType : uint8
{
	Clicked = 0,
	Press,
	Release,
};

UENUM()
enum class EInputMode : uint8
{
	UIOnly = 0,
	GameOnly = 1,
	GameAndUI = 2,
};

template<typename TEnum>
FORCEINLINE FString GetEnumValueToString( const FString& Name, TEnum Value )
{
	const UEnum* enumPtr = FindObject<UEnum>( ANY_PACKAGE, *Name, true );
	if( !enumPtr )
	{
		return FString( "Invalid" );
	}

	return enumPtr->GetNameStringByIndex( (int32)Value );
}