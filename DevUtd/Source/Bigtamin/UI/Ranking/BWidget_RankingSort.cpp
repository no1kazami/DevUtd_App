#include "BWidget_RankingSort.h"

void UBWidget_RankingSort::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Sort_Cancel, &UBWidget_RankingSort::_OnClick_SortCancel );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Goal, &UBWidget_RankingSort::_OnClick_SortGoal );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Assist, &UBWidget_RankingSort::_OnClick_SortAssist );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Point, &UBWidget_RankingSort::_OnClick_SortPoint );
	ButtonDelegate_Clicked( this, C_Btn_Sort_Game, &UBWidget_RankingSort::_OnClick_SortGame );
}

void UBWidget_RankingSort::OnClose()
{
	Super::OnClose();
}

void UBWidget_RankingSort::InitRankingSort( const E_SORT_TYPE sortType )
{
	_SortType = sortType;
	_UpdateSortTextColor();
}

void UBWidget_RankingSort::_OnClick_SortCancel()
{
	this->SetVisibility( ESlateVisibility::Collapsed );
}

void UBWidget_RankingSort::_OnClick_SortGoal()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_GOAL );
}

void UBWidget_RankingSort::_OnClick_SortAssist()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_ASSIST );
}

void UBWidget_RankingSort::_OnClick_SortPoint()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_POINT );
}

void UBWidget_RankingSort::_OnClick_SortGame()
{
	_ClickSortBtn( E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE );
}

void UBWidget_RankingSort::_ClickSortBtn( const E_SORT_TYPE sortType )
{
	_SortType = sortType;
	OnClickRankingSort.Broadcast( _SortType );
}

void UBWidget_RankingSort::_UpdateSortTextColor()
{
	C_Txt_Sort_Goal->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_Assist->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_Point->SetColorAndOpacity( Color_GrayFont );
	C_Txt_Sort_Game->SetColorAndOpacity( Color_GrayFont );

	switch( _SortType )
	{
	case E_SORT_TYPE::E_SORT_TYPE_GOAL:
		C_Txt_Sort_Goal->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ASSIST:
		C_Txt_Sort_Assist->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_POINT:
		C_Txt_Sort_Point->SetColorAndOpacity( Color_SortSelectFont );
		break;
	case E_SORT_TYPE::E_SORT_TYPE_ATTENDANCE:
		C_Txt_Sort_Game->SetColorAndOpacity( Color_SortSelectFont );
		break;
	default:
		break;
	}
}
