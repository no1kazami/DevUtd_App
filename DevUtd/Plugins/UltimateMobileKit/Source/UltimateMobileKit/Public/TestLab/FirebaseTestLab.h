// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

/** Run automatic and customized tests for your app on virtual and physical devices hosted by Google. */
class ULTIMATEMOBILEKIT_API FFirebaseTestLab
{
public:
	FFirebaseTestLab();
	virtual ~FFirebaseTestLab();

	/** Initialize the Firebase Test Lab API  */
	void Init();

	/** Shutdown the Firebase Test Lab API  */
	void Shutdown();

	/** Check if Firebase Test Lab is initialized */
	const bool IsInitialized() const;

	/** Make a screenshot for Firebase Test Lab */
	void TakeScreenshot(const FString& Label) const;

	/** Finishes test of Firebase Test Lab */
	void FinishTest() const;

	/** Gets game loop scenario of Firebase Test Lab */
	int32 GetGameLoopScenario() const;

private:
	bool bInitialized = false;
};
