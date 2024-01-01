// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "OnlineAsyncTaskManager.h"
#include "CoreMinimal.h"

/** Ultimate Mobile Kit version of the async task manager */
class FUltimateMobileKitAsyncTaskManager : public FOnlineAsyncTaskManager
{
public:

	FUltimateMobileKitAsyncTaskManager() {}

	virtual void OnlineTick() override {}
};
