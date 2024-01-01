#pragma once

#include "Bigtamin_Enum.h"
#include "Util/FBMUtil.h"
#include "Bigtamin_Struct.generated.h"

// 리뷰 데이터
USTRUCT( BlueprintType )
struct FST_REVIEW_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Title;
	UPROPERTY() FString Source;
	UPROPERTY() FString ImgURL;
	UPROPERTY() FString ReviewURL;

	FST_REVIEW_DATA()
	{
		Title.Empty();
		Source.Empty();
		ImgURL.Empty();
		ReviewURL.Empty();
	}

	FST_REVIEW_DATA( FString title, FString source, FString imgURL, FString reviewURL )
	{
		Title = title;
		Source = source;
		ImgURL = imgURL;
		ReviewURL = reviewURL;
	}
};

// 축구화 기본 정보 데이터(데이터 Table -> DB 로 이전하면서 변경)
USTRUCT( BlueprintType )
struct FST_FOOTBALL_BOOTS_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() int32 BootsIndex;
	UPROPERTY()	FString BootsName;
	UPROPERTY()	E_BRAND_TYPE BrandType;
	UPROPERTY()	int32 CollectionNum;
	UPROPERTY()	E_COLLECTION_TYPE CollectionType;
	UPROPERTY()	TArray<E_GROUND_TYPE> GroundTypes;
	UPROPERTY()	FString IconURL;
	UPROPERTY()	E_MODEL_TYPE ModelType;
	UPROPERTY()	TArray<FString> Other_ProductID;
	UPROPERTY()	TMap<FString, FString> Other_ProductURL;
	UPROPERTY()	TMap<FString, int32> Other_ReleaseDate;
	UPROPERTY()	TMap<FString, int32> Other_Price;
	UPROPERTY()	E_SILO_TYPE SiloType;
	UPROPERTY()	E_STUDS_TYPE StudsType;
	UPROPERTY()	E_UPPER_TYPE UpperType;
	UPROPERTY()	int32 Weight;
	UPROPERTY()	int32 Price;
	UPROPERTY()	int32 ReleaseDate;
	UPROPERTY()	FString ProductID;
	UPROPERTY()	TArray<FST_REVIEW_DATA> ReviewData;

	FST_FOOTBALL_BOOTS_DATA()
	{

	}

	~FST_FOOTBALL_BOOTS_DATA()
	{

	}

	void SortReleaseDate()
	{
		Other_ProductID.Sort( [this]( const FString& A, const FString& B )
							  {
								  if (Other_ReleaseDate.Contains(A) && Other_ReleaseDate.Contains(B))
								  {
									  return Other_ReleaseDate[A] > Other_ReleaseDate[B];
								  }

								  return true;
							  } );
	}

	// CSV 메인 아이템 출시 순서 얻어오기(CSV 대표 축구화 data)
	int32 GetCsvReleasedateIndex() const
	{
		TArray<int32> releaseDateArray;
		releaseDateArray.Add(ReleaseDate);
		for( auto& releaseDateElem : Other_ReleaseDate )
		{
			releaseDateArray.Add( releaseDateElem.Value );
		}
		releaseDateArray.Sort( []( const int32& A, const int32& B )
							   {
								   return A > B;
							   } );

		int32 returnIndex = releaseDateArray.Find(ReleaseDate);
		if (returnIndex == INDEX_NONE)
			returnIndex = 0;

		return returnIndex;
	}

	// 제일 최신 축구화
	bool GetNewReleaseDateProductID( FString& newProductID ) const
	{
		bool isOtherProductNew = false;
		int32 tempDate = ReleaseDate;
		FString tempProductID = ProductID;
		for( auto& releaseDateElem : Other_ReleaseDate )
		{
			if( tempDate < releaseDateElem.Value )
			{
				tempDate = releaseDateElem.Value;
				tempProductID = releaseDateElem.Key;
				isOtherProductNew = true;
			}
		}
		newProductID = tempProductID;
		return isOtherProductNew;
	}

	// 제일 최신 날짜 얻기
	int32 GetNewReleaseDate() const
	{
		int32 tempDate = ReleaseDate;
		for( auto& releaseDateElem : Other_ReleaseDate )
		{
			if( tempDate < releaseDateElem.Value )
			{
				tempDate = releaseDateElem.Value;
			}
		}
		return tempDate;
	}

	// 제일 낮은 가격 얻기
	int32 GetLowPrice() const
	{
		int32 tempPrice = Price;
		for( auto& priceElem : Other_Price )
		{
			if( tempPrice > priceElem.Value )
			{
				tempPrice = priceElem.Value;
			}
		}
		return tempPrice;
	}

	// 제일 높은 가격 얻기
	int32 GetHighPrice() const
	{
		int32 tempPrice = Price;
		for( auto& priceElem : Other_Price )
		{
			if( tempPrice < priceElem.Value )
			{
				tempPrice = priceElem.Value;
			}
		}
		return tempPrice;
	}
};

