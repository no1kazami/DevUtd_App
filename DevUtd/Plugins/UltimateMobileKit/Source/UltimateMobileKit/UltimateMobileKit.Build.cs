// Ultimate Mobile Kit
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

using System;
using System.IO;
using System.Collections.Generic;
using Tools.DotNETCommon;

namespace UnrealBuildTool.Rules
{
	public class UltimateMobileKit : ModuleRules
	{
		public UltimateMobileKit(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            PrecompileForTargets = PrecompileTargetsType.Any;

            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem", "OnlineSubsystemUtils", "Bigtamin" });
			PrivateIncludePaths.Add("UltimateMobileKit/Private");
			PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });

            // Get Project Path
            string ProjectPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../"));
            if (Target.ProjectFile != null)
            {
                ProjectPath = Path.GetDirectoryName(Target.ProjectFile.ToString());
            }

            // Get Settings from Config Cache
            var Ini = UnrealBuildTool.ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, new DirectoryReference(ProjectPath), Target.Platform);

			// Paths
			string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty");
			string ThirdPartyIOSPath = Path.Combine(ThirdPartyPath, "IOS");
			string ThirdPartyUniversalPath = Path.Combine(ThirdPartyPath, "Universal", "firebase_cpp_sdk");
            string ThirdPartyUniversalIncludePath = Path.Combine(ThirdPartyUniversalPath, "include");
			
            // Include
            PublicIncludePaths.Add(ThirdPartyUniversalIncludePath);

            // Modules
            bool bEnableAnalytics = false;
			bool bEnableAuthentication = false;
			bool bEnableRemoteConfig = false;
			bool bEnableCrashlytics = false;
            bool bEnableInAppMessaging = false;
            bool bEnableInstanceId = false;
            bool bEnableLinksInvites = false;
			bool bEnableCloudMessaging = false;
			bool bEnablePerformanceMonitoring = false;
			bool bEnableStorage = false;
            bool bEnableTestLab = false;
			bool bEnableDataBase_CKH = false;

			string SettingsPath = "/Script/UltimateMobileKit.UltimateMobileKitSettings";
			if (!Ini.GetBool(SettingsPath, "bEnableAnalytics", out bEnableAnalytics))
				bEnableAnalytics = false;
			if (!Ini.GetBool(SettingsPath, "bEnableAuthentication", out bEnableAuthentication))
				bEnableAuthentication = false;
			if (!Ini.GetBool(SettingsPath, "bEnableRemoteConfig", out bEnableRemoteConfig))
				bEnableRemoteConfig = false;
			if (!Ini.GetBool(SettingsPath, "bEnableCrashlytics", out bEnableCrashlytics))
				bEnableCrashlytics = false;
            if (!Ini.GetBool(SettingsPath, "bEnableInAppMessaging", out bEnableInAppMessaging))
                bEnableInAppMessaging = false;
            if (!Ini.GetBool(SettingsPath, "bEnableInstanceId", out bEnableInstanceId))
                bEnableInstanceId = false;
            if (!Ini.GetBool(SettingsPath, "bEnableLinksInvites", out bEnableLinksInvites))
				bEnableLinksInvites = false;
			if (!Ini.GetBool(SettingsPath, "bEnableCloudMessaging", out bEnableCloudMessaging))
				bEnableCloudMessaging = false;
			if (!Ini.GetBool(SettingsPath, "bEnablePerformanceMonitoring", out bEnablePerformanceMonitoring))
				bEnablePerformanceMonitoring = false;
			if (!Ini.GetBool(SettingsPath, "bEnableStorage", out bEnableStorage))
				bEnableStorage = false;
            if (!Ini.GetBool(SettingsPath, "bEnableTestLab", out bEnableTestLab))
                bEnableTestLab = false;
            if (!Ini.GetBool(SettingsPath, "bEnableDataBase_CKH", out bEnableDataBase_CKH))
				bEnableDataBase_CKH = false;

            if (bEnableAnalytics)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_ANALYTICS=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_ANALYTICS=0");
			}

			if (bEnableAuthentication)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_AUTHENTICATION=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_AUTHENTICATION=0");
			}

			if (bEnableRemoteConfig)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_REMOTECONFIG=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_REMOTECONFIG=0");
			}

			if (bEnableCrashlytics)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_CRASHLYTICS=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_CRASHLYTICS=0");
			}

            if (bEnableInAppMessaging)
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING=1");
            }
            else
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_INAPPMESSAGING=0");
            }

            if (bEnableInstanceId)
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_INSTANCEID=1");
            }
            else
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_INSTANCEID=0");
            }

            if (bEnableLinksInvites)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_LINKSINVITES=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_LINKSINVITES=0");
			}

			if (bEnableCloudMessaging)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_CLOUDMESSAGING=0");
			}

			if (bEnablePerformanceMonitoring)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_PERFORMANCEMONITORING=0");
			}

			if (bEnableStorage)
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_STORAGE=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_STORAGE=0");
			}

            if (bEnableTestLab)
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_TESTLAB=1");
            }
            else
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_TESTLAB=0");
            }

            if (bEnableDataBase_CKH)
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_DATABASE_CKH=1");
            }
            else
            {
                PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT_DATABASE_CKH=0");
            }

            // IOS
            if (Target.Platform == UnrealTargetPlatform.IOS)
			{
				// SDKs checks
				bool bHasGoogleSDK = (Directory.Exists(ThirdPartyPath) &&
									  Directory.Exists(ThirdPartyIOSPath) &&
									  Directory.Exists(ThirdPartyUniversalPath) &&
									  File.Exists(Path.Combine(ThirdPartyIOSPath, "FirebaseCore.embeddedframework.zip")));

				// GoogleServicesPlist
				string GoogleServicesPlistPath = Path.Combine(ProjectPath, "Build", "IOS", "Firebase", "GoogleServicesPlist.embeddedframework.zip");
				string GoogleServicesPlistIntermediatePath = Path.Combine(ModuleDirectory, "..", "..", "Intermediate", "Firebase", "IOS", "GoogleServicesPlist.embeddedframework.zip");

				if (bHasGoogleSDK)
				{
					if (File.Exists(GoogleServicesPlistPath))
					{
						Directory.CreateDirectory(Path.GetDirectoryName(GoogleServicesPlistIntermediatePath));
						File.Copy(GoogleServicesPlistPath, GoogleServicesPlistIntermediatePath, true);

						PublicAdditionalFrameworks.Add(
						new Framework(
							   "GoogleServicesPlist",
							   "../../Intermediate/Firebase/IOS/GoogleServicesPlist.embeddedframework.zip",
							   "GoogleService-Info.plist"
							)
						);
					}
					else
					{
						Console.WriteLine("GoogleServicesPlist.embeddedframework.zip not found!");
						bHasGoogleSDK = false;
					}
				}
                
                if (bHasGoogleSDK)
                {
                    PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT=1");
                }
                else
                {
                    PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT=0");
                    Console.WriteLine("Firebase SDK not installed!");
                }

				string FirebaseAdditionalLibrariesPath = Path.Combine(ThirdPartyUniversalPath, "libs", "ios", "universal");
				bool bRequiresAnalytics = false;

				if(bHasGoogleSDK)
				{
					PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_app.a"));
                    PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_instance_id.a"));

                    PublicAdditionalFrameworks.Add(
						new Framework(
						   "FirebaseCore",
						   "../ThirdParty/IOS/FirebaseCore.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "FirebaseCoreDiagnostics",
						   "../ThirdParty/IOS/FirebaseCoreDiagnostics.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "GTMSessionFetcher",
						   "../ThirdParty/IOS/GTMSessionFetcher.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
                           "GoogleAppMeasurement",
                           "../ThirdParty/IOS/GoogleAppMeasurement.embeddedframework.zip"
                        )
					);

                    PublicAdditionalFrameworks.Add(
						new Framework(
                           "GoogleUtilities",
                           "../ThirdParty/IOS/GoogleUtilities.embeddedframework.zip"
                        )
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "nanopb",
						   "../ThirdParty/IOS/nanopb.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "GoogleSignIn",
						   "../ThirdParty/IOS/GoogleSignIn.embeddedframework.zip",
                           "Resources/GoogleSignIn.bundle"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "Protobuf",
						   "../ThirdParty/IOS/Protobuf.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "GTMOAuth2",
						   "../ThirdParty/IOS/GTMOAuth2.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "GoogleToolboxForMac",
						   "../ThirdParty/IOS/GoogleToolboxForMac.embeddedframework.zip"
						)
					);

					PublicAdditionalFrameworks.Add(
						new Framework(
						   "GoogleAPIClientForREST",
						   "../ThirdParty/IOS/GoogleAPIClientForREST.embeddedframework.zip"
						)
					);

                    PublicAdditionalFrameworks.Add(
						new Framework(
                           "FirebaseABTesting",
                           "../ThirdParty/IOS/FirebaseABTesting.embeddedframework.zip"
                        )
					);

                    PublicAdditionalFrameworks.Add(
			            new Framework(
						    "FirebaseInstanceID",
						    "../ThirdParty/IOS/FirebaseInstanceID.embeddedframework.zip"
					    )
					);
				

					if (bEnableAuthentication)
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_auth.a"));

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseAuth",
							   "../ThirdParty/IOS/FirebaseAuth.embeddedframework.zip"
							)
						);
					}

					if(bEnableCrashlytics)
					{
                        PublicAdditionalFrameworks.Add(
						    new Framework(
							    "Fabric",
							    "../ThirdParty/IOS/Fabric.embeddedframework.zip"
						    )
				        );

				        PublicAdditionalFrameworks.Add(
						    new Framework(
							    "Crashlytics",
							    "../ThirdParty/IOS/Crashlytics.embeddedframework.zip"
						    )
				        );
					}

                    if (bEnableLinksInvites)
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_invites.a"));
                        PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_dynamic_links.a"));

                        PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseInvites",
							   "../ThirdParty/IOS/FirebaseInvites.embeddedframework.zip",
                               "Resources/GINInviteResources.bundle"
                            )
						);

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseDynamicLinks",
							   "../ThirdParty/IOS/FirebaseDynamicLinks.embeddedframework.zip",
                               "Resources/GPPACLPickerResources.bundle"
                            )
						);
                    }

                    if (bEnableCloudMessaging)
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_messaging.a"));

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseMessaging",
							   "../ThirdParty/IOS/FirebaseMessaging.embeddedframework.zip"
							)
						);

						bRequiresAnalytics = true;
					}

                    if(bEnableInAppMessaging)
                    {
                        PublicAdditionalFrameworks.Add(
							new Framework(
                               "FirebaseInAppMessaging",
                               "../ThirdParty/IOS/FirebaseInAppMessaging.embeddedframework.zip"
                            )
						);

                        PublicAdditionalFrameworks.Add(
							new Framework(
                               "FirebaseInAppMessagingDisplay",
                               "../ThirdParty/IOS/FirebaseInAppMessagingDisplay.embeddedframework.zip",
                               "Resources/InAppMessagingDisplayResources.bundle"
                            )
						);
                    }

					if (bEnableRemoteConfig)
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_remote_config.a"));

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseRemoteConfig",
							   "../ThirdParty/IOS/FirebaseRemoteConfig.embeddedframework.zip"
							)
						);
					}

					if (bEnablePerformanceMonitoring)
					{
						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebasePerformance",
							   "../ThirdParty/IOS/FirebasePerformance.embeddedframework.zip"
							)
						);
                    }

					if (bEnableStorage)
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_storage.a"));

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseStorage",
							   "../ThirdParty/IOS/FirebaseStorage.embeddedframework.zip"
							)
						);
					}

                    if (bEnableDataBase_CKH)
                    {
                        PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_database.a"));

                        PublicAdditionalFrameworks.Add(
                            new Framework(
							   "FirebaseDatabase",
                               "../ThirdParty/IOS/FirebaseDatabase.embeddedframework.zip"
                            )
                        );
                    }

                    if ((bEnableAnalytics || bRequiresAnalytics))
					{
						PublicAdditionalLibraries.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "libfirebase_analytics.a"));

						PublicAdditionalFrameworks.Add(
							new Framework(
							   "FirebaseAnalytics",
							   "../ThirdParty/IOS/FirebaseAnalytics.embeddedframework.zip"
							)
						);

                        PublicAdditionalFrameworks.Add(
							new Framework(
                               "FIRAnalyticsConnector",
                               "../ThirdParty/IOS/FIRAnalyticsConnector.embeddedframework.zip"
                            )
						);
					}
				}

				PublicFrameworks.AddRange(
					new string[]
					{
						"AddressBook",
						"AddressBookUI",
						"AudioToolbox",
						"AVFoundation",
						"CFNetwork",
						"CoreData",
						"CoreGraphics",
						"CoreLocation",
						"CoreMedia",
						"CoreMotion",
						"CoreTelephony",
						"EventKit",
						"EventKitUI",
						"Foundation",
						"GLKit",
						"MapKit",
						"MediaPlayer",
						"MessageUI",
						"MobileCoreServices",
                        "LocalAuthentication",
                        "PassKit",
						"QuartzCore",
						"SafariServices",
						"Security",
						"Social",
						"StoreKit",
						"SystemConfiguration",
						"Twitter",
						"UIKit",
						"WebKit"
					}
				);

				PublicAdditionalLibraries.Add("xml2");
				PublicAdditionalLibraries.Add("sqlite3");
				PublicAdditionalLibraries.Add("c++");
				PublicAdditionalLibraries.Add("z");

				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "UltimateMobileKit_UPL_IOS.xml"));
			}
			// Android
			else if (Target.Platform == UnrealTargetPlatform.Android)
			{
				// SDKs checks
				bool bHasGoogleSDK = (Directory.Exists(ThirdPartyPath) &&
									  Directory.Exists(ThirdPartyUniversalPath) &&
									  File.Exists(Path.Combine(ThirdPartyUniversalPath, "libs", "android", "armeabi", "c++", "libfirebase_analytics.a")));

				if (bHasGoogleSDK)
				{
					PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT=1");
				}
				else
				{
					PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT=0");
					Console.WriteLine("Firebase SDK not installed!");
				}

				string FirebaseAdditionalLibrariesPath = Path.Combine(ThirdPartyUniversalPath, "libs", "android");
				PublicLibraryPaths.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "armv7"));
				PublicLibraryPaths.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "arm64"));
				PublicLibraryPaths.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "x86"));
				PublicLibraryPaths.Add(Path.Combine(FirebaseAdditionalLibrariesPath, "x86_64"));

				if (bHasGoogleSDK)
				{
					PublicAdditionalLibraries.Add("firebase_app");
                    PublicAdditionalLibraries.Add("firebase_instance_id");
				
					if(bEnableAnalytics)
					{
						PublicAdditionalLibraries.Add("firebase_analytics");
					}

					if (bEnableAuthentication)
					{
						PublicAdditionalLibraries.Add("firebase_auth");
					}

					if (bEnableLinksInvites)
					{
                        PublicAdditionalLibraries.Add("firebase_invites");
                        PublicAdditionalLibraries.Add("firebase_dynamic_links");
                    }

                    if (bEnableCloudMessaging)
					{
						PublicAdditionalLibraries.Add("firebase_messaging");
					}

					if (bEnableRemoteConfig)
					{
						PublicAdditionalLibraries.Add("firebase_remote_config");
					}

					if (bEnableStorage)
					{
						PublicAdditionalLibraries.Add("firebase_storage");
					}

                    if (bEnableDataBase_CKH)
                    {
                        PublicAdditionalLibraries.Add("firebase_database");
                    }
                }

				PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "UltimateMobileKit_UPL_Android.xml"));
			}
			// Other platforms
			else
			{
				PublicDefinitions.Add("WITH_ULTIMATEMOBILEKIT=0");
			}
		}

		private static void CopyFileDirectory(string SourceDir, string DestDir, Dictionary<string, string> Replacements)
		{
			if (!Directory.Exists(SourceDir))
			{
				return;
			}

			string[] Files = Directory.GetFiles(SourceDir, "*.*", SearchOption.AllDirectories);
			foreach (string Filename in Files)
			{
				// skip template files
				if (Path.GetExtension(Filename) == ".template")
				{
					continue;
				}

				// make the dst filename with the same structure as it was in SourceDir
				string DestFilename = Path.Combine(DestDir, Utils.MakePathRelativeTo(Filename, SourceDir));
				if (File.Exists(DestFilename))
				{
					File.Delete(DestFilename);
				}

				// make the subdirectory if needed
				string DestSubdir = Path.GetDirectoryName(DestFilename);
				if (!Directory.Exists(DestSubdir))
				{
					Directory.CreateDirectory(DestSubdir);
				}

				// some files are handled specially
				string Ext = Path.GetExtension(Filename);
				if (Ext == ".xml")
				{
					string Contents = File.ReadAllText(Filename);

					// replace some varaibles
					foreach (var Pair in Replacements)
					{
						Contents = Contents.Replace(Pair.Key, Pair.Value);
					}

					// write out file
					File.WriteAllText(DestFilename, Contents);
				}
				else
				{
					File.Copy(Filename, DestFilename);

					// remove any read only flags
					FileInfo DestFileInfo = new FileInfo(DestFilename);
					DestFileInfo.Attributes = DestFileInfo.Attributes & ~FileAttributes.ReadOnly;
				}
			}
		}
	}
}
