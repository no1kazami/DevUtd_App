// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

/** Called when Firebase Analytics module is initialized */
DECLARE_DELEGATE_OneParam(FOnFirebaseAnalyticsInitializeCompleteDelegate, const bool);

/** Called when Firebase retrieving Analytics Instance Id is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAnalyticsGetAnalyticsInstanceIdCompleteDelegate, const bool,  const FString&);