// 설문 구조체
USTRUCT( BlueprintType )
struct FST_SURVEY_INFO
{
	GENERATED_USTRUCT_BODY()

	// 설문 인덱스
	int32 nSurveyIndex;

	// 설문 타입
	E_SURVEY_TYPE eSurveyType;

	// 설문 제목
	FString strSurveyTitle;

	// 하위 설문 제목
	FString strSurveySubTitle;

	// 보기 갯수
	int32 nExampleNum;

	// 보기 버튼 이미지 주소들
	TArray<FString> arExampleBtnAddress;

	// 보기 버튼 텍스트들
	TArray<FString> arExampleBtnText;

	// 하위(다운) 보기 버튼 텍스트들
	TArray<FString> arDownExampleBtnText;

	// 설문 페이지 인덱스
	int32 nSurveyPageIndex;
};

// 필터 구조체
USTRUCT( BlueprintType )
struct FST_BOOTS_FILTER_INFO
{
	GENERATED_USTRUCT_BODY()

	TArray < E_BRAND_TYPE> BrandType;
	TArray < E_COLLECTION_TYPE> CollectionType;
	TArray < E_MODEL_TYPE> ModelType;
	TArray < E_STUDS_TYPE> StudsTYpe;
	TArray < E_SILO_TYPE> SiloType;

	void InitFilterInfo()
	{
		BrandType.Empty();
		CollectionType.Empty();
		ModelType.Empty();
		StudsTYpe.Empty();
		SiloType.Empty();
	}

