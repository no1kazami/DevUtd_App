// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_Survey.h"
#include "BWidget_SurveyItemImgBtn.h"
#include "BWidget_SurveyItemTwoTextBtn.h"
#include "BWidget_SurveyItemTwoTextDownBtn.h"
#include "BWidget_SurveyItemManyTextBtn.h"
#include "BWidget_SurveyItemDropDown.h"
#include "BWidget_Survey_NextBtn.h"
#include "BWidget_SurveyItemManyImgBtn.h"
#include "UI/BWidget_Top.h"
#include "GameMode/BGameMode_main.h"
#include "Bigtamin.h"


void UBWidget_Survey::Init()
{
	Super::Init();

	_CurPage = 0;
	_TotalPage = 0;

	BP_Top_Survey_UMG->Init();
	BP_Top_Survey_UMG->ChangeTopMode( E_MODE::E_MODE_SURVEY );

	InitSurvey();
}

void UBWidget_Survey::OnClose()
{

}

void UBWidget_Survey::InitSurvey()
{
	SendSurveyInfo();
}

void UBWidget_Survey::SendSurveyInfo()
{
	RecvSurveyInfo();
}

void UBWidget_Survey::RecvSurveyInfo()
{
	_TotalPage = 3;
	_SetPage(1);
	_SaveSurveyInfo();
	_SetSurveyInfo();
}

