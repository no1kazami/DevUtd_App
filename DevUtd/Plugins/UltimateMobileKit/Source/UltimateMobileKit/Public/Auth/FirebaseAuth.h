// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#pragma once

#include "Delegates/FirebaseAuthDelegates.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/auth.h"
#endif

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
typedef TSharedPtr<firebase::auth::Auth, ESPMode::ThreadSafe> FFirebaseNativeAuthPtr;
#endif

/** Firebase Authentication provides backend services to securely authenticate users. It can authenticate users using passwords and federated identity provider credentials, and it can integrate with a custom auth backend. */
class ULTIMATEMOBILEKIT_API FFirebaseAuth
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	: firebase::auth::AuthStateListener
	, firebase::auth::IdTokenListener
#endif
{
public:
	FFirebaseAuth();
	virtual ~FFirebaseAuth();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	inline FFirebaseNativeAuthPtr GetFirebaseNativeAuth()
	{
		return FirebaseNativeAuthPtr;
	}
#endif

	/** Initialize the Firebase Authentication API  */
	void Init(const FOnFirebaseAuthInitializeCompleteDelegate& Delegate = FOnFirebaseAuthInitializeCompleteDelegate());

	/** Shutdown the Firebase Analytics API  */
	void Shutdown();

	/** Check if Firebase Authentication is initialized */
	const bool IsInitialized() const;

	/** Set Firebase Authentication initialization state */
	void SetInitialized(const bool Initialized);

	/** Register Firebase Authentication services */
	const bool RegisterService();

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	/** Listener called when there is a change in the authentication state */
	virtual void OnAuthStateChanged(firebase::auth::Auth* Auth);

	/** Listener called when there is a change in the current user's token. */
	virtual void OnIdTokenChanged(firebase::auth::Auth* Auth);
#endif

	/** Creates, and on success, logs in a user with the given email address and password */
	void CreateUserWithEmailAndPassword(const FString& Email, const FString& Password, const FOnFirebaseAuthCreateUserEmailCompleteDelegate& Delegate = FOnFirebaseAuthCreateUserEmailCompleteDelegate()) const;

	/** Signs in using provided email address and password */
	void SignInWithEmailAndPassword(const FString& Email, const FString& Password, const FOnFirebaseAuthSignInEmailCompleteDelegate& Delegate = FOnFirebaseAuthSignInEmailCompleteDelegate()) const;

	/**
	* Asynchronously creates and becomes an anonymous user.
	* If there is already an anonymous user signed in, that user will be returned instead. If there is any other existing user, that user will be signed out.
	*/
	void SignInAnonymously(const FOnFirebaseAuthSignInAnonymousCompleteDelegate& Delegate = FOnFirebaseAuthSignInAnonymousCompleteDelegate()) const;

	/** Initiates a password reset for the given email address */
	void SendPasswordResetEmail(const FString& Email, const FOnFirebaseAuthPasswordResetCompleteDelegate& Delegate = FOnFirebaseAuthPasswordResetCompleteDelegate()) const;

	/** Removes any existing authentication credentials from this client */
	void SignOut() const;

	/** Initiates email verification for the user */
	void SendEmailVerification(const FOnFirebaseAuthSendEmailVerificationCompleteDelegate& Delegate = FOnFirebaseAuthSendEmailVerificationCompleteDelegate()) const;

	/** Start the phone number authentication operation. */
	void VerifyPhoneNumber(const FString& PhoneNumber, const FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate& Delegate = FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate()) const;

	/** The Java Web Token (JWT) that can be used to identify the user to the backend */
	void GetUserToken(const FOnFirebaseAuthGetUserTokenCompleteDelegate& Delegate = FOnFirebaseAuthGetUserTokenCompleteDelegate(), bool ForceRefresh = false) const;

	/** Check if User is logged in */
	bool IsUserLoggedIn() const;

	/** Synchronously gets the cached current user, or nullptr if there is none */
	const FFirebaseUser GetLoggedUser() const;

	/** Sets the email address for the user */
	void UpdateEmail(const FString& Email, const FOnFirebaseAuthUpdateEmailCompleteDelegate& Delegate = FOnFirebaseAuthUpdateEmailCompleteDelegate()) const;

	/*
	* Attempts to change the password for the current user.
	* For an account linked to an Identity Provider (IDP) with no password, this will result in the account becoming an email/password-based account while maintaining the IDP link. May fail if the password is invalid, if there is a conflicting email/password-based account, or if the token has expired. To retrieve fresh tokens, call Reauthenticate.
	*/
	void UpdatePassword(const FString& Password, const FOnFirebaseAuthUpdatePasswordCompleteDelegate& Delegate = FOnFirebaseAuthUpdatePasswordCompleteDelegate()) const;

	/** Updates a subset of user profile information */
	void UpdateUserProfile(const FFirebaseUserProfile UserProfile, const FOnFirebaseAuthUpdateUserProfileCompleteDelegate& Delegate = FOnFirebaseAuthUpdateUserProfileCompleteDelegate()) const;

	/** Deletes the user account */
	void DeleteUser(const FOnFirebaseAuthDeleteUserCompleteDelegate& Delegate = FOnFirebaseAuthDeleteUserCompleteDelegate()) const;

	/** Reauthenticate using a credential */
	void ReauthenticateUser(const UFirebaseCredential* Credential, const FOnFirebaseAuthReauthenticateUserCompleteDelegate& Delegate = FOnFirebaseAuthReauthenticateUserCompleteDelegate()) const;

	/** Refreshes the data for this user */
	void ReloadUser(const FOnFirebaseAuthReloadUserCompleteDelegate& Delegate = FOnFirebaseAuthReloadUserCompleteDelegate()) const;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	/** Transform Native To Unreal User */
	const FFirebaseUser TransformNativeToUnrealUser(firebase::auth::User* NativeUser) const;

	/** Convert Native Firebase Auth Error to Unreal Firebase Error */
	static const EFirebaseAuthError FirebaseErrorFromNative(const firebase::auth::AuthError& NativeError);
#endif

	/** Asynchronously requests the IDPs (identity providers) that can be used for the given email address */
	void FetchProvidersForEmail(const FString& Email, const FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate& Delegate = FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate()) const;

	/** Asynchronously logs into Firebase with the given credentials */
	void SignInWithCredential(const UFirebaseCredential* Credential, const FOnFirebaseAuthSignInWithCredentialCompleteDelegate& Delegate = FOnFirebaseAuthSignInWithCredentialCompleteDelegate()) const;

	/** Asynchronously logs into Google and Google Play system */
	void SignInWithGoogle(const FOnFirebaseAuthSignInWithGoogleCompleteDelegate& Delegate = FOnFirebaseAuthSignInWithGoogleCompleteDelegate()) const;

	/** Asynchronously logs into Firebase with the given Auth token */
	void SignInWithCustomToken(const FString& Token, const FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate& Delegate = FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate()) const;

	/**
	* Links the user with the given 3rd party credentials.
	* For example, a Facebook login access token, a Twitter token/token-secret pair. Status will be an error if the token is invalid, expired, or otherwise not accepted by the server as well as if the given 3rd party user id is already linked with another user account or if the current user is already linked with another id from the same provider.
	*/
	void LinkWithCredential(const UFirebaseCredential* Credential, const FOnFirebaseAuthLinkWithCredentialCompleteDelegate& Delegate = FOnFirebaseAuthLinkWithCredentialCompleteDelegate()) const;

	/** Unlinks the current user from the provider specified */
	void Unlink(const EFirebaseProvider Provider, const FOnFirebaseAuthUnlinkCompleteDelegate& Delegate = FOnFirebaseAuthUnlinkCompleteDelegate()) const;

	/** Retrieves Game Center Credential for Game Center Sign In */
	void GetGameCenterCredential(const FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate& Delegate = FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate()) const;

private:
	bool bInitialized = false;

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FFirebaseNativeAuthPtr FirebaseNativeAuthPtr;
#endif
};