	void CheckBrandType( E_BRAND_TYPE brandType, bool isCheck)
	{
		int32 findIndex = BrandType.Find( brandType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			BrandType.AddUnique( brandType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false)
		{
			BrandType.Remove( brandType );
		}
	}

	void CheckCollectionType( E_COLLECTION_TYPE collectionType, bool isCheck )
	{
		int32 findIndex = CollectionType.Find( collectionType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			CollectionType.AddUnique( collectionType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			CollectionType.Remove( collectionType );
		}
	}

	void CheckModelType( E_MODEL_TYPE modelType, bool isCheck )
	{
		int32 findIndex = ModelType.Find( modelType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			ModelType.AddUnique( modelType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			ModelType.Remove( modelType );
		}
	}

	void CheckStudsType( E_STUDS_TYPE studsType, bool isCheck )
	{
		int32 findIndex = StudsTYpe.Find( studsType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			StudsTYpe.AddUnique( studsType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			StudsTYpe.Remove( studsType );
		}
	}

	void CheckSiloType( E_SILO_TYPE siloType, bool isCheck )
	{
		int32 findIndex = SiloType.Find( siloType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			SiloType.AddUnique( siloType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			SiloType.Remove( siloType );
		}
	}

	bool IsNotFilter()
	{
		return BrandType.Num() == 0 && CollectionType.Num() == 0 &&
			ModelType.Num() == 0 && StudsTYpe.Num() == 0 && SiloType.Num() == 0;
	}

	bool IsCheckBrand( E_BRAND_TYPE brandTYpe)
	{
		return BrandType.Find( brandTYpe ) != INDEX_NONE;
	}

	bool IsCheckCollection( E_COLLECTION_TYPE collectionTYpe )
	{
		return CollectionType.Find( collectionTYpe ) != INDEX_NONE;
	}

	bool IsCheckModel( E_MODEL_TYPE modelType )
	{
		return ModelType.Find( modelType ) != INDEX_NONE;
	}

	bool IsCheckStuds( E_STUDS_TYPE studsType )
	{
		return StudsTYpe.Find( studsType ) != INDEX_NONE;
	}

	bool IsCheckSilo( E_SILO_TYPE siloType )
	{
		return SiloType.Find( siloType ) != INDEX_NONE;
	}
};

// 필터 구조체
USTRUCT( BlueprintType )
struct FST_RANKING_FILTER_INFO
{
	GENERATED_USTRUCT_BODY()

	TArray<FString> StadiumTypes;
	TArray<FString> AwayTeamTypes;

	void InitFilterInfo()
	{
		StadiumTypes.Empty();
		AwayTeamTypes.Empty();
	}

	void CheckStadiumType( FString stadiumType, bool isCheck )
	{
		int32 findIndex = StadiumTypes.Find( stadiumType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			StadiumTypes.AddUnique( stadiumType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			StadiumTypes.Remove( stadiumType );
		}
	}

	void CheckAwayTeamType( FString awayTeamType, bool isCheck )
	{
		int32 findIndex = AwayTeamTypes.Find( awayTeamType );
		if( findIndex == INDEX_NONE && isCheck )
		{
			AwayTeamTypes.AddUnique( awayTeamType );
		}
		else if( findIndex != INDEX_NONE && isCheck == false )
		{
			AwayTeamTypes.Remove( awayTeamType );
		}
	}

	bool IsNotFilter()
	{
		return StadiumTypes.Num() == 0 && AwayTeamTypes.Num() == 0;
	}

	bool IsCheckStadium( FString stadiumType ) const
	{
		if( StadiumTypes.Num() == 0 )
		{
			return true;
		}

		return StadiumTypes.Find( stadiumType ) != INDEX_NONE;
	}

	bool IsCheckAwayTeam( FString awayTeamType ) const
	{
		if( AwayTeamTypes.Num() == 0 )
		{
			return true;
		}

		return AwayTeamTypes.Find( awayTeamType ) != INDEX_NONE;
	}
};

USTRUCT( BlueprintType )
struct FST_PLAYER_CHART_INFO_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Date;
	UPROPERTY() FString DateDay;
	UPROPERTY() FString DateMonth;
	UPROPERTY() uint32 Goal;
	UPROPERTY() uint32 Assist;

	FST_PLAYER_CHART_INFO_DATA()
	{
		Date.Empty();
		DateDay.Empty();
		DateMonth.Empty();
		Goal = 0;
		Assist = 0;
	}

	FST_PLAYER_CHART_INFO_DATA( FString date, uint32 goalData, uint32 assistData )
	{
		Date = date;
		Goal = goalData;
		Assist = assistData;

		FString strYear = date.Mid( 2, 2 );
		FString strMonth = date.Mid( 4, 2 );
		FString strDay = date.Mid( 6, 2 );
		DateDay = strMonth + TEXT( "." ) + strDay;
		DateMonth = strYear + TEXT( "." ) + strMonth;
	}
};

USTRUCT( BlueprintType )
struct FST_LOW_PRICE_INFO_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Date;
	UPROPERTY() E_CRAWLING_WEBPAGE ShopData;
	UPROPERTY() uint32 PriceData;

	FST_LOW_PRICE_INFO_DATA()
	{
		Date.Empty();
		ShopData = E_CRAWLING_WEBPAGE::NONE;
		PriceData = 0;
	}

	FST_LOW_PRICE_INFO_DATA( FString date, E_CRAWLING_WEBPAGE shop, int32 price)
	{
		Date = date;
		ShopData = shop;
		PriceData = price;
	}

	FST_LOW_PRICE_INFO_DATA( FString key, int32 price )
	{
		FString strYear = key.Left( 2 );
		FString strMonth = key.Mid( 2, 2 );
		FString strDay = key.Mid( 4, 2 );
		Date = strMonth + TEXT( "." ) + strDay;

		FString shopNameText = key.RightChop( 7 );
		ShopData = UFBMUtil::ShopNameEnum( shopNameText );

		PriceData = price;
	}
};

// 축구화 가격 정보 크롤링 데이터
USTRUCT( BlueprintType )
struct FST_BOOTS_CRAWLING_INFO_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString UrlData;
	UPROPERTY() int32 PriceData;
	UPROPERTY() bool IsDomestic;
};

USTRUCT( BlueprintType )
struct FST_BOOTS_CRAWLING_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()	uint32 FIreBaseDBVersion; // DB 버전
	UPROPERTY() FString UpdateDate;  // 업데이트 날짜
	UPROPERTY() TMap<E_CRAWLING_WEBPAGE, FST_BOOTS_CRAWLING_INFO_DATA> CrawlingInfo;
	UPROPERTY()	TMap<FString, int32> LowPriceDay; // 최근 일주일 최저가 정보
	UPROPERTY()	TMap<FString, int32> LowPriceWeek; // 최근 1개월 최저가 정보
	UPROPERTY()	TMap<FString, int32> LowPriceMonth; // 최근 6개월 최저가 정보
};

// 메인 배너 데이터
USTRUCT( BlueprintType )
struct FST_MAIN_BANNER_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()	E_BANNER_TYPE BannerType;
	UPROPERTY() FString BannerValue;
	UPROPERTY() FString BannerImgURL;

	FST_MAIN_BANNER_DATA()
	{
		BannerType = E_BANNER_TYPE::NONE;
		BannerValue.Empty();
		BannerImgURL.Empty();
	}

	FST_MAIN_BANNER_DATA( E_BANNER_TYPE bannerType, FString bannerValue, FString imgUrl )
	{
		BannerType = bannerType;
		BannerValue = bannerValue;
		BannerImgURL = imgUrl;
	}

	bool operator==( const FST_MAIN_BANNER_DATA& val ) const
	{
		return (this->BannerType == val.BannerType &&
				 this->BannerValue == val.BannerValue &&
				 this->BannerImgURL == val.BannerImgURL);
	}
};

// 공지사항 데이터
USTRUCT( BlueprintType )
struct FST_NOTICE_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString NoticeDate;
	UPROPERTY() FString NoticeTitle;
	UPROPERTY() FString NoticeContents;