void UBWidget_Survey::_SaveSurveyInfo()
{
	_arSurveyInfo.Empty();

	// Page1 : 개인정보
	{
		FST_SURVEY_INFO surveyInfo;
		surveyInfo.nSurveyIndex = 0;
		surveyInfo.nSurveyPageIndex = 1;
		surveyInfo.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_RECT_BTN;
		surveyInfo.strSurveyTitle = TEXT( "Football Boots Manager에 오신것을 환영합니다!\n\n다음 질문들을 통해 사용자에게 맞춤형\n축구화 추천과 정보를 전달하기 위함이니\n최대한 정확히 기입해 주세요!\n\n모든 정보는 해당 어플내에서만 사용되며\n개인정보로 보호됩니다." );
		surveyInfo.nExampleNum = 2;
		surveyInfo.arExampleBtnAddress.Add( TEXT( "Survey/Avatar_Man" ) );
		surveyInfo.arExampleBtnAddress.Add( TEXT( "Survey/Avatar_Woman" ) );
		_arSurveyInfo.Add( surveyInfo );

		FST_SURVEY_INFO surveyInfo2;
		surveyInfo2.nSurveyIndex = 1;
		surveyInfo2.nSurveyPageIndex = 1;
		surveyInfo2.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
		surveyInfo2.strSurveyTitle = TEXT( "당신의 나이는?" );
		surveyInfo2.nExampleNum = 11;
		surveyInfo2.arExampleBtnText.Add( TEXT( "0 ~ 10" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "11 ~ 20" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "21 ~ 30" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "31 ~ 40" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "41 ~ 50" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "51 ~ 60" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "61 ~ 70" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "71 ~ 80" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "81 ~ 90" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "91 ~ 100" ) );
		surveyInfo2.arExampleBtnText.Add( TEXT( "100 ~" ) );
		_arSurveyInfo.Add( surveyInfo2 );
	}

	// Page2 : 필터링 정보
	{
		FST_SURVEY_INFO surveyInfo3;
		surveyInfo3.nSurveyIndex = 2;
		surveyInfo3.nSurveyPageIndex = 2;
		surveyInfo3.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
		surveyInfo3.strSurveyTitle = TEXT( "선호하는 브랜드를 모두 선택해주세요" );
		surveyInfo3.nExampleNum = 13;
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_NIKE ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_ADIDAS ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_PUMA ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_NB ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_UMBRO ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_UNDERARMOUR ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_MIZUNO ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_LOTTO ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_DIADORA ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_JOMA ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_KIKA ).ToString() );
		//surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_ASICS ).ToString() );
		//surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_PANTOFOLADORO ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_DESPORTE ).ToString() );
		surveyInfo3.arExampleBtnText.Add( UFBMUtil::BrandNameText( E_BRAND_TYPE::E_BRAND_TYPE_ATHLETA ).ToString() );
		_arSurveyInfo.Add( surveyInfo3 );

		FST_SURVEY_INFO surveyInfo4;
		surveyInfo4.nSurveyIndex = 3;
		surveyInfo4.nSurveyPageIndex = 2;
		surveyInfo4.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
		surveyInfo4.strSurveyTitle = TEXT( "선호하는 스터드 타입을 모두 선택해주세요" );
		surveyInfo4.nExampleNum = 8;
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_FG ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_AG ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_SG ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_HG ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_MG ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_TF ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_ID ).ToString() );
		surveyInfo4.arExampleBtnText.Add( UFBMUtil::StudsNameText( E_STUDS_TYPE::E_STUDS_MAX ).ToString() );
		_arSurveyInfo.Add( surveyInfo4 );

		FST_SURVEY_INFO surveyInfo5;
		surveyInfo5.nSurveyIndex = 4;
		surveyInfo5.nSurveyPageIndex = 2;
		surveyInfo5.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
		surveyInfo5.strSurveyTitle = TEXT( "선호하는 소재를 모두 선택해주세요" );
		surveyInfo5.nExampleNum = 3;
		surveyInfo5.arExampleBtnText.Add( UFBMUtil::UpperNameText( E_UPPER_TYPE::E_UPPER_TYPE_NATURAL_LEATHER ).ToString() );
		surveyInfo5.arExampleBtnText.Add( UFBMUtil::UpperNameText( E_UPPER_TYPE::E_UPPER_TYPE_ARTIFICIAL_LEATHER ).ToString() );
		surveyInfo5.arExampleBtnText.Add( UFBMUtil::UpperNameText( E_UPPER_TYPE::E_UPPER_TYPE_KNIT ).ToString() );
		_arSurveyInfo.Add( surveyInfo5 );

		FST_SURVEY_INFO surveyInfo6;
		surveyInfo6.nSurveyIndex = 5;
		surveyInfo6.nSurveyPageIndex = 2;
		surveyInfo6.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
		surveyInfo6.strSurveyTitle = TEXT( "선호하는 사일로를 모두 선택해주세요" );
		surveyInfo6.nExampleNum = 5;
		surveyInfo6.arExampleBtnText.Add( UFBMUtil::SiloNameText( E_SILO_TYPE::E_SILO_TYPE_SPEED ).ToString() );
		surveyInfo6.arExampleBtnText.Add( UFBMUtil::SiloNameText( E_SILO_TYPE::E_SILO_TYPE_POWER ).ToString() );
		surveyInfo6.arExampleBtnText.Add( UFBMUtil::SiloNameText( E_SILO_TYPE::E_SILO_TYPE_CONTROL ).ToString() );
		surveyInfo6.arExampleBtnText.Add( UFBMUtil::SiloNameText( E_SILO_TYPE::E_SILO_TYPE_TOUCH ).ToString() );
		surveyInfo6.arExampleBtnText.Add( UFBMUtil::SiloNameText( E_SILO_TYPE::E_SILO_TYPE_AGILITY ).ToString() );
		_arSurveyInfo.Add( surveyInfo6 );

		FST_SURVEY_INFO surveyInfo7;
		surveyInfo7.nSurveyIndex = 6;
		surveyInfo7.nSurveyPageIndex = 2;
		surveyInfo7.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
		surveyInfo7.strSurveyTitle = TEXT( "주로 사용하시는 구장을 모두 선택해주세요" );
		surveyInfo7.nExampleNum = 4;
		surveyInfo7.arExampleBtnText.Add( UFBMUtil::GroundNameText( E_GROUND_TYPE::E_GROUND_NATURAL ).ToString() );
		surveyInfo7.arExampleBtnText.Add( UFBMUtil::GroundNameText( E_GROUND_TYPE::E_GROUND_ARTIFICIAL ).ToString() );
		surveyInfo7.arExampleBtnText.Add( UFBMUtil::GroundNameText( E_GROUND_TYPE::E_GROUND_HARD ).ToString() );
		surveyInfo7.arExampleBtnText.Add( UFBMUtil::GroundNameText( E_GROUND_TYPE::E_GROUND_INDOOR ).ToString() );
		_arSurveyInfo.Add( surveyInfo7 );

		FST_SURVEY_INFO surveyInfo8;
		surveyInfo8.nSurveyIndex = 7;
		surveyInfo8.nSurveyPageIndex = 2;
		surveyInfo8.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
		surveyInfo8.strSurveyTitle = TEXT( "예산을 설정해주세요" );
		surveyInfo8.nExampleNum = 4;
		surveyInfo8.arExampleBtnText.Add( TEXT( "10만원 이하" ) );
		surveyInfo8.arExampleBtnText.Add( TEXT( "20만원 이하" ) );
		surveyInfo8.arExampleBtnText.Add( TEXT( "30만원 이하" ) );
		surveyInfo8.arExampleBtnText.Add( TEXT( "상관없음" ) );
		_arSurveyInfo.Add( surveyInfo8 );

		FST_SURVEY_INFO surveyInfo9;
		surveyInfo9.nSurveyIndex = 8;
		surveyInfo9.nSurveyPageIndex = 3;
		surveyInfo9.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
		surveyInfo9.strSurveyTitle = TEXT( "선호하는 무게감을 선택해주세요\n(1:가벼움 ~ 10:무거움)" );
		surveyInfo9.nExampleNum = 10;
		surveyInfo9.arExampleBtnText.Add( TEXT( "1(가벼움)" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "2" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "3" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "4" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "5(보통)" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "6" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "7" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "8" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "9" ) );
		surveyInfo9.arExampleBtnText.Add( TEXT( "10(무거움)" ) );
		_arSurveyInfo.Add( surveyInfo9 );

		FST_SURVEY_INFO surveyInfo10;
		surveyInfo10.nSurveyIndex = 9;
		surveyInfo10.nSurveyPageIndex = 3;
		surveyInfo10.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
		surveyInfo10.strSurveyTitle = TEXT( "발볼 사이즈를 선택해주세요\n(1:좁음 ~ 10:넓음)" );
		surveyInfo10.nExampleNum = 10;
		surveyInfo10.arExampleBtnText.Add( TEXT( "1(좁음)" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "2" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "3" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "4" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "5(보통)" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "6" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "7" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "8" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "9" ) );
		surveyInfo10.arExampleBtnText.Add( TEXT( "10(넓음)" ) );
		_arSurveyInfo.Add( surveyInfo10 );

		FST_SURVEY_INFO surveyInfo11;
		surveyInfo11.nSurveyIndex = 10;
		surveyInfo11.nSurveyPageIndex = 3;
		surveyInfo11.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
		surveyInfo11.strSurveyTitle = TEXT( "발등 사이즈를 선택해주세요\n(1:낮음 ~ 10:높음)" );
		surveyInfo11.nExampleNum = 10;
		surveyInfo11.arExampleBtnText.Add( TEXT( "1(낮음)" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "2" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "3" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "4" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "5(보통)" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "6" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "7" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "8" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "9" ) );
		surveyInfo11.arExampleBtnText.Add( TEXT( "10(높음)" ) );
		_arSurveyInfo.Add( surveyInfo11 );
	}

	// Page3 : 가중치 정보
	{
	}

	/*
	FST_SURVEY_INFO surveyInfo3;
	surveyInfo3.nSurveyIndex = 2;
	surveyInfo3.nSurveyPageIndex = 1;
	surveyInfo3.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_CIRCLE_BTN;
	surveyInfo3.strSurveyTitle = TEXT("하루에 몇 잔의 커피를 마시나요?");
	surveyInfo3.nExampleNum = 3;
	surveyInfo3.arExampleBtnAddress.Add(TEXT(""));
	surveyInfo3.arExampleBtnAddress.Add(TEXT("Survey/coffee_2"));
	surveyInfo3.arExampleBtnAddress.Add(TEXT("Survey/coffee_3"));
	surveyInfo3.arExampleBtnText.Add(TEXT("마시지 않는다"));
	surveyInfo3.arExampleBtnText.Add(TEXT("1~2잔"));
	surveyInfo3.arExampleBtnText.Add(TEXT("3잔 이상"));
	_arSurveyInfo.Add(surveyInfo3);

	FST_SURVEY_INFO surveyInfo4;
	surveyInfo4.nSurveyIndex = 3;
	surveyInfo4.nSurveyPageIndex = 1;
	surveyInfo4.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN;
	surveyInfo4.strSurveyTitle = TEXT("일주일에 어느정도 음주를 하시나요?");
	surveyInfo4.nExampleNum = 7;
	surveyInfo4.arExampleBtnText.Add(TEXT("1회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("2회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("3회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("4회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("5회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("6회"));
	surveyInfo4.arExampleBtnText.Add(TEXT("7회"));
	_arSurveyInfo.Add(surveyInfo4);

	FST_SURVEY_INFO surveyInfo5;
	surveyInfo5.nSurveyIndex = 4;
	surveyInfo5.nSurveyPageIndex = 1;
	surveyInfo5.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_CIRCLE_BTN;
	surveyInfo5.strSurveyTitle = TEXT("흡연을 하시나요?");
	surveyInfo5.nExampleNum = 4;
	surveyInfo5.arExampleBtnAddress.Add(TEXT(""));
	surveyInfo5.arExampleBtnAddress.Add(TEXT("Survey/Smoke_1"));
	surveyInfo5.arExampleBtnAddress.Add(TEXT("Survey/Smoke_2"));
	surveyInfo5.arExampleBtnAddress.Add(TEXT("Survey/Smoke_3"));
	surveyInfo5.arExampleBtnText.Add(TEXT("피지 않는다"));
	surveyInfo5.arExampleBtnText.Add(TEXT("반갑 정도 핀다"));
	surveyInfo5.arExampleBtnText.Add(TEXT("하루 한갑 핀다"));
	surveyInfo5.arExampleBtnText.Add(TEXT("Heavy Smoker!"));
	_arSurveyInfo.Add(surveyInfo5);

	FST_SURVEY_INFO surveyInfo6;
	surveyInfo6.nSurveyIndex = 5;
	surveyInfo6.nSurveyPageIndex = 1;
	surveyInfo6.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_CIRCLE_BTN;
	surveyInfo6.strSurveyTitle = TEXT("탄산 음료는 많이 드시나요?");
	surveyInfo6.nExampleNum = 3;
	surveyInfo6.arExampleBtnAddress.Add(TEXT(""));
	surveyInfo6.arExampleBtnAddress.Add(TEXT("Survey/Coke_1"));
	surveyInfo6.arExampleBtnAddress.Add(TEXT("Survey/Coke_2"));
	surveyInfo6.arExampleBtnText.Add(TEXT("마시지 않는다"));
	surveyInfo6.arExampleBtnText.Add(TEXT("하루에 한병"));
	surveyInfo6.arExampleBtnText.Add(TEXT("많이 마신다"));
	_arSurveyInfo.Add(surveyInfo6);

	FST_SURVEY_INFO surveyInfo7;
	surveyInfo7.nSurveyIndex = 6;
	surveyInfo7.nSurveyPageIndex = 1;
	surveyInfo7.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
	surveyInfo7.strSurveyTitle = TEXT("앓고 있는 지병이 있으신가요?");
	surveyInfo7.nExampleNum = 8;
	surveyInfo7.arExampleBtnText.Add(TEXT("자가 면역 질환"));
	surveyInfo7.arExampleBtnText.Add(TEXT("고혈압"));
	surveyInfo7.arExampleBtnText.Add(TEXT("당뇨병"));
	surveyInfo7.arExampleBtnText.Add(TEXT("고지혈증"));
	surveyInfo7.arExampleBtnText.Add(TEXT("뇌졸증"));
	surveyInfo7.arExampleBtnText.Add(TEXT("골다골증"));
	surveyInfo7.arExampleBtnText.Add(TEXT("심장병"));
	surveyInfo7.arExampleBtnText.Add(TEXT("암"));
	_arSurveyInfo.Add(surveyInfo7);

	FST_SURVEY_INFO surveyInfo8;
	surveyInfo8.nSurveyIndex = 7;
	surveyInfo8.nSurveyPageIndex = 1;
	surveyInfo8.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN;
	surveyInfo8.strSurveyTitle = TEXT("숙면을 잘 취하시나요?");
	surveyInfo8.nExampleNum = 2;
	surveyInfo8.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo8.arExampleBtnText.Add(TEXT("아니다"));
	surveyInfo8.strSurveySubTitle = TEXT("불면증이 있으신가요?");
	surveyInfo8.arDownExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo8.arDownExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo8);

	FST_SURVEY_INFO surveyInfo9;
	surveyInfo9.nSurveyIndex = 8;
	surveyInfo9.nSurveyPageIndex = 1;
	surveyInfo9.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_BTN;
	surveyInfo9.strSurveyTitle = TEXT("속이 더부룩하거나 가스가 차는 편인가요?");
	surveyInfo9.nExampleNum = 2;
	surveyInfo9.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo9.arExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo9);

	FST_SURVEY_INFO surveyInfo10;
	surveyInfo10.nSurveyIndex = 9;
	surveyInfo10.nSurveyPageIndex = 1;
	surveyInfo10.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_BTN;
	surveyInfo10.strSurveyTitle = TEXT("규칙적인 배변활동을 하시나요?");
	surveyInfo10.nExampleNum = 2;
	surveyInfo10.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo10.arExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo10);

	FST_SURVEY_INFO surveyInfo11;
	surveyInfo11.nSurveyIndex = 10;
	surveyInfo11.nSurveyPageIndex = 1;
	surveyInfo11.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_BTN;
	surveyInfo11.strSurveyTitle = TEXT("혹시 과민성 장 증후군이 있나요?");
	surveyInfo11.nExampleNum = 2;
	surveyInfo11.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo11.arExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo11);

	FST_SURVEY_INFO surveyInfo12;
	surveyInfo12.nSurveyIndex = 11;
	surveyInfo12.nSurveyPageIndex = 1;
	surveyInfo12.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN;
	surveyInfo12.strSurveyTitle = TEXT("눈이 피로하고 침침함이 있나요?");
	surveyInfo12.nExampleNum = 2;
	surveyInfo12.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo12.arExampleBtnText.Add(TEXT("아니다"));
	surveyInfo12.strSurveySubTitle = TEXT("눈 노화가 우려우신가요?");
	surveyInfo12.arDownExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo12.arDownExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo12);

	FST_SURVEY_INFO surveyInfo13;
	surveyInfo13.nSurveyIndex = 12;
	surveyInfo13.nSurveyPageIndex = 1;
	surveyInfo13.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN;
	surveyInfo13.strSurveyTitle = TEXT("평소에 운동은 하시나요?");
	surveyInfo13.nExampleNum = 2;
	surveyInfo13.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo13.arExampleBtnText.Add(TEXT("아니다"));
	surveyInfo13.strSurveySubTitle = TEXT("관절에는 문제가 없으시죠?");
	surveyInfo13.arDownExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo13.arDownExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo13);

	FST_SURVEY_INFO surveyInfo14;
	surveyInfo14.nSurveyIndex = 13;
	surveyInfo14.nSurveyPageIndex = 1;
	surveyInfo14.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN;
	surveyInfo14.strSurveyTitle = TEXT("야외파? 실내파?");
	surveyInfo14.nExampleNum = 2;
	surveyInfo14.arExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo14.arExampleBtnText.Add(TEXT("아니다"));
	surveyInfo14.strSurveySubTitle = TEXT("관절에는 문제가 없으시죠?");
	surveyInfo14.arDownExampleBtnText.Add(TEXT("그렇다"));
	surveyInfo14.arDownExampleBtnText.Add(TEXT("아니다"));
	_arSurveyInfo.Add(surveyInfo14);

	FST_SURVEY_INFO surveyInfo15;
	surveyInfo15.nSurveyIndex = 14;
	surveyInfo15.nSurveyPageIndex = 1;
	surveyInfo15.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN;
	surveyInfo15.strSurveyTitle = TEXT("현재 복용중인 의약품을 골라주세요\n(없다면 고르지 않아도 됩니다)");
	surveyInfo15.nExampleNum = 11;
	surveyInfo15.arExampleBtnText.Add(TEXT("경구 피임제 및\n여성호르몬제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("위산분비 억재제\n(제산제 포함)"));
	surveyInfo15.arExampleBtnText.Add(TEXT("다이어트 보조제\n(지방 차단제류)"));
	surveyInfo15.arExampleBtnText.Add(TEXT("소염 진통제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("혈압약"));
	surveyInfo15.arExampleBtnText.Add(TEXT("당뇨병약"));
	surveyInfo15.arExampleBtnText.Add(TEXT("진통제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("골다골증\n치료제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("수면제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("콜레스트롤\n저하제"));
	surveyInfo15.arExampleBtnText.Add(TEXT("발기부전\n치료제"));
	_arSurveyInfo.Add(surveyInfo15);

	FST_SURVEY_INFO surveyInfo16;
	surveyInfo16.nSurveyIndex = 15;
	surveyInfo16.nSurveyPageIndex = 2;
	surveyInfo16.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo16.strSurveyTitle = TEXT("자! 마지막이에요! 지난 3일간 먹은것중\n기억나는건 모두 골라주세요!");
	surveyInfo16.strSurveySubTitle = TEXT("한식");
	surveyInfo16.nExampleNum = 16;
	surveyInfo16.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo16.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo16.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	_arSurveyInfo.Add(surveyInfo16);

	FST_SURVEY_INFO surveyInfo17;
	surveyInfo17.nSurveyIndex = 16;
	surveyInfo17.nSurveyPageIndex = 2;
	surveyInfo17.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo17.strSurveyTitle = TEXT("");
	surveyInfo17.strSurveySubTitle = TEXT("양식");
	surveyInfo17.nExampleNum = 12;
	surveyInfo17.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo17.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo17.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	_arSurveyInfo.Add(surveyInfo17);

	FST_SURVEY_INFO surveyInfo18;
	surveyInfo18.nSurveyIndex = 17;
	surveyInfo18.nSurveyPageIndex = 2;
	surveyInfo18.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo18.strSurveyTitle = TEXT("");
	surveyInfo18.strSurveySubTitle = TEXT("일식");
	surveyInfo18.nExampleNum = 11;
	surveyInfo18.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo18.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo18.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	_arSurveyInfo.Add(surveyInfo18);

	FST_SURVEY_INFO surveyInfo19;
	surveyInfo19.nSurveyIndex = 18;
	surveyInfo19.nSurveyPageIndex = 2;
	surveyInfo19.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo19.strSurveyTitle = TEXT("");
	surveyInfo19.strSurveySubTitle = TEXT("중식");
	surveyInfo19.nExampleNum = 10;
	surveyInfo19.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo19.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo19.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	_arSurveyInfo.Add(surveyInfo19);

	FST_SURVEY_INFO surveyInfo20;
	surveyInfo20.nSurveyIndex = 19;
	surveyInfo20.nSurveyPageIndex = 2;
	surveyInfo20.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo20.strSurveyTitle = TEXT("");
	surveyInfo20.strSurveySubTitle = TEXT("디저트");
	surveyInfo20.nExampleNum = 9;
	surveyInfo20.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo20.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo20.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo20.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo20.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	_arSurveyInfo.Add(surveyInfo20);

	FST_SURVEY_INFO surveyInfo21;
	surveyInfo21.nSurveyIndex = 20;
	surveyInfo21.nSurveyPageIndex = 2;
	surveyInfo21.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo21.strSurveyTitle = TEXT("");
	surveyInfo21.strSurveySubTitle = TEXT("야식");
	surveyInfo21.nExampleNum = 8;
	surveyInfo21.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo21.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo21.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo21.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo21.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo21.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo21.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo21.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo21.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	_arSurveyInfo.Add(surveyInfo21);

	FST_SURVEY_INFO surveyInfo22;
	surveyInfo22.nSurveyIndex = 21;
	surveyInfo22.nSurveyPageIndex = 2;
	surveyInfo22.eSurveyType = E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN;
	surveyInfo22.strSurveyTitle = TEXT("");
	surveyInfo22.strSurveySubTitle = TEXT("분식 & 라면");
	surveyInfo22.nExampleNum = 7;
	surveyInfo22.arExampleBtnText.Add(TEXT("된장찌개"));
	surveyInfo22.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo22.arExampleBtnText.Add(TEXT("소불고기"));
	surveyInfo22.arExampleBtnText.Add(TEXT("순댓국"));
	surveyInfo22.arExampleBtnText.Add(TEXT("김밥"));
	surveyInfo22.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo22.arExampleBtnText.Add(TEXT("김치찌개"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_02"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_03"));
	surveyInfo22.arExampleBtnAddress.Add(TEXT("Survey/Food_01"));
	_arSurveyInfo.Add(surveyInfo22);
	*/
}

