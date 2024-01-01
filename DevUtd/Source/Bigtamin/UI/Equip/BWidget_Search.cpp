// Fill out your copyright notice in the Description page of Project Settings.


#include "BWidget_Search.h"
#include "UI/BWidget_Top.h"
#include "UI/Boots/BWidget_BootsSlot.h"
#include "Bigtamin.h"

void UBWidget_Search::Init()
{
	Super::Init();

	ButtonDelegate_Clicked( this, C_Btn_Delete, &UBWidget_Search::_OnClick_Delete );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch1, &UBWidget_Search::_OnClick_Search1 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch2, &UBWidget_Search::_OnClick_Search2 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch3, &UBWidget_Search::_OnClick_Search3 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch4, &UBWidget_Search::_OnClick_Search4 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch5, &UBWidget_Search::_OnClick_Search5 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch6, &UBWidget_Search::_OnClick_Search6 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch7, &UBWidget_Search::_OnClick_Search7 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch8, &UBWidget_Search::_OnClick_Search8 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch9, &UBWidget_Search::_OnClick_Search9 );
	ButtonDelegate_Clicked( this, C_Btn_SaveSearch10, &UBWidget_Search::_OnClick_Search10 );

	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch1 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch2 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch3 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch4 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch5 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch6 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch7 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch8 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch9 );
	_BtnSaveSearch.AddUnique( C_Btn_SaveSearch10 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch1 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch2 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch3 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch4 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch5 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch6 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch7 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch8 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch9 );
	_TxtSaveSearch.AddUnique( C_Txt_SaveSearch10 );

	BP_Top_Search->Init();
	BP_Top_Search->ChangeTopMode( E_MODE::E_MODE_SEARCH );
	InitSearch();

	GInst->AddBackInput( this );
}

void UBWidget_Search::OnClose()
{
	Super::OnClose();
}

void UBWidget_Search::InitSearch()
{
	BP_Top_Search->SetSearchText( FText::FromString( "" ), true );

	C_WS_Search->SetActiveWidgetIndex( 0 );

	// 최근 검색어 셋팅
	_InitSearchSaveData();
}

void UBWidget_Search::HandleTopSearch( const FText handleTopText )
{
	if( handleTopText.IsEmpty() )
	{
		return;
	}

	_SearchData( handleTopText );

	UFBM_SaveGame::Get().AddSearchData( handleTopText.ToString(), true );
}

void UBWidget_Search::HandleTopSearchImg()
{
	if( C_WS_Search->GetActiveWidgetIndex() == 1 )
	{
		InitSearch();
	}
}

bool UBWidget_Search::_OnBackInput()
{
	if ( C_WS_Search->GetActiveWidgetIndex() == 1)
	{
		InitSearch();
		return false;
	}

	Super::_OnBackInput();
	CloseUI();

	return true;
}

void UBWidget_Search::_OnClick_Delete()
{
	UFBM_SaveGame::Get().DeleteSearchData();

	_InitSearchSaveData();
}

void UBWidget_Search::_OnClick_Search1()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch1->GetText() );
}

void UBWidget_Search::_OnClick_Search2()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch2->GetText() );
}

void UBWidget_Search::_OnClick_Search3()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch3->GetText() );
}

void UBWidget_Search::_OnClick_Search4()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch4->GetText() );
}

void UBWidget_Search::_OnClick_Search5()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch5->GetText() );
}

void UBWidget_Search::_OnClick_Search6()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch6->GetText() );
}

void UBWidget_Search::_OnClick_Search7()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch7->GetText() );
}

void UBWidget_Search::_OnClick_Search8()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch8->GetText() );
}

void UBWidget_Search::_OnClick_Search9()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch9->GetText() );
}

void UBWidget_Search::_OnClick_Search10()
{
	BP_Top_Search->SetSearchText( C_Txt_SaveSearch10->GetText() );
}

void UBWidget_Search::_InitSearchSaveData()
{
	C_WS_SearchResult->SetActiveWidgetIndex(0);

	const TArray<FString> searchData = UFBM_SaveGame::Get().GetSearchData();
	int32 searchDataNum = searchData.Num();
	if( searchDataNum == 0 )
	{
		C_WS_SearchText->SetActiveWidgetIndex( 0 );
	}
	else
	{
		C_WS_SearchText->SetActiveWidgetIndex( 1 );
		C_ScrollBox_SearchText->ScrollToStart();

		for( int32 index = 0; index < searchDataNum; ++index )
		{
			if( _TxtSaveSearch.IsValidIndex( index ) )
			{
				_TxtSaveSearch[index]->SetText( FText::FromString( searchData.Last( index ) ) );
			}
			if( _BtnSaveSearch.IsValidIndex( index ) )
			{
				_BtnSaveSearch[index]->SetVisibility( ESlateVisibility::Visible );
			}
		}
		for( int32 emptyIndex = searchDataNum; emptyIndex < _TxtSaveSearch.Num(); ++emptyIndex )
		{
			if( _BtnSaveSearch.IsValidIndex( emptyIndex ) )
			{
				_BtnSaveSearch[emptyIndex]->SetVisibility( ESlateVisibility::Collapsed );
			}
		}
	}
}

void UBWidget_Search::_SearchData( const FText searchText )
{
	C_WS_Search->SetActiveWidgetIndex( 1 );

	C_ScrollBox_Search->ClearChildren();
	C_ScrollBox_Search->ScrollToStart();

	TArray<int> arrayBootsIndexInfo;
#if DB_BOOTS_DATA
	UFBM_SaveGame::Get().SearchBootsInfo_DB( searchText, arrayBootsIndexInfo );
#else
	GInst->SearchBootsInfo( searchText, arrayBootsIndexInfo );
#endif

	int32 searchNum = arrayBootsIndexInfo.Num();
	for( int32 slotIndex = 0; slotIndex < searchNum; ++slotIndex )
	{
		UBWidget_BootsSlot* bootsSlotWidget = B_HUD->CreateDynamicWidget<UBWidget_BootsSlot>( EDynamicWidgetParts::BootsSlot );
		if( bootsSlotWidget != nullptr )
		{
			bootsSlotWidget->OwnerPannel = this;
#if DB_BOOTS_DATA
			bootsSlotWidget->SetBootSlotData_DB( slotIndex, arrayBootsIndexInfo[slotIndex] );
#else
			bootsSlotWidget->SetBootSlotData( slotIndex, arrayBootsIndexInfo[slotIndex] );
#endif
			C_ScrollBox_Search->AddChild( bootsSlotWidget );
		}
	}

	C_WS_SearchResult->SetActiveWidgetIndex( searchNum > 0 ? 0 : 1  );
}