	FST_NOTICE_DATA()
	{
		NoticeDate.Empty();
		NoticeTitle.Empty();
		NoticeContents.Empty();
	}

	FST_NOTICE_DATA( FString date, FString title, FString contents )
	{
		NoticeDate = date;
		NoticeTitle = title;
		NoticeContents = contents;
	}
	/*
	FST_NOTICE_DATA& operator = ( const FST_NOTICE_DATA& val )
	{
		this->NoticeDate = val.NoticeDate;
		this->NoticeTitle = val.NoticeTitle;
		this->NoticeContents = val.NoticeContents;

		return *this;
	}
	*/
	bool operator==( const FST_NOTICE_DATA& val ) const
	{
		return (this->NoticeDate == val.NoticeDate &&
				 this->NoticeTitle == val.NoticeTitle &&
				 this->NoticeContents == val.NoticeContents);
	}
};

// FAQ 데이터
USTRUCT( BlueprintType )
struct FST_FAQ_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString FaqTitle;
	UPROPERTY() FString FaqContents;

	FST_FAQ_DATA()
	{
		FaqTitle.Empty();
		FaqContents.Empty();
	}

	FST_FAQ_DATA( FString title, FString contents )
	{
		FaqTitle = title;
		FaqContents = contents;
	}

	bool operator==( const FST_FAQ_DATA& val ) const
	{
		return ( this->FaqTitle == val.FaqTitle &&
				 this->FaqContents == val.FaqContents);
	}
};

// 출시예정 데이터
USTRUCT( BlueprintType )
struct FST_UPCOMING_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString UpcomingDate;
	UPROPERTY() E_BRAND_TYPE UpcomingBrandType;
	UPROPERTY() FString UpcomingBootsName;
	UPROPERTY() FString UpcomingURL;

	FST_UPCOMING_DATA()
	{
		UpcomingBrandType = E_BRAND_TYPE::E_BRAND_TYPE_MAX;
		UpcomingDate.Empty();
		UpcomingBootsName.Empty();
		UpcomingURL.Empty();
	}

	FST_UPCOMING_DATA( FString date, FString bootsName, FString url, E_BRAND_TYPE brandType )
	{
		UpcomingDate = date;
		UpcomingBootsName = bootsName;
		UpcomingURL = url;
		UpcomingBrandType = brandType;
	}

	bool operator==( const FST_UPCOMING_DATA& val ) const
	{
		return (this->UpcomingDate == val.UpcomingDate &&
				 this->UpcomingBootsName == val.UpcomingBootsName &&
				 this->UpcomingURL == val.UpcomingURL &&
				 this->UpcomingBrandType == val.UpcomingBrandType);
	}
};

