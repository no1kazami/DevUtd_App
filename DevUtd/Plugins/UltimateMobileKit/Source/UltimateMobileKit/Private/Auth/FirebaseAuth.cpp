// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "Auth/FirebaseAuth.h"
#include "UltimateMobileKit.h"

#include "Auth/AuthInitialize.h"
#include "Auth/AuthCreateUserEmail.h"
#include "Auth/AuthPasswordReset.h"
#include "Auth/AuthSignInAnonymous.h"
#include "Auth/AuthSignInEmail.h"
#include "Auth/AuthDeleteUser.h"
#include "Auth/AuthGetUserToken.h"
#include "Auth/AuthReauthenticateUser.h"
#include "Auth/AuthReloadUser.h"
#include "Auth/AuthSendEmailVerification.h"
#include "Auth/AuthVerifyPhoneNumber.h"
#include "Auth/AuthUpdateEmail.h"
#include "Auth/AuthUpdatePassword.h"
#include "Auth/AuthUpdateUserProfile.h"
#include "Auth/AuthFetchProvidersForEmail.h"
#include "Auth/AuthLinkWithCredential.h"
#include "Auth/AuthSignInWithCredential.h"
#include "Auth/AuthSignInWithGoogle.h"
#include "Auth/AuthSignInWithCustomToken.h"
#include "Auth/AuthUnlink.h"
#include "Auth/AuthGetGameCenterCredential.h"
#include "UltimateMobileKitComponent.h"

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
#include "firebase/auth/user.h"
#endif

FFirebaseAuth::FFirebaseAuth()
{
}

FFirebaseAuth::~FFirebaseAuth()
{
}

void FFirebaseAuth::Init(const FOnFirebaseAuthInitializeCompleteDelegate& Delegate /*= FOnFirebaseAuthInitializeCompleteDelegate()*/)
{
	if (IsInitialized())
	{
		Delegate.ExecuteIfBound(true, EFirebaseAuthError::None);
		return;
	}

	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		auto QueryTask = new FFirebaseAuthInitialize(UltimateMobileKit->Get(), Delegate);
		UltimateMobileKit->QueueAsyncTask(QueryTask);

		return;
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::Shutdown()
{
	UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Authentication Shutdown"));

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	if (FirebaseNativeAuthPtr.IsValid())
	{
		FirebaseNativeAuthPtr->RemoveAuthStateListener(this);
	}
#endif
}

const bool FFirebaseAuth::IsInitialized() const
{
	return bInitialized;
}

void FFirebaseAuth::SetInitialized(const bool Initialized)
{
	bInitialized = Initialized;

	if (bInitialized)
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Authentication is initialized successfully"));
	}
	else
	{
		UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Authentication is not initialized"));
	}
}

const bool FFirebaseAuth::RegisterService()
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
	if (UltimateMobileKit)
	{
		FirebaseNativeAuthPtr = MakeShareable(firebase::auth::Auth::GetAuth(UltimateMobileKit->GetFirebaseApp()->GetFirebaseNativeApp().Get()));

		if (FirebaseNativeAuthPtr.IsValid())
		{
			FirebaseNativeAuthPtr->AddAuthStateListener(this);

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase Native Authentication service registered"));

			return true;
		}
	}
#endif

	return false;
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
void FFirebaseAuth::OnAuthStateChanged(firebase::auth::Auth* auth)
{
	firebase::auth::User* user = auth->current_user();

	// User Is Signed In
	if (user != nullptr) 
	{
		UUltimateMobileKitComponent::UserSignedInDelegate.Broadcast(TransformNativeToUnrealUser(user));
	}
	// User Is Signed Out
	else 
	{
		UUltimateMobileKitComponent::UserSignedOutDelegate.Broadcast();
	}
}

void FFirebaseAuth::OnIdTokenChanged(firebase::auth::Auth* auth)
{
	firebase::auth::User* user = auth->current_user();

	if (user != nullptr)
	{
		UUltimateMobileKitComponent::UserIdTokenChangedDelegate.Broadcast(TransformNativeToUnrealUser(user));
	}
}
#endif

