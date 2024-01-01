// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "TestLab/TestLabLibrary.h"
#include "UltimateMobileKit.h"



UUltimateMobileKitTestLab::UUltimateMobileKitTestLab(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const bool UUltimateMobileKitTestLab::IsFirebaseTestLabInitialized()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseTestLabPtr FirebaseTestLab = UltimateMobileKit->GetFirebaseTestLab();

		if (FirebaseTestLab.IsValid())
		{
			return FirebaseTestLab->IsInitialized();
		}
	}

	return false;
}

void UUltimateMobileKitTestLab::TakeScreenshot(const FString& Label)
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseTestLabPtr FirebaseTestLab = UltimateMobileKit->GetFirebaseTestLab();

		if (FirebaseTestLab.IsValid())
		{
			FirebaseTestLab->TakeScreenshot(Label);
		}
	}
}

void UUltimateMobileKitTestLab::FinishTest()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseTestLabPtr FirebaseTestLab = UltimateMobileKit->GetFirebaseTestLab();

		if (FirebaseTestLab.IsValid())
		{
			FirebaseTestLab->FinishTest();
		}
	}
}

int32 UUltimateMobileKitTestLab::GetGameLoopScenario()
{
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FFirebaseTestLabPtr FirebaseTestLab = UltimateMobileKit->GetFirebaseTestLab();

		if (FirebaseTestLab.IsValid())
		{
			return FirebaseTestLab->GetGameLoopScenario();
		}
	}

	return 0;
}
