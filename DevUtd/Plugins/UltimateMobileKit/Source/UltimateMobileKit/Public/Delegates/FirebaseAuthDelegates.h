// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "FirebaseCredential.h"
#include "FirebaseAuthDelegates.generated.h"


/** Error code returned by Firebase Authentication functions. */
UENUM(BlueprintType)
enum class EFirebaseAuthError : uint8
{
	/** Success */
	None,

	/** An unknown error occurred. */
	UnknownError,

	/** Indicates an account already exists with the same email address but using different sign-in credentials. Account linking is required. Caused by "Sign in with credential" methods. */
	AccountExistsWithDifferentCredentials,

	/** This can happen when certain methods on App are performed, when the auth API is not loaded. */
	ApiNotAvailable,

	/** Indicates the App is not authorized to use Firebase Authentication with the provided API Key. Common error code for all API Methods. On Android this error should no longer occur (as of 2016 v3). Common error code for all API Methods. */
	AppNotAuthorized,

	/** Indicates that the app could not be verified by Firebase during phone number authentication. */
	AppNotVerified,

	/** Indicates a general failure during the app verification flow. */
	AppVerificationFailed,

	/** Indicates that the reCAPTCHA token is not valid. */
	CaptchaCheckFailed,

	/** Indicates an attempt to link with a credential that has already been linked with a different Firebase account. Caused by "Set account info" methods. */
	CredentialAlreadyInUse,

	/** Indicates the service account and the API key belong to different projects. Caused by "Bring your own auth" methods. */
	CustomTokenMismatch,

	/** Indicates the email used to attempt a sign up is already in use. Caused by "Set account info" methods. */
	EmailAlreadyInUse,

	/** Indicates the out-of-band authentication code is expired. */
	ExpiredActionCode,

	/** This indicates an internal error. Common error code for all API Methods. */
	Failure,

	/** Indicates the out-of-band authentication code is invalid. */
	InvalidActionCode,

	/** Indicates an invalid API key was supplied in the request. For Android these should no longer occur (as of 2016 v3). Common error code for all API Methods. */
	InvalidApiKey,

	/** Indicates that an invalid APNS device token was used in the verifyClient request. */
	InvalidAppCredential,

	/** Indicates that the clientID used to invoke a web flow is invalid. */
	InvalidClientId,

	/** Indicates that the domain specified in the continue URI is not valid. */
	InvalidContinueUri,

	/** Indicates the IDP token or requestUri is invalid. Caused by "Sign in with credential" methods. */
	InvalidCredential,

	/** Indicates a validation error with the custom token. This error originates from "bring your own auth" methods. */
	InvalidCustomToken,

	/** Indicates an invalid email address. mCaused by "Sign in with password" methods. */
	InvalidEmail,

	/** Indicates that there are invalid parameters in the payload during a "send password reset email" attempt. */
	InvalidMessagePayload,

	/** Indicates that an invalid phone number was provided. This is caused when the user is entering a phone number for verification. */
	InvalidPhoneNumber,

	/** Indicates that the recipient email is invalid. */
	InvalidRecipientEmail,

	/** Indicates that the sender email is invalid during a "send password reset email" attempt. */
	InvalidSender,

	/** Indicates user's saved auth credential is invalid, the user needs to sign in again. Caused by requests with an STS id token. */
	InvalidUserToken,

	/** Indicates that an invalid verification code was used in the verifyPhoneNumber request. */
	InvalidVerificationCode,

	/** Indicates that an invalid verification ID was used in the verifyPhoneNumber request. */
	InvalidVerificationId,

	/** Indicates an error occurred while attempting to access the keychain. Common error code for all API Methods. */
	KeychainError,

	/** Indicates that the APNS device token is missing in the verifyClient request. */
	MissingAppCredential,

	/** Indicates that the APNs device token could not be obtained. The app may not have set up remote notification correctly, or may have failed to forward the APNs device token to FIRAuth if app delegate swizzling is disabled. */
	MissingAppToken,

	/** Indicates that a continue URI was not provided in a request to the backend which requires one. */
	MissingContinueUri,

	/** Indicates that an email address was expected but one was not provided. */
	MissingEmail,

	/** Indicates that the iOS bundle ID is missing when an iOS App Store ID is provided. */
	MissingIosBundleId,

	/** Represents the error code for when an application attempts to create an email/password account with an empty/null password field. */
	MissingPassword,

	/** Indicates that a phone number was not provided during phone number verification.0 */
	MissingPhoneNumber,