void FFirebaseAuth::CreateUserWithEmailAndPassword(const FString& Email, const FString& Password, const FOnFirebaseAuthCreateUserEmailCompleteDelegate& Delegate /*= FOnFirebaseAuthCreateUserEmailCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthCreateUserEmail(UltimateMobileKit->Get(), Delegate, Email, Password);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::SignInWithEmailAndPassword(const FString& Email, const FString& Password, const FOnFirebaseAuthSignInEmailCompleteDelegate& Delegate /*= FOnFirebaseAuthSignInEmailCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSignInEmail(UltimateMobileKit->Get(), Delegate, Email, Password);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::SignInAnonymously(const FOnFirebaseAuthSignInAnonymousCompleteDelegate& Delegate /*= FOnFirebaseAuthSignInAnonymousCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSignInAnonymous(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::SendPasswordResetEmail(const FString& Email, const FOnFirebaseAuthPasswordResetCompleteDelegate& Delegate /*= FOnFirebaseAuthPasswordResetCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthPasswordReset(UltimateMobileKit->Get(), Delegate, Email);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::SignOut() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	if (IsInitialized())
	{
		if (FirebaseNativeAuthPtr.IsValid())
		{
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase User Sign Out"));

			FirebaseNativeAuthPtr->SignOut();
		}
	}
#endif
}

void FFirebaseAuth::SendEmailVerification(const FOnFirebaseAuthSendEmailVerificationCompleteDelegate& Delegate /*= FOnFirebaseAuthSendEmailVerificationCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSendEmailVerification(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::VerifyPhoneNumber(const FString& PhoneNumber, const FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate& Delegate /*= FOnFirebaseAuthVerifyPhoneNumberCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthVerifyPhoneNumber(UltimateMobileKit->Get(), Delegate, PhoneNumber);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable, FString(), nullptr);
}

void FFirebaseAuth::GetUserToken(const FOnFirebaseAuthGetUserTokenCompleteDelegate& Delegate /*= FOnFirebaseAuthGetUserTokenCompleteDelegate()*/, bool ForceRefresh /*= false*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthGetUserToken(UltimateMobileKit->Get(), Delegate, ForceRefresh);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable, FString());
}

bool FFirebaseAuth::IsUserLoggedIn() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	if (IsInitialized() && FirebaseNativeAuthPtr.IsValid())
	{
		firebase::auth::User* user = FirebaseNativeAuthPtr->current_user();
		bool bUserIsLoggedIn = user != nullptr;

		if (bUserIsLoggedIn)
		{
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase User Is Logged In"));
		}
		else
		{
			UE_LOG(LogUltimateMobileKit, Display, TEXT("Firebase User Is Not Logged In"));
		}

		return bUserIsLoggedIn;
	}
	else
	{
		return false;
	}
#endif

	return false;
}

const FFirebaseUser FFirebaseAuth::GetLoggedUser() const
{
#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
	if (IsInitialized() && FirebaseNativeAuthPtr.IsValid())
	{
		firebase::auth::User* user = FirebaseNativeAuthPtr->current_user();
		if (user != nullptr)
		{
			FFirebaseUser FirebaseUser = FFirebaseUser(TransformNativeToUnrealUser(user));

			UE_LOG(LogUltimateMobileKit, Display, TEXT("Retrieve Firebase User. Display name: %s, Email: %s, IsAnonymous: %d, IsEmailVerified: %d, PhotoUrl: %s, Provider: %s, User ID: %s"), *FirebaseUser.DisplayName, *FirebaseUser.Email, FirebaseUser.IsAnonymous, FirebaseUser.IsEmailVerified, *FirebaseUser.PhotoUrl, *UFirebaseCredential::ProviderToString(FirebaseUser.Provider), *FirebaseUser.UserID);

			return FirebaseUser;
		}
	}
#endif

	return FFirebaseUser();
}

void FFirebaseAuth::UpdateEmail(const FString& Email, const FOnFirebaseAuthUpdateEmailCompleteDelegate& Delegate /*= FOnFirebaseAuthUpdateEmailCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthUpdateEmail(UltimateMobileKit->Get(), Delegate, Email);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::UpdatePassword(const FString& Password, const FOnFirebaseAuthUpdatePasswordCompleteDelegate& Delegate /*= FOnFirebaseAuthUpdatePasswordCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthUpdatePassword(UltimateMobileKit->Get(), Delegate, Password);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::UpdateUserProfile(const FFirebaseUserProfile UserProfile, const FOnFirebaseAuthUpdateUserProfileCompleteDelegate& Delegate /*= FOnFirebaseAuthUpdateUserProfileCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthUpdateUserProfile(UltimateMobileKit->Get(), Delegate, UserProfile);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::DeleteUser(const FOnFirebaseAuthDeleteUserCompleteDelegate& Delegate /*= FOnFirebaseAuthDeleteUserCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthDeleteUser(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::ReauthenticateUser(const UFirebaseCredential* Credential, const FOnFirebaseAuthReauthenticateUserCompleteDelegate& Delegate /*= FOnFirebaseAuthReauthenticateUserCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthReauthenticateUser(UltimateMobileKit->Get(), Delegate, Credential);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::ReloadUser(const FOnFirebaseAuthReloadUserCompleteDelegate& Delegate /*= FOnFirebaseReloadUserCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthReloadUser(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
const FFirebaseUser FFirebaseAuth::TransformNativeToUnrealUser(firebase::auth::User* NativeUser) const
{
	FFirebaseUser FirebaseUser;

	if (NativeUser != nullptr)
	{
		FirebaseUser.DisplayName = FString(NativeUser->display_name().c_str());
		FirebaseUser.Email = FString(NativeUser->email().c_str());
		FirebaseUser.PhotoUrl = FString(NativeUser->photo_url().c_str());
		FirebaseUser.UserID = FString(NativeUser->uid().c_str());
		FirebaseUser.PhoneNumber = FString(NativeUser->phone_number().c_str());
		FirebaseUser.Provider = UFirebaseCredential::StringToProvider(NativeUser->provider_id().c_str());
		FirebaseUser.IsAnonymous = NativeUser->is_anonymous();
		FirebaseUser.IsEmailVerified = NativeUser->is_email_verified();
		FirebaseUser.ProviderData = TArray<FFirebaseUserInterface>();

		std::vector<firebase::auth::UserInfoInterface*> ProvidersData = NativeUser->provider_data();

		for (int i = 0; i < ProvidersData.size(); i++)
		{
			FFirebaseUserInterface UserInterface;
			UserInterface.DisplayName = FString(ProvidersData.at(i)->display_name().c_str());
			UserInterface.Email = FString(ProvidersData.at(i)->email().c_str());
			UserInterface.PhotoUrl = FString(ProvidersData.at(i)->photo_url().c_str());
			UserInterface.UserID = FString(ProvidersData.at(i)->uid().c_str());
			UserInterface.PhoneNumber = FString(ProvidersData.at(i)->phone_number().c_str());
			UserInterface.Provider = UFirebaseCredential::StringToProvider(FString(ProvidersData.at(i)->provider_id().c_str()));

			FirebaseUser.ProviderData.Add(UserInterface);
		}

		FFirebaseUserMetadata FirebaseUserMetadata;
		FirebaseUserMetadata.CreationTimestamp = FString::Printf(TEXT("%lld"), NativeUser->metadata().creation_timestamp);
		FirebaseUserMetadata.LastSignInTimestamp = FString::Printf(TEXT("%lld"), NativeUser->metadata().last_sign_in_timestamp);
		FirebaseUser.Metadata = FirebaseUserMetadata;
	}

	return FirebaseUser;
}


const EFirebaseAuthError FFirebaseAuth::FirebaseErrorFromNative(const firebase::auth::AuthError& NativeError)
{
	switch (NativeError)
	{
	case firebase::auth::AuthError::kAuthErrorNone:
		return EFirebaseAuthError::None;
	case firebase::auth::AuthError::kAuthErrorAccountExistsWithDifferentCredentials:
		return EFirebaseAuthError::AccountExistsWithDifferentCredentials;
	case firebase::auth::AuthError::kAuthErrorApiNotAvailable:
		return EFirebaseAuthError::ApiNotAvailable;
	case firebase::auth::AuthError::kAuthErrorAppNotAuthorized:
		return EFirebaseAuthError::AppNotAuthorized;
	case firebase::auth::AuthError::kAuthErrorAppNotVerified:
		return EFirebaseAuthError::AppNotVerified;
	case firebase::auth::AuthError::kAuthErrorAppVerificationFailed:
		return EFirebaseAuthError::AppVerificationFailed;
	case firebase::auth::AuthError::kAuthErrorCaptchaCheckFailed:
		return EFirebaseAuthError::CaptchaCheckFailed;
	case firebase::auth::AuthError::kAuthErrorCredentialAlreadyInUse:
		return EFirebaseAuthError::CredentialAlreadyInUse;
	case firebase::auth::AuthError::kAuthErrorCustomTokenMismatch:
		return EFirebaseAuthError::CustomTokenMismatch;
	case firebase::auth::AuthError::kAuthErrorEmailAlreadyInUse:
		return EFirebaseAuthError::EmailAlreadyInUse;
	case firebase::auth::AuthError::kAuthErrorExpiredActionCode:
		return EFirebaseAuthError::ExpiredActionCode;
	case firebase::auth::AuthError::kAuthErrorFailure:
		return EFirebaseAuthError::Failure;
	case firebase::auth::AuthError::kAuthErrorInvalidActionCode:
		return EFirebaseAuthError::InvalidActionCode;
	case firebase::auth::AuthError::kAuthErrorInvalidApiKey:
		return EFirebaseAuthError::InvalidApiKey;
	case firebase::auth::AuthError::kAuthErrorInvalidAppCredential:
		return EFirebaseAuthError::InvalidAppCredential;
	case firebase::auth::AuthError::kAuthErrorInvalidClientId:
		return EFirebaseAuthError::InvalidClientId;
	case firebase::auth::AuthError::kAuthErrorInvalidContinueUri:
		return EFirebaseAuthError::InvalidContinueUri;
	case firebase::auth::AuthError::kAuthErrorInvalidCredential:
		return EFirebaseAuthError::InvalidCredential;
	case firebase::auth::AuthError::kAuthErrorInvalidCustomToken:
		return EFirebaseAuthError::InvalidCustomToken;
	case firebase::auth::AuthError::kAuthErrorInvalidEmail:
		return EFirebaseAuthError::InvalidEmail;
	case firebase::auth::AuthError::kAuthErrorInvalidMessagePayload:
		return EFirebaseAuthError::InvalidMessagePayload;
	case firebase::auth::AuthError::kAuthErrorInvalidPhoneNumber:
		return EFirebaseAuthError::InvalidPhoneNumber;
	case firebase::auth::AuthError::kAuthErrorInvalidRecipientEmail:
		return EFirebaseAuthError::InvalidRecipientEmail;
	case firebase::auth::AuthError::kAuthErrorInvalidSender:
		return EFirebaseAuthError::InvalidSender;
	case firebase::auth::AuthError::kAuthErrorInvalidUserToken:
		return EFirebaseAuthError::InvalidUserToken;
	case firebase::auth::AuthError::kAuthErrorInvalidVerificationCode:
		return EFirebaseAuthError::InvalidVerificationCode;
	case firebase::auth::AuthError::kAuthErrorInvalidVerificationId:
		return EFirebaseAuthError::InvalidVerificationId;
	case firebase::auth::AuthError::kAuthErrorKeychainError:
		return EFirebaseAuthError::KeychainError;
	case firebase::auth::AuthError::kAuthErrorMissingAppCredential:
		return EFirebaseAuthError::MissingAppCredential;
	case firebase::auth::AuthError::kAuthErrorMissingAppToken:
		return EFirebaseAuthError::MissingAppToken;
	case firebase::auth::AuthError::kAuthErrorMissingContinueUri:
		return EFirebaseAuthError::MissingContinueUri;
	case firebase::auth::AuthError::kAuthErrorMissingEmail:
		return EFirebaseAuthError::MissingEmail;
	case firebase::auth::AuthError::kAuthErrorMissingIosBundleId:
		return EFirebaseAuthError::MissingIosBundleId;
	case firebase::auth::AuthError::kAuthErrorMissingPassword:
		return EFirebaseAuthError::MissingPassword;
	case firebase::auth::AuthError::kAuthErrorMissingPhoneNumber:
		return EFirebaseAuthError::MissingPhoneNumber;
	case firebase::auth::AuthError::kAuthErrorMissingVerificationCode:
		return EFirebaseAuthError::MissingVerificationCode;
	case firebase::auth::AuthError::kAuthErrorMissingVerificationId:
		return EFirebaseAuthError::MissingVerificationId;
	case firebase::auth::AuthError::kAuthErrorNetworkRequestFailed:
		return EFirebaseAuthError::NetworkRequestFailed;
	case firebase::auth::AuthError::kAuthErrorNoSignedInUser:
		return EFirebaseAuthError::NoSignedInUser;
	case firebase::auth::AuthError::kAuthErrorNoSuchProvider:
		return EFirebaseAuthError::NoSuchProvider;
	case firebase::auth::AuthError::kAuthErrorNotificationNotForwarded:
		return EFirebaseAuthError::NotificationNotForwarded;
	case firebase::auth::AuthError::kAuthErrorOperationNotAllowed:
		return EFirebaseAuthError::OperationNotAllowed;
	case firebase::auth::AuthError::kAuthErrorProviderAlreadyLinked:
		return EFirebaseAuthError::ProviderAlreadyLinked;
	case firebase::auth::AuthError::kAuthErrorQuotaExceeded:
		return EFirebaseAuthError::QuotaExceeded;
	case firebase::auth::AuthError::kAuthErrorRequiresRecentLogin:
		return EFirebaseAuthError::RequiresRecentLogin;
	case firebase::auth::AuthError::kAuthErrorRetryPhoneAuth:
		return EFirebaseAuthError::RetryPhoneAuth;
	case firebase::auth::AuthError::kAuthErrorSessionExpired:
		return EFirebaseAuthError::SessionExpired;
	case firebase::auth::AuthError::kAuthErrorTooManyRequests:
		return EFirebaseAuthError::TooManyRequests;
	case firebase::auth::AuthError::kAuthErrorUnauthorizedDomain:
		return EFirebaseAuthError::UnauthorizedDomain;
	case firebase::auth::AuthError::kAuthErrorUnimplemented:
		return EFirebaseAuthError::Unimplemented;
	case firebase::auth::AuthError::kAuthErrorUserDisabled:
		return EFirebaseAuthError::UserDisabled;
	case firebase::auth::AuthError::kAuthErrorUserMismatch:
		return EFirebaseAuthError::UserMismatch;
	case firebase::auth::AuthError::kAuthErrorUserNotFound:
		return EFirebaseAuthError::UserNotFound;
	case firebase::auth::AuthError::kAuthErrorUserTokenExpired:
		return EFirebaseAuthError::UserTokenExpired;
	case firebase::auth::AuthError::kAuthErrorWeakPassword:
		return EFirebaseAuthError::WeakPassword;
	case firebase::auth::AuthError::kAuthErrorWebContextAlreadyPresented:
		return EFirebaseAuthError::WebContextAlreadyPresented;
	case firebase::auth::AuthError::kAuthErrorWebContextCancelled:
		return EFirebaseAuthError::WebContextCancelled;
	case firebase::auth::AuthError::kAuthErrorWrongPassword:
		return EFirebaseAuthError::WrongPassword;
	case firebase::auth::AuthError::kAuthErrorDynamicLinkNotActivated:
		return EFirebaseAuthError::DynamicLinkNotActivated;
	case firebase::auth::AuthError::kAuthErrorCancelled:
		return EFirebaseAuthError::Cancelled;
	case firebase::auth::AuthError::kAuthErrorInvalidProviderId:
		return EFirebaseAuthError::InvalidProviderId;
	case firebase::auth::AuthError::kAuthErrorWebInternalError:
		return EFirebaseAuthError::WebInternalError;
	case firebase::auth::AuthError::kAuthErrorWebStorateUnsupported:
		return EFirebaseAuthError::WebStorateUnsupported;
	case firebase::auth::AuthError::kAuthErrorTenantIdMismatch:
		return EFirebaseAuthError::TenantIdMismatch;
	case firebase::auth::AuthError::kAuthErrorUnsupportedTenantOperation:
		return EFirebaseAuthError::UnsupportedTenantOperation;
	case firebase::auth::AuthError::kAuthErrorInvalidLinkDomain:
		return EFirebaseAuthError::InvalidLinkDomain;
	case firebase::auth::AuthError::kAuthErrorRejectedCredential:
		return EFirebaseAuthError::RejectedCredential;
	default:
		return EFirebaseAuthError::None;
	}
}
#endif

void FFirebaseAuth::FetchProvidersForEmail(const FString& Email, const FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate& Delegate /*= FOnFirebaseAuthFetchProvidersForEmailCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthFetchProvidersForEmail(UltimateMobileKit->Get(), Delegate, Email);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable, TArray<FString>());
}

void FFirebaseAuth::SignInWithCredential(const UFirebaseCredential* Credential, const FOnFirebaseAuthSignInWithCredentialCompleteDelegate& Delegate /*= FOnFirebaseAuthSignInWithCredentialCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSignInWithCredential(UltimateMobileKit->Get(), Delegate, Credential);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::SignInWithGoogle(const FOnFirebaseAuthSignInWithGoogleCompleteDelegate& Delegate /*= FOnFirebaseAuthSignInWithGoogleCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSignInWithGoogle(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, FString(), FString());
}

void FFirebaseAuth::SignInWithCustomToken(const FString& Token, const FOnFirebaseAuthSignInWithCustomTokenCompleteDelegate& Delegate /*= FOnFirebaseSignInWithCustomTokenCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthSignInWithCustomToken(UltimateMobileKit->Get(), Delegate, Token);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::LinkWithCredential(const UFirebaseCredential* Credential, const FOnFirebaseAuthLinkWithCredentialCompleteDelegate& Delegate /*= FOnFirebaseAuthLinkWithCredentialCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthLinkWithCredential(UltimateMobileKit->Get(), Delegate, Credential);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::Unlink(const EFirebaseProvider Provider, const FOnFirebaseAuthUnlinkCompleteDelegate& Delegate /*= FOnFirebaseAuthUnlinkCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthUnlink(UltimateMobileKit->Get(), Delegate, Provider);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable);
}

void FFirebaseAuth::GetGameCenterCredential(const FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate& Delegate /*= FOnFirebaseAuthGetGameCenterCredentialCompleteDelegate()*/) const
{
	if (IsInitialized())
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			auto QueryTask = new FFirebaseAuthGetGameCenterCredential(UltimateMobileKit->Get(), Delegate);
			UltimateMobileKit->QueueAsyncTask(QueryTask);

			return;
		}
	}

	Delegate.ExecuteIfBound(false, EFirebaseAuthError::ApiNotAvailable, nullptr);
}