void UBWidget_Survey::_SetSurveyInfo()
{
	if (C_ScrollBox_SurveyItem.IsValid())
	{
		C_ScrollBox_SurveyItem.Get()->ClearChildren();
		C_ScrollBox_SurveyItem.Get()->ScrollToStart();

		for (auto& stInfoTemp : _arSurveyInfo)
		{
			if (stInfoTemp.nSurveyPageIndex != _CurPage)
				continue;

			switch (stInfoTemp.eSurveyType)
			{
				case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_RECT_BTN:
				case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_CIRCLE_BTN:
				{
					UBWidget_SurveyItemImgBtn* imgBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemImgBtn>(EDynamicWidgetParts::SurveyItemImgBtn);
					if (imgBtnWidget != nullptr)
					{
						imgBtnWidget->OwnerPannel = this;
						imgBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(imgBtnWidget);
					}
				}
				break;
				case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_BTN:
				{
					UBWidget_SurveyItemTwoTextBtn* twoTextBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemTwoTextBtn>(EDynamicWidgetParts::SurveyItemTwoTextBtn);
					if (twoTextBtnWidget != nullptr)
					{
						twoTextBtnWidget->OwnerPannel = this;
						twoTextBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(twoTextBtnWidget);
					}
				}
				break;
				case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_TWO_DOWN_BTN:
				{
					UBWidget_SurveyItemTwoTextDownBtn* twoTextDownBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemTwoTextDownBtn>(EDynamicWidgetParts::SurveyItemTwoTextDownBtn);
					if (twoTextDownBtnWidget != nullptr)
					{
						twoTextDownBtnWidget->OwnerPannel = this;
						twoTextDownBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(twoTextDownBtnWidget);
					}
				}
				break;
				case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_MANY_BTN:
				{
					UBWidget_SurveyItemManyTextBtn* manyTextDownBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemManyTextBtn>(EDynamicWidgetParts::SurveyItemManyTextBtn);
					if (manyTextDownBtnWidget != nullptr)
					{
						manyTextDownBtnWidget->OwnerPannel = this;
						manyTextDownBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(manyTextDownBtnWidget);
					}
				}
				break;
				case E_SURVEY_TYPE::E_SURVEY_TYPE_TEXT_DROPDOWN:
				{
					UBWidget_SurveyItemDropDown* manyTextDownBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemDropDown>(EDynamicWidgetParts::SurveyItemDropDown);
					if (manyTextDownBtnWidget != nullptr)
					{
						manyTextDownBtnWidget->OwnerPannel = this;
						manyTextDownBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(manyTextDownBtnWidget);
					}
				}
				break;
				case E_SURVEY_TYPE::E_SURVEY_TYPE_IMG_MANY_BTN:
				{
					UBWidget_SurveyItemManyImgBtn* foodBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_SurveyItemManyImgBtn>(EDynamicWidgetParts::SurveyItemManyImgBtn);
					if (foodBtnWidget != nullptr)
					{
						foodBtnWidget->OwnerPannel = this;
						foodBtnWidget->SetCurSurveyItem(stInfoTemp);
						C_ScrollBox_SurveyItem.Get()->AddChild(foodBtnWidget);
					}
				}
				break;
				default:
					break;
			}
		}

		UBWidget_Survey_NextBtn* nextBtnWidget = B_HUD->CreateDynamicWidget<UBWidget_Survey_NextBtn>(EDynamicWidgetParts::SurveyNextBtn);
		if (nextBtnWidget != nullptr)
		{
			FText txtNext = _CurPage == _TotalPage ? GET_BTEXT(30) : GET_BTEXT(14);
			nextBtnWidget->SetBtnText(txtNext);
			nextBtnWidget->OwnerPannel = this;
			C_ScrollBox_SurveyItem.Get()->AddChild(nextBtnWidget);
		}
	}
}