// 팀 정보 데이터
USTRUCT( BlueprintType )
struct FST_TEAM_INFO_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString TeamName;     // 팀 이름
	UPROPERTY() FString TeamLogoURL;  // 팀 로고 URL
};

// 구장 정보 데이터
USTRUCT( BlueprintType )
struct FST_STADIUM_INFO_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString StadiumName;  // 구장 이름
};

// 경기 데이터
USTRUCT( BlueprintType )
struct FST_MATCH_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()	E_MATCH_TYPE MatchType;          // 매치 타입( A 매치, 자체전)
	UPROPERTY()	E_MATCH_INFO_TYPE InfoType;      // 정보 타입 ( 일정, 결과 )
	UPROPERTY() FString HomeTeamName;            // 홈팀 이름
	UPROPERTY() FString AwayTeamName;            // 원정팀 이름
	UPROPERTY() FString Comment;                 // 코멘트( 보통 구장 이름)
	UPROPERTY() FString MatchDate;               // 날짜
	UPROPERTY() FString MatchTime;               // 시간
	UPROPERTY() uint32 HomeGoal;                 // 홈팀 득점
	UPROPERTY() uint32 AwayGoal;                 // 원정팀 득점
	UPROPERTY()	TArray<FString> HomeGoalInfo;    // 홈팀 골 정보
	UPROPERTY()	TArray<FString> AwayGoalInfo;    // 원정팀 골 정보
	UPROPERTY()	TArray<FString> HomeAssistInfo;  // 홈팀 어시스트 정보
	UPROPERTY()	TArray<FString> AwayAssistInfo;  // 원정팀 어시스트 정보
	UPROPERTY()	TArray<FString> HomePlayerInfo;  // 홈팀 선수 정보^
	UPROPERTY()	TArray<FString> AwayPlayerInfo;  // 원정팀 선수 정보
};

// 선수별 경기 데이터
USTRUCT( BlueprintType )
struct FST_PLAYER_MATCH_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()	E_MATCH_TYPE MatchType;          // 매치 타입( A 매치, 자체전)
	UPROPERTY() FString Stadium;  // 경기장 장보
	UPROPERTY() FString AwayTeam; // 상대팀 정보

	FST_PLAYER_MATCH_DATA()
	{
		MatchType = E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH;
		Stadium.Empty();
		AwayTeam.Empty();
	}

	FST_PLAYER_MATCH_DATA( FString InStadium, FString InAwayTeam, E_MATCH_TYPE InMatchType )
	{
		Stadium = InStadium;
		AwayTeam = InAwayTeam;
		MatchType = InMatchType;
	}

	bool IsExceptionStadium() const
	{
		return Stadium == TEXT( "광주 문형 구장" );
	}
};

USTRUCT( BlueprintType )
struct FST_PLAYER_MATCH_DATAS
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() TArray<FST_PLAYER_MATCH_DATA> PlayerMatchDatas;
};

