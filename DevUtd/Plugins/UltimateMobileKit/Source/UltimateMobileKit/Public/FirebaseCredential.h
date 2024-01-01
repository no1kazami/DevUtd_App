// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/auth/credential.h"
#endif

#include "FirebaseCredential.generated.h"

/** Provider for Firebase user authentication */
UENUM(BlueprintType)
enum class EFirebaseProvider : uint8
{
	Firebase,
	Password,
	Facebook,
	Google,
	GooglePlayGames,
	GameCenter,
	GitHub,
	Twitter,
    Phone
};

/** Authentication credentials for an authentication provider */
UCLASS()
class ULTIMATEMOBILEKIT_API UFirebaseCredential : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Creates email credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Email Credential"))
	static UFirebaseCredential* EmailCredential(const FString& Email, const FString& Password);

	/** Creates Facebook credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Facebook Credential"))
	static UFirebaseCredential* FacebookCredential(const FString& AccessToken);

	/** Creates Google credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Google Credential"))
	static UFirebaseCredential* GoogleCredential(const FString& IdToken, const FString& AccessToken);

	/** Creates Google Play Games credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Google Play Games Credential"))
	static UFirebaseCredential* GooglePlayGamesCredential(const FString& ServerAuthCode);

	/** Creates GitHub credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase GitHub Credential"))
	static UFirebaseCredential* GitHubCredential(const FString& Token);

	/** Creates Twitter credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Twitter Credential"))
	static UFirebaseCredential* TwitterCredential(const FString& Token, const FString& Secret);
    
	/** Creates Phone credential */
	UFUNCTION(BlueprintPure, Category = "Ultimate Mobile Kit|Credential", meta = (DisplayName = "Firebase Phone Credential"))
	static UFirebaseCredential* PhoneCredential(const FString& VerificationId, const FString& VerificationCode);

	/** Converts string to provider */
	static const EFirebaseProvider StringToProvider(const FString& Credential);

	/** Converts provider to string */
	static const FString ProviderToString(const EFirebaseProvider Credential);

	/** Returns Firebase provider type */
	const EFirebaseProvider GetType() const;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	/** Returns Firebase native credential */
	firebase::auth::Credential GetNativeCredential() const;

	/** Create Credential from Native Credential */
	static UFirebaseCredential* MakeNativeCredential(firebase::auth::Credential Credential, const EFirebaseProvider& Type);
#endif

private:
	EFirebaseProvider Credential;
	FString Email;
	FString Password;
	FString AccessToken;
	FString ServerAuthCode;
	FString IdToken;
	FString Token;
	FString Secret;
    FString VerificationId;
    FString VerificationCode;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	TSharedPtr<firebase::auth::Credential, ESPMode::ThreadSafe> NativeCredential;
#endif
};
