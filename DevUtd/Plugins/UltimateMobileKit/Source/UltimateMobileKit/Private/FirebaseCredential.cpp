// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "FirebaseCredential.h"

UFirebaseCredential::UFirebaseCredential(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Credential = EFirebaseProvider::Password;
}

UFirebaseCredential* UFirebaseCredential::EmailCredential(const FString& Email, const FString& Password)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::Password;
	UltimateMobileKitCredential->Email = Email;
	UltimateMobileKitCredential->Password = Password;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::FacebookCredential(const FString& AccessToken)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::Facebook;
	UltimateMobileKitCredential->AccessToken = AccessToken;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::GoogleCredential(const FString& IdToken, const FString& AccessToken)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::Google;
	UltimateMobileKitCredential->IdToken = IdToken;
	UltimateMobileKitCredential->AccessToken = AccessToken;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::GooglePlayGamesCredential(const FString& ServerAuthCode)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::GooglePlayGames;
	UltimateMobileKitCredential->ServerAuthCode = ServerAuthCode;;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::GitHubCredential(const FString& Token)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::GitHub;
	UltimateMobileKitCredential->Token = Token;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::TwitterCredential(const FString& Token, const FString& Secret)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = EFirebaseProvider::Twitter;
	UltimateMobileKitCredential->Token = Token;
	UltimateMobileKitCredential->Secret = Secret;

	return UltimateMobileKitCredential;
}

UFirebaseCredential* UFirebaseCredential::PhoneCredential(const FString& VerificationId, const FString& VerificationCode)
{
    UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
    UltimateMobileKitCredential->Credential = EFirebaseProvider::Phone;
    UltimateMobileKitCredential->VerificationId = VerificationId;
    UltimateMobileKitCredential->VerificationCode = VerificationCode;
    
    return UltimateMobileKitCredential;
}

const EFirebaseProvider UFirebaseCredential::GetType() const
{
	return Credential;
}

#if WITH_ULTIMATEMOBILEKIT && WITH_ULTIMATEMOBILEKIT_AUTHENTICATION
firebase::auth::Credential UFirebaseCredential::GetNativeCredential() const
{
	if (NativeCredential.IsValid())
	{
		return *NativeCredential.Get();
	}
	else if (Credential == EFirebaseProvider::Password)
	{
		return firebase::auth::EmailAuthProvider::GetCredential(TCHAR_TO_UTF8(*Email), TCHAR_TO_UTF8(*Password));
	}
	else if (Credential == EFirebaseProvider::Facebook)
	{
		return firebase::auth::FacebookAuthProvider::GetCredential(TCHAR_TO_UTF8(*AccessToken));
	}
	else if (Credential == EFirebaseProvider::Google)
	{
		return firebase::auth::GoogleAuthProvider::GetCredential(TCHAR_TO_UTF8(*IdToken), TCHAR_TO_UTF8(*AccessToken));
	}
	else if (Credential == EFirebaseProvider::GooglePlayGames)
	{
		return firebase::auth::PlayGamesAuthProvider::GetCredential(TCHAR_TO_UTF8(*ServerAuthCode));
	}
	else if (Credential == EFirebaseProvider::Twitter)
	{
		return firebase::auth::TwitterAuthProvider::GetCredential(TCHAR_TO_UTF8(*Token), TCHAR_TO_UTF8(*Secret));
	}
	else if (Credential == EFirebaseProvider::GitHub)
	{
		return firebase::auth::GitHubAuthProvider::GetCredential(TCHAR_TO_UTF8(*Token));
	}
	else if(Credential == EFirebaseProvider::Phone)
	{
		FUltimateMobileKit* UltimateMobileKit = FUltimateMobileKit::Get();
		if (UltimateMobileKit)
		{
			FFirebaseNativeAuthPtr NativeAuth = UltimateMobileKit->GetFirebaseAuth()->GetFirebaseNativeAuth();
			if (NativeAuth.IsValid())
			{
				firebase::auth::PhoneAuthProvider& PhoneProvider = firebase::auth::PhoneAuthProvider::GetInstance(NativeAuth.Get());
				return PhoneProvider.GetCredential(TCHAR_TO_UTF8(*VerificationId), TCHAR_TO_UTF8(*VerificationCode));
			}
		}
	}
	else if(Credential == EFirebaseProvider::GameCenter)
	{
		return *(NativeCredential.Get());
	}
		
	return firebase::auth::EmailAuthProvider::GetCredential(TCHAR_TO_UTF8(*Email), TCHAR_TO_UTF8(*Password));
}

UFirebaseCredential* UFirebaseCredential::MakeNativeCredential(firebase::auth::Credential Credential, const EFirebaseProvider& Type)
{
	UFirebaseCredential* UltimateMobileKitCredential = NewObject<UFirebaseCredential>();
	UltimateMobileKitCredential->Credential = Type;
	UltimateMobileKitCredential->NativeCredential = MakeShareable(new firebase::auth::Credential(Credential));

	return UltimateMobileKitCredential;
}

#endif

const EFirebaseProvider UFirebaseCredential::StringToProvider(const FString& Credential)
{
	if (Credential.Equals("password"))
	{
		return EFirebaseProvider::Password;
	}
	else if (Credential.Equals("facebook.com"))
	{
		return EFirebaseProvider::Facebook;
	}
	else if (Credential.Equals("google.com"))
	{
		return EFirebaseProvider::Google;
	}
	else if (Credential.Equals("playgames.google.com"))
	{
		return EFirebaseProvider::GooglePlayGames;
	}
	else if (Credential.Equals("github.com"))
	{
		return EFirebaseProvider::GitHub;
	}
	else if (Credential.Equals("twitter.com"))
	{
		return EFirebaseProvider::Twitter;
	}
	else if(Credential.Equals("phone"))
	{
		return EFirebaseProvider::Phone;
	}
	else if(Credential.Equals("gc.apple.com"))
	{
		return EFirebaseProvider::GameCenter;
	}
	else if(Credential.Equals("Firebase"))
	{
		return EFirebaseProvider::Firebase;
	}

	return EFirebaseProvider::Password;
}

const FString UFirebaseCredential::ProviderToString(const EFirebaseProvider Credential)
{
	switch (Credential)
	{
		case EFirebaseProvider::Password:
			return FString("password");
		case EFirebaseProvider::Facebook:
			return FString("facebook.com");
		case EFirebaseProvider::Google:
			return FString("google.com");
		case EFirebaseProvider::GooglePlayGames:
			return FString("playgames.google.com");
		case EFirebaseProvider::GitHub:
			return FString("github.com");
		case EFirebaseProvider::Twitter:
			return FString("twitter.com");
		case EFirebaseProvider::Phone:
			return FString("phone");
		case EFirebaseProvider::GameCenter:
			return FString("gc.apple.com");
		case EFirebaseProvider::Firebase:
			return FString("Firebase");
		default:
			return FString("password");
	}
}
