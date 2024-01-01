// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/BWidget.h"
#include "BWidget_SwipeScroll.generated.h"

///////////////////////////////////////////////////////////////
// 스와이프 가능한 스크롤 클래스
///////////////////////////////////////////////////////////////
UCLASS()
class BIGTAMIN_API UBWidget_SwipeScroll : public UBWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY( meta = (BindWidget) )
		TWeakObjectPtr<UScrollBox>  C_ScrollBox_Swipe;

	UPROPERTY( meta = (BindWidget) )
		TWeakObjectPtr<UHorizontalBox> C_HB_PageCircle;

private:
	bool _IsSwiping;
	bool _IsPlus;
	bool _IsCheckRemainX;
	bool _IsAutoCheckRemainX = false;
	float _FirstTouchLocationX;
	float _TouchLocationX;
	float _MoveTouchLocationX;
	float _CurrentScrollBoxOffset;
	float _ContentsSizeX;
	float _FinalX;
	float _CurAutoMoveTime = 0.f;
	int32 _CurPage = 1;
	int32 _PrevPage = 0;

	TArray<int32> _ScrollItemIndexList;
	int32 _ClickSensitivity = 1;

public:
	virtual void Init() override;
	virtual void OnClose() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;

	void SetContentsSizeX( float contentsSizeX );
	void Swipe_InputTouch( uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex );
	void InitSwipeScrollComponent();
	void AddSwipeScrollChild( UImage* addChild, int32 itemIndex, bool isLast = false );

protected:
	virtual void _OnClickSwipeScrollItem( int32 itemIndex );

private:
	void _SetRemainMoveX();
	void _CheckRemainMoveX( float fDelta );
	void _SetPageIcon();
	void _SetAutoMoveRemainMoveX();
};