// 선수 데이터
USTRUCT( BlueprintType )
struct FST_PLAYER_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString PlayerName;    // 선수 이름
	UPROPERTY() FString TeamName;      // 팀 이름
	UPROPERTY() FString PictureURL;    // 선수 사진 URL

	UPROPERTY() uint32 MvpNum;            // MVP 횟수
	UPROPERTY() uint32 TopScorerNum;      // 득점왕 횟수
	UPROPERTY() uint32 TopAssistNum;      // 도움왕 횟수
	UPROPERTY() uint32 TopAttendanceNum;  // 출석왕 횟수
	UPROPERTY() uint32 TopPointNum;       // 공격포인트왕 횟수

	UPROPERTY()	TMap<FString, int32> GoalNum;            // 전체 골
	UPROPERTY()	TMap<FString, int32> GoalNum_AMatch;     // A-Match 골
	UPROPERTY()	TMap<FString, int32> GoalNum_OwnMatch;   // 자체전골
	UPROPERTY()	TMap<FString, int32> AssistNum;          // 전체 도움
	UPROPERTY()	TMap<FString, int32> AssistNum_AMatch;   // A-Match 도움
	UPROPERTY()	TMap<FString, int32> AssistNum_OwnMatch; // 자체전 도움
	UPROPERTY()	TMap<FString, int32> GamesNum;           // 전체 경기수
	UPROPERTY()	TMap<FString, int32> GamesNum_AMatch;    // A-Match수
	UPROPERTY()	TMap<FString, int32> GamesNum_OwnMatch;  // 자체전 경기수

	UPROPERTY()	TMap<FString, FST_PLAYER_MATCH_DATAS> NewGoalData;      // 골 정보
	UPROPERTY()	TMap<FString, FST_PLAYER_MATCH_DATAS> NewAssistData;    // 도움 정보
	UPROPERTY()	TMap<FString, FST_PLAYER_MATCH_DATAS> NewGamesNumData;  // 경기수 정보

	UPROPERTY()	TMap<FString, uint32> RecentDayGoalNum;            // 최근 7경기 골
	UPROPERTY()	TMap<FString, uint32> RecentWeekGoalNum;           // 최근 4주 골
	UPROPERTY()	TMap<FString, uint32> RecentMonthGoalNum;          // 최근 6개월 골

	UPROPERTY()	TMap<FString, uint32> RecentDayAssistNum;            // 최근 7경기 도움
	UPROPERTY()	TMap<FString, uint32> RecentWeekAssistNum;           // 최근 4주 도움
	UPROPERTY()	TMap<FString, uint32> RecentMonthAssistNum;          // 최근 6개월 도움

	FST_PLAYER_DATA()
	{
		MvpNum = 0;
		TopScorerNum = 0;
		TopAssistNum = 0;
		TopAttendanceNum = 0;
		TopPointNum = 0;

		RecentDayGoalNum.Empty();
		RecentWeekGoalNum.Empty();
		RecentMonthGoalNum.Empty();
		RecentDayAssistNum.Empty();
		RecentWeekAssistNum.Empty();
		RecentMonthAssistNum.Empty();

		GoalNum.Empty();
		GoalNum_AMatch.Empty();
		GoalNum_OwnMatch.Empty();
		AssistNum.Empty();
		AssistNum_AMatch.Empty();
		AssistNum_OwnMatch.Empty();
		GamesNum.Empty();
		GamesNum_AMatch.Empty();
		GamesNum_OwnMatch.Empty();

		NewGoalData.Empty();
		NewAssistData.Empty();
		NewGamesNumData.Empty();
	}

	int32 GetGoalNum( FString strYear, E_FILTER_ITEM_TYPE matchType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL) const
	{
		if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL )
		{
			return GoalNum.Contains( strYear ) ? GoalNum[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
		{
			return GoalNum_AMatch.Contains( strYear ) ? GoalNum_AMatch[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
		{
			return GoalNum_OwnMatch.Contains( strYear ) ? GoalNum_OwnMatch[strYear] : 0;
		}

		return 0;
	}

	int32 GetNewGoalNum( FString strYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, E_FILTER_ITEM_TYPE matchType, bool isExceptionStadium ) const
	{
		int32 returnVal = 0;
		if( NewGoalData.Contains( strYear ) )
		{
			for( auto& goalData : NewGoalData[strYear].PlayerMatchDatas )
			{
				if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
				{
					if ( goalData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						continue;
					}
				}
				else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
				{
					if( goalData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						continue;
					}
				}

				if( isExceptionStadium && goalData.IsExceptionStadium() )
				{
					continue;
				}

				if( curRankingFilterInfo.IsCheckStadium( goalData.Stadium ) &&
					curRankingFilterInfo.IsCheckAwayTeam( goalData.AwayTeam ) )
				{
					returnVal++;
				}
			}
		}

		return returnVal;
	}
	
	int32 GetAssistNum( FString strYear, E_FILTER_ITEM_TYPE matchType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL ) const
	{
		if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL )
		{
			return AssistNum.Contains( strYear ) ? AssistNum[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
		{
			return AssistNum_AMatch.Contains( strYear ) ? AssistNum_AMatch[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
		{
			return AssistNum_OwnMatch.Contains( strYear ) ? AssistNum_OwnMatch[strYear] : 0;
		}

		return 0;
	}

	int32 GetNewAssistNum( FString strYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, E_FILTER_ITEM_TYPE matchType, bool isExceptionStadium ) const
	{
		int32 returnVal = 0;
		if( NewAssistData.Contains( strYear ) )
		{
			for( auto& assistData : NewAssistData[strYear].PlayerMatchDatas )
			{
				if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
				{
					if( assistData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						continue;
					}
				}
				else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
				{
					if( assistData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						continue;
					}
				}

				if( isExceptionStadium && assistData.IsExceptionStadium() )
				{
					continue;
				}

				if( curRankingFilterInfo.IsCheckStadium( assistData.Stadium ) &&
					curRankingFilterInfo.IsCheckAwayTeam( assistData.AwayTeam ) )
				{
					returnVal++;
				}
			}
		}

		return returnVal;
	}

	int32 GetPointNum( FString strYear, E_FILTER_ITEM_TYPE matchType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL ) const
	{
		return GetGoalNum( strYear, matchType ) + GetAssistNum( strYear, matchType );
	}

	int32 GetNewPointNum( FString strYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, E_FILTER_ITEM_TYPE matchType, bool isExceptionStadium ) const
	{
		return GetNewGoalNum( strYear, curRankingFilterInfo, matchType, isExceptionStadium ) + GetNewAssistNum( strYear, curRankingFilterInfo, matchType, isExceptionStadium );
	}

	int32 GetGamesNum( FString strYear, E_FILTER_ITEM_TYPE matchType = E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL ) const
	{
		if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_ALL )
		{
			return GamesNum.Contains( strYear ) ? GamesNum[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
		{
			return GamesNum_AMatch.Contains( strYear ) ? GamesNum_AMatch[strYear] : 0;
		}
		else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
		{
			return GamesNum_OwnMatch.Contains( strYear ) ? GamesNum_OwnMatch[strYear] : 0;
		}

		return 0;
	}

	int32 GetNewGamesNum( FString strYear, const FST_RANKING_FILTER_INFO curRankingFilterInfo, E_FILTER_ITEM_TYPE matchType, bool isExceptionStadium ) const
	{
		int32 returnVal = 0;
		if( NewGamesNumData.Contains( strYear ) )
		{
			for( auto& gamesNumData : NewGamesNumData[strYear].PlayerMatchDatas )
			{
				if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_A_MATCH )
				{
					if( gamesNumData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_A_MATCH )
					{
						continue;
					}
				}
				else if( matchType == E_FILTER_ITEM_TYPE::E_FILTER_ITEM_TYPE_RANKING_OWN_MATCH )
				{
					if( gamesNumData.MatchType != E_MATCH_TYPE::E_MATCH_TYPE_OWN_MATCH )
					{
						continue;
					}
				}

				if ( isExceptionStadium && gamesNumData.IsExceptionStadium())
				{
					continue;
				}

				if( curRankingFilterInfo.IsCheckStadium( gamesNumData.Stadium ) &&
					curRankingFilterInfo.IsCheckAwayTeam( gamesNumData.AwayTeam ) )
				{
					returnVal++;
				}
			}
		}

		return returnVal;
	}
};

// MVP 정보 데이터
USTRUCT( BlueprintType )
struct FST_YEAR_MVP_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Year;          // 연도
	UPROPERTY()	TArray<FString> Name;  // 이름
};

// 랭커 정보 데이터
USTRUCT( BlueprintType )
struct FST_YEAR_KING_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Year;          // 연도
	UPROPERTY() FString GoalKing;      // 득점왕
	UPROPERTY() FString AssistKing;    // 어시왕
	UPROPERTY() FString TotalPointKing;// 공격 포인트
	UPROPERTY() FString AttendanceKing;// 출석왕
};

// Staff 정보 데이터
USTRUCT( BlueprintType )
struct FST_STAFF_DATA
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() FString Owner;          // 구단주
	UPROPERTY() FString GeneralManager; // 단장
	UPROPERTY() FString HeadCoach;      // 감독
	UPROPERTY() FString SecondCoach;    // 수석 코치
	UPROPERTY() FString ThirdCoach;     // 코치
	UPROPERTY() FString FourthCoach;    // 코치
};