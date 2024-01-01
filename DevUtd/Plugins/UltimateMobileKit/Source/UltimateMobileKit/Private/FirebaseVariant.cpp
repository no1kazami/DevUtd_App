// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "FirebaseVariant.h"

UFirebaseVariant::UFirebaseVariant(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Variant = EFirebaseVariantType::String;
	NameVariant = FString();
	StringVariant = FString();
	IntegerVariant = 0;
	FloatVariant = 0;
	BooleanVariant = false;
}

UFirebaseVariant* UFirebaseVariant::FirebaseStringVariant(const FString& Name, const FString& Value)
{
	UFirebaseVariant* UltimateMobileKitVariant = NewObject<UFirebaseVariant>();
	UltimateMobileKitVariant->Variant = EFirebaseVariantType::String;
	UltimateMobileKitVariant->NameVariant = Name;
	UltimateMobileKitVariant->StringVariant = Value;

	return UltimateMobileKitVariant;
}

UFirebaseVariant* UFirebaseVariant::FirebaseIntegerVariant(const FString& Name, const int32 Value)
{
	UFirebaseVariant* UltimateMobileKitVariant = NewObject<UFirebaseVariant>();
	UltimateMobileKitVariant->Variant = EFirebaseVariantType::Integer;
	UltimateMobileKitVariant->NameVariant = Name;
	UltimateMobileKitVariant->IntegerVariant = Value;

	return UltimateMobileKitVariant;
}

UFirebaseVariant* UFirebaseVariant::FirebaseFloatVariant(const FString& Name, const float Value)
{
	UFirebaseVariant* UltimateMobileKitVariant = NewObject<UFirebaseVariant>();
	UltimateMobileKitVariant->Variant = EFirebaseVariantType::Float;
	UltimateMobileKitVariant->NameVariant = Name;
	UltimateMobileKitVariant->FloatVariant = Value;

	return UltimateMobileKitVariant;
}

UFirebaseVariant* UFirebaseVariant::FirebaseBooleanVariant(const FString& Name, const bool Value)
{
	UFirebaseVariant* UltimateMobileKitVariant = NewObject<UFirebaseVariant>();
	UltimateMobileKitVariant->Variant = EFirebaseVariantType::Boolean;
	UltimateMobileKitVariant->NameVariant = Name;
	UltimateMobileKitVariant->BooleanVariant = Value;

	return UltimateMobileKitVariant;
}

const EFirebaseVariantType UFirebaseVariant::GetType() const
{
	return Variant;
}

const FString& UFirebaseVariant::GetName() const
{
	return NameVariant;
}

const FString& UFirebaseVariant::GetStringVariant() const
{
	return StringVariant;
}

const int32 UFirebaseVariant::GetIntegerVariant() const
{
	return IntegerVariant;
}

const bool UFirebaseVariant::GetBooleanVariant() const
{
	return BooleanVariant;
}

const float UFirebaseVariant::GetFloatVariant() const
{
	return FloatVariant;
}