	/** Indicates that the phone auth credential was created with an empty verification code. */
	MissingVerificationCode,

	/** Indicates that the phone auth credential was created with an empty verification ID. */
	MissingVerificationId,

	/** Indicates a network error occurred (such as a timeout, interrupted connection, or unreachable host). These types of errors are often recoverable with a retry. Common error code for all API Methods. */
	NetworkRequestFailed,

	/** Internal api usage error code when there is no signed-in user and getAccessToken is called. */
	NoSignedInUser,

	/** Indicates an attempt to unlink a provider that is not linked. Caused by "Link credential" methods. */
	NoSuchProvider,

	/** Indicates that the app fails to forward remote notification to FIRAuth. */
	NotificationNotForwarded,

	/** Indicates the administrator disabled sign in with the specified identity provider. Caused by "Set account info" methods. */
	OperationNotAllowed,

	/** Indicates an attempt to link a provider to which the account is already linked. Caused by "Link credential" methods. */
	ProviderAlreadyLinked,

	/** Indicates that the quota of SMS messages for a given project has been exceeded. */
	QuotaExceeded,

	/** Indicates the user has attemped to change email or password more than 5 minutes after signing in, and will need to refresh the credentials. Caused by "Set account info" methods. */
	RequiresRecentLogin,

	/** Thrown when one or more of the credentials passed to a method fail to identify and/or authenticate the user subject of that operation. Inspect the error message to find out the specific cause. */
	RetryPhoneAuth,

	/** Indicates that the SMS code has expired. */
	SessionExpired,

	/** Indicates that too many requests were made to a server method. Common error code for all API methods. */
	TooManyRequests,

	/** Indicates that the domain specified in the continue URL is not white- listed in the Firebase console. */
	UnauthorizedDomain,

	/** Function will be implemented in a later revision of the API. */
	Unimplemented,

	/** Indicates the user’s account is disabled on the server. Caused by "Sign in with credential" methods. */
	UserDisabled,

	/** Indicates that an attempt was made to reauthenticate with a user which is not the current user. */
	UserMismatch,

	/** Indicates the user account was not found. Send password request email error code. Common error code for all API methods. */
	UserNotFound,

	/** Indicates the saved token has expired. For example, the user may have changed account password on another device. The user needs to sign in again on the device that made this request. Caused by requests with an STS id token. */
	UserTokenExpired,

	/** Indicates an attempt to set a password that is considered too weak. */
	WeakPassword,

	/** Indicates that an attempt was made to present a new web context while one was already being presented. */
	WebContextAlreadyPresented,

	/** Indicates that the URL presentation was cancelled prematurely by the user. */
	WebContextCancelled,

	/** Indicates the user attempted sign in with a wrong password. Caused by "Sign in with password" methods. */
	WrongPassword,

	/** The custom token corresponds to a different Firebase project. */
	CredentialMismatch,

	/** An invalid refresh token is provided. */
	InvalidRefreshToken,

	/** The grant type specified is invalid. */
	InvalidGrantType,

	/** No refresh token provided. */
	MissingRefreshToken,

	/** Indicates that Dynamic Links in the Firebase Console is not activated. */
	DynamicLinkNotActivated,
	
	/** Indicates that the operation was cancelled. */
	Cancelled,

	/** Indicates that the provider id given for the web operation is invalid. */
	InvalidProviderId,

	/** Indicates that an internal error occurred during a web operation. */
	WebInternalError,

	/** Indicates that 3rd party cookies or data are disabled, or that there was a problem with the browser. */
	WebStorateUnsupported,

	/** Indicates that an attempt was made to update the current user with a different tenant ID. */
	TenantIdMismatch,

	/** Indicates that a request was made to the backend with an associated tenant ID for an operation that does not support multi-tenancy. */
	UnsupportedTenantOperation,

	/** Indicates that an FDL domain used for an out of band code flow is either not configured or is unauthorized for the current project. */
	InvalidLinkDomain,

	/** Indicates that credential related request data is invalid. This can occur when there is a project number mismatch (sessionInfo, spatula header, temporary proof), an incorrect temporary proof phone number, or during game center sign in when the user is already signed into a different game center account. */
	RejectedCredential,

	/** User not logged in to Game Center */
	GameCenterNotLoggedIn
};

/** Firebase user account interface object */
USTRUCT(BlueprintType)
struct FFirebaseUserInterface
{
	GENERATED_USTRUCT_BODY()

	/** Display name associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString DisplayName;

	/** Email associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString Email;

	/** Photo url associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString PhotoUrl;

	/** Unique Firebase user ID for the user */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString UserID;

	/** Gets the phone number for the user, in E.164 format. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString PhoneNumber;

	/** Provider ID for the user (For example, "Facebook") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	EFirebaseProvider Provider;

	FFirebaseUserInterface()
	{
		DisplayName = FString("");
		Email = FString("");
		PhotoUrl = FString("");
		UserID = FString("");
		PhoneNumber = FString();
		Provider = EFirebaseProvider::Password;
	}
};

/** Metadata corresponding to a Firebase user */
USTRUCT(BlueprintType)
struct FFirebaseUserMetadata
{
	GENERATED_USTRUCT_BODY()

	/** The Firebase user creation UTC timestamp in milliseconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString CreationTimestamp;

	/** The last sign in UTC timestamp in milliseconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString LastSignInTimestamp;

	FFirebaseUserMetadata()
	{
		CreationTimestamp = FString("");
		LastSignInTimestamp = FString("");
	}
};

/** Firebase user account object */
USTRUCT(BlueprintType)
struct FFirebaseUser
{
	GENERATED_USTRUCT_BODY()

	/** Display name associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString DisplayName;

	/** Email associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString Email;

	/** Photo url associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString PhotoUrl;

	/** Unique Firebase user ID for the user */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString UserID;

	/** Gets the phone number for the user, in E.164 format. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString PhoneNumber;

	/** Provider ID for the user (For example, "Facebook") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	EFirebaseProvider Provider;

	/** Third party profile data associated with this user returned by the authentication server, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	TArray<FFirebaseUserInterface> ProviderData;

	/** Gets the metadata for this user account */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FFirebaseUserMetadata Metadata;
	
	/** True if user signed in anonymously */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	bool IsAnonymous;

	/** True if the email address associated with this user has been verified */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	bool IsEmailVerified;

	FFirebaseUser()
	{
		DisplayName = FString("");
		Email = FString("");
		PhotoUrl = FString("");
		UserID = FString("");
		PhoneNumber = FString();
		Provider = EFirebaseProvider::Password;
		ProviderData = TArray<FFirebaseUserInterface>();
		Metadata = FFirebaseUserMetadata();
		IsAnonymous = false;
		IsEmailVerified = false;
	}
};

/** Firebase user profile object */
USTRUCT(BlueprintType)
struct FFirebaseUserProfile
{
	GENERATED_USTRUCT_BODY()

	/** Display name associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString DisplayName;

	/** Photo url associated with the user, if any */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Mobile Kit|Authentication")
	FString PhotoUrl;

	FFirebaseUserProfile()
	{
		DisplayName = FString("");
		PhotoUrl = FString("");
	}
};


/** Called when Firebase Authentication module is initialized */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthInitializeCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user is created via email */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthCreateUserEmailCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user password reset is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthPasswordResetCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user verification email is sent */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthSendEmailVerificationCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase phone number is verified */
DECLARE_DELEGATE_FourParams(FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate, const bool, const EFirebaseAuthError&, const FString&, const UFirebaseCredential*);

/** Called when Firebase user is signed in anonymously */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthSignInAnonymousCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user is signed in via email */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthSignInEmailCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase retrieving user token is completed */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseAuthGetUserTokenCompleteDelegate, const bool, const EFirebaseAuthError&, const FString&);

/** Called when Firebase updating user email is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthUpdateEmailCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase updating user password is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthUpdatePasswordCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase updating user profile is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthUpdateUserProfileCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase deleting user is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthDeleteUserCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase reauthenticating user is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthReauthenticateUserCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase reloading user is completed */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthReloadUserCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase fetching providers for email is completed */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate, const bool, const EFirebaseAuthError&, const TArray<FString>&);

/** Called when Firebase user is signed in with 3rd party credential */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthSignInWithCredentialCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Google Sign-In completed successfully */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseAuthSignInWithGoogleCompleteDelegate, const bool, const FString&, const FString&);

/** Called when Firebase user is signed in with custom token */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user is linked with 3rd party credential */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthLinkWithCredentialCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase user is unlinked from the specified provider */
DECLARE_DELEGATE_TwoParams(FOnFirebaseAuthUnlinkCompleteDelegate, const bool, const EFirebaseAuthError&);

/** Called when Firebase retrieving Game Center Credential is completed */
DECLARE_DELEGATE_ThreeParams(FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate, const bool, const EFirebaseAuthError&, const UFirebaseCredential*);
