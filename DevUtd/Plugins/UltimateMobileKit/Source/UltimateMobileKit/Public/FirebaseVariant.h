// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "FirebaseVariant.generated.h"

/** Type of Firebase Variant */
UENUM(BlueprintType)
enum class EFirebaseVariantType : uint8
{
	String,
	Float,
	Integer,
	Boolean
};

/** Variant data type used by Firebase libraries. This is unified data type which can be constructed from String, Integer, Float and Boolean. */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseVariant : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Makes new Firebase variant of string type */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Variant", meta = (DisplayName = "Firebase String Variant"))
	static UFirebaseVariant* FirebaseStringVariant(const FString& Name, const FString& Value);

	/** Makes new Firebase variant of integer type */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Variant", meta = (DisplayName = "Firebase Integer Variant"))
	static UFirebaseVariant* FirebaseIntegerVariant(const FString& Name, const int32 Value);

	/** Makes new Firebase variant of float type */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Variant", meta = (DisplayName = "Firebase Float Variant"))
	static UFirebaseVariant* FirebaseFloatVariant(const FString& Name, const float Value);

	/** Makes new Firebase variant of boolean type */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Variant", meta = (DisplayName = "Firebase Boolean Variant"))
	static UFirebaseVariant* FirebaseBooleanVariant(const FString& Name, const bool Value);

	/** Get Firebase type of variant */
	const EFirebaseVariantType GetType() const;

	/** Get name of Firebase variant */
	const FString& GetName() const;

	/** Get Firebase variant as string type */
	const FString& GetStringVariant() const;

	/** Get Firebase variant as integer type */
	const int32 GetIntegerVariant() const;

	/** Get Firebase variant as boolean type */
	const bool GetBooleanVariant() const;

	/** Get Firebase variant as float type */
	const float GetFloatVariant() const;

private:
	EFirebaseVariantType Variant;
	FString NameVariant;
	FString StringVariant;
	int32 IntegerVariant;
	float FloatVariant;
	bool BooleanVariant;
};