void UBWidget_Survey::_SetPage(int32 nCurPage)
{
	_CurPage = nCurPage;
	BP_Top_Survey_UMG->SetTopSurvey( _CurPage, _TotalPage );
}

bool UBWidget_Survey::CheckSurveyPage()
{
	for( int i = 0; i < C_ScrollBox_SurveyItem->GetChildrenCount(); i++ )
	{
		UBWidget_SurveyItemBase* It = Cast<UBWidget_SurveyItemBase>( C_ScrollBox_SurveyItem->GetChildAt( i ) );
		if( It )
		{
			if( It->IsCheckSelected() == false )
			{
				return false;
			}
		}
	}
		
	return true;

	/*
	bool isSuccess = false;

	if( BP_SurveyItem_UMG.IsValid() )
	{
		ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
		if( gameMode )
		{
			if( gameMode->GetCurSurveyInfo().eSurveyType == E_SURVEY_TYPE::E_SURVEY_TYPE_SUBJECTIVE )
				isSuccess = BP_SurveyItem_UMG.Get()->GetEditBoxSurveyState();
			else
				isSuccess = BP_SurveyItem_UMG.Get()->GetCheckBoxSurveyState();
		}
	}

	return isSuccess;
	*/
}

bool UBWidget_Survey::OnClickNextBtn()
{
	if( CheckSurveyPage() )
	{
		if( _CurPage < _TotalPage )
		{
			_SetPage( _CurPage + 1 );
			_SetSurveyInfo();
		}
		else
		{
			ABGameMode_Main* gameMode = Cast<ABGameMode_Main>( GetGameMode() );
			if( gameMode != nullptr )
			{
				gameMode->ChangeMode( E_MODE::E_MODE_SURVEY_RESULT );
				CloseUI();
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}