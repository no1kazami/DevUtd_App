// Fill out your copyright notice in the Description page of Project Settings.

#include "BWidget_SwipeScroll.h"
#include "Kismet/KismetMathLibrary.h"

#define AUTO_MOVE_TIME 4.f
#define PAGE_CIRCLE_IMAGE_SIZE FVector2D( 16.f, 16.f )

void UBWidget_SwipeScroll::Init()
{
	Super::Init();

	_IsSwiping = false;
	_IsPlus = true;
	_IsCheckRemainX = false;
	_FirstTouchLocationX = 0.f;
	_TouchLocationX = 0.f;
	_MoveTouchLocationX = 0.f;
	_CurrentScrollBoxOffset = 0.f;
	_FinalX = 0.f;
	_ContentsSizeX = 1.f;
	_CurAutoMoveTime = 0.f;
	_CurPage = 1;
	_PrevPage = 0;
	_IsAutoCheckRemainX = false;

	_ClickSensitivity = UFBM_SaveGame::Get().GetScrollClickSensitivity();
}

void UBWidget_SwipeScroll::SetContentsSizeX( float contentsSizeX )
{
	_ContentsSizeX = contentsSizeX;
}

void UBWidget_SwipeScroll::OnClose()
{

}

void UBWidget_SwipeScroll::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
{
	Super::NativeTick( MyGeometry, InDeltaTime );

	if( _IsSwiping )
	{
		if( _CurrentScrollBoxOffset >= 0.f )
		{
			if( (_CurrentScrollBoxOffset + _ContentsSizeX) > C_ScrollBox_Swipe->GetDesiredSize().X )
			{
				_CurrentScrollBoxOffset = C_ScrollBox_Swipe->GetDesiredSize().X - 1.f - _ContentsSizeX;
			}

			C_ScrollBox_Swipe->SetScrollOffset( _CurrentScrollBoxOffset );
		}
		else
		{
			C_ScrollBox_Swipe->ScrollToStart();
			_CurrentScrollBoxOffset = 0.f;
		}
	}
	else
	{
		_CurAutoMoveTime += InDeltaTime;
		if (_CurAutoMoveTime > AUTO_MOVE_TIME )
		{
			_CurAutoMoveTime = 0.f;
			_SetAutoMoveRemainMoveX();
		}
	}

	_CheckRemainMoveX( InDeltaTime );
}

void UBWidget_SwipeScroll::Swipe_InputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex )
{
	FGeometry swipeScrollGeo = C_ScrollBox_Swipe->GetCachedGeometry();
	bool isUnder = swipeScrollGeo.IsUnderLocation( swipeScrollGeo.LocalToAbsolute( TouchLocation ) );
	if( isUnder )
	{
		switch( Type )
		{
		case ETouchType::Began:
			_FirstTouchLocationX = TouchLocation.X;
			_TouchLocationX = TouchLocation.X;
			_MoveTouchLocationX = TouchLocation.X;
			_IsSwiping = true;
			_CurAutoMoveTime = 0.f;
			break;
		case ETouchType::Ended:
			_IsSwiping = false;
			_SetRemainMoveX();
			if( FMath::Abs( TouchLocation.X - _FirstTouchLocationX ) < _ClickSensitivity )
			//if( _FirstTouchLocationX == TouchLocation.X )
			{
				int32 clickItemIndex = _CurPage - 1;
				if ( clickItemIndex >= 0 && clickItemIndex < _ScrollItemIndexList.Num())
				{
					_OnClickSwipeScrollItem( _ScrollItemIndexList[clickItemIndex] );
				}
			}
			break;
		case ETouchType::Moved:
			_MoveTouchLocationX = TouchLocation.X;
			_CurrentScrollBoxOffset = _TouchLocationX - _MoveTouchLocationX + _CurrentScrollBoxOffset;
			_TouchLocationX = TouchLocation.X;
			break;
		case ETouchType::Stationary:
			break;
		default:
			break;
		}
	}
}

void UBWidget_SwipeScroll::InitSwipeScrollComponent()
{
	C_ScrollBox_Swipe->ClearChildren();
	C_ScrollBox_Swipe->ScrollToStart();
	C_HB_PageCircle->ClearChildren();

	_ScrollItemIndexList.Empty();
}

void UBWidget_SwipeScroll::AddSwipeScrollChild( UImage* addChild, int32 itemIndex, bool isLast/* = false */)
{
	C_ScrollBox_Swipe->AddChild( addChild );
	_ScrollItemIndexList.AddUnique( itemIndex );

	UTexture2D* texturePageCircle = GetTexture( TEXT( "Icon/Page_Circle" ) );
	if( texturePageCircle != nullptr )
	{
		UImage* pageCircleImage = NewObject<UImage>( UImage::StaticClass() );
		if( pageCircleImage != nullptr )
		{
			pageCircleImage->SetBrushFromTexture( texturePageCircle, true );
			pageCircleImage->SetBrushSize( PAGE_CIRCLE_IMAGE_SIZE );
			pageCircleImage->SetVisibility( ESlateVisibility::Visible );
			if ( C_HB_PageCircle->GetChildrenCount() == 0)
			{
				pageCircleImage->SetColorAndOpacity( Color_Black );
			}
			C_HB_PageCircle->AddChild( pageCircleImage );
		}
	}

	if( isLast == false )
	{
		USpacer* addSpacer = NewObject<USpacer>( USpacer::StaticClass() );
		if( addSpacer != nullptr)
		{
			addSpacer->SetSize( FVector2D( 30.f, 0.f ) );
			C_HB_PageCircle->AddChild( addSpacer );
		}
	}
}

void UBWidget_SwipeScroll::_OnClickSwipeScrollItem( int32 itemIndex )
{
	
}

void UBWidget_SwipeScroll::_SetRemainMoveX()
{
	if( _MoveTouchLocationX > _FirstTouchLocationX )
	{
		_IsPlus = !((_MoveTouchLocationX - _FirstTouchLocationX) > 50.f);
	}
	else if( _MoveTouchLocationX < _FirstTouchLocationX )
	{
		_IsPlus = (_FirstTouchLocationX - _MoveTouchLocationX) > 50.f;
	}

	_IsCheckRemainX = true;
	float currentOffset = C_ScrollBox_Swipe->GetScrollOffset();

	if( _IsPlus )
	{
		if( UKismetMathLibrary::GenericPercent_FloatFloat( currentOffset, _ContentsSizeX ) == 0.f )
		{
			_FinalX = currentOffset;
		}
		else
		{
			_FinalX = currentOffset + (_ContentsSizeX - UKismetMathLibrary::GenericPercent_FloatFloat( currentOffset, _ContentsSizeX ));
		}
	}
	else
	{
		_FinalX = currentOffset - UKismetMathLibrary::GenericPercent_FloatFloat( currentOffset, _ContentsSizeX );
	}
}

void UBWidget_SwipeScroll::_CheckRemainMoveX( float fDelta )
{
	if( !_IsSwiping && (_IsCheckRemainX || _IsAutoCheckRemainX) )
	{
		float localData = fDelta * 5000.f;
		if( _IsPlus )
		{
			if( C_ScrollBox_Swipe->GetScrollOffset() < _FinalX )
			{
				_CurrentScrollBoxOffset = FMath::Min( C_ScrollBox_Swipe->GetDesiredSize().X - 1.f - _ContentsSizeX, FMath::Min( _CurrentScrollBoxOffset + localData, _FinalX ) );
				C_ScrollBox_Swipe->SetScrollOffset( _CurrentScrollBoxOffset );
			}
			else
			{
				_SetPageIcon();
			}
		}
		else
		{
			if( C_ScrollBox_Swipe->GetScrollOffset() > _FinalX )
			{
				_CurrentScrollBoxOffset = FMath::Max( _CurrentScrollBoxOffset - localData, _FinalX );
				C_ScrollBox_Swipe->SetScrollOffset( _CurrentScrollBoxOffset );
			}
			else
			{
				_SetPageIcon();
			}
		}
	}
}

void UBWidget_SwipeScroll::_SetPageIcon()
{
	_IsCheckRemainX = false;
	_IsAutoCheckRemainX = false;
	_CurAutoMoveTime = 0.f;

	int32 ChildrenCount = C_ScrollBox_Swipe->GetChildrenCount();
	float currentOffset = C_ScrollBox_Swipe->GetScrollOffset();
	float deX = C_ScrollBox_Swipe->GetDesiredSize().X;

	int32 calcPage = currentOffset / _ContentsSizeX + 1;
	if( _IsPlus )
	{
		_CurPage = FMath::Min( calcPage, ChildrenCount );
		_PrevPage = _CurPage - 1;
	}
	else
	{
		_CurPage = FMath::Max( calcPage, 1 );
		_PrevPage = _CurPage + 1;
	}


	for( int i = 0; i < C_HB_PageCircle->GetChildrenCount(); i++ )
	{
		UImage* curCircleImage = Cast<UImage>( C_HB_PageCircle->GetChildAt( i ) );
		if( curCircleImage != nullptr )
		{
			if( (i % 2) == 0 )
			{
				curCircleImage->SetColorAndOpacity( ((i / 2) + 1 == _CurPage) ? Color_Black : Color_White );
			}
		}
	}
}

void UBWidget_SwipeScroll::_SetAutoMoveRemainMoveX()
{
	int32 ChildrenCount = C_ScrollBox_Swipe->GetChildrenCount();
	if( ChildrenCount <= 1 )
	{
		return;
	}

	if( _CurPage <= 1 )
	{
		_IsPlus = true;
	}
	else if ( _CurPage >= ChildrenCount )
	{
		_IsPlus = false;
	}
	else
	{
		_IsPlus = _CurPage > _PrevPage;
	}

	_IsAutoCheckRemainX = true;
	float currentOffset = C_ScrollBox_Swipe->GetScrollOffset();

	if( _IsPlus )
	{
		_FinalX = currentOffset + (_ContentsSizeX - UKismetMathLibrary::GenericPercent_FloatFloat( currentOffset, _ContentsSizeX ));
	}
	else
	{
		_FinalX = currentOffset - (_ContentsSizeX - UKismetMathLibrary::GenericPercent_FloatFloat( currentOffset, _ContentsSizeX ));
	}
}

