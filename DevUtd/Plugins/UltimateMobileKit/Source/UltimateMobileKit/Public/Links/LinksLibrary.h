// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Links/LinksListener.h"
#include "LinksLibrary.generated.h"

/** Blueprint implementation of FirebaseLinks. Firebase Links is for generating and receiving links, whether or not the app is already installed. */
UCLASS()
class ULTIMATEMOBILEKIT_API UUltimateMobileKitLinks : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Check if Firebase Dynamic Links is initialized */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Ultimate Mobile Kit|Dynamic Links")
	static const bool IsFirebaseLinksInitialized();

	/** Fetch any pending dynamic links. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Dynamic Links", DisplayName = "Firebase Dynamic Links Fetch")
	static void Fetch();

	/** Create listener used to receive Dynamic Links */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Dynamic Links", DisplayName = "Firebase Dynamic Links Create Listener")
	static UFirebaseLinksListener* CreateListener();

	/** Creates a long Dynamic Link from the given parameters. */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Mobile Kit|Dynamic Links", DisplayName = "Firebase Dynamic Links Get Long Link")
	static const FFirebaseGeneratedDynamicLink GetLongLink(const FFirebaseDynamicLinkComponents& DynamicLinkComponents);
};
