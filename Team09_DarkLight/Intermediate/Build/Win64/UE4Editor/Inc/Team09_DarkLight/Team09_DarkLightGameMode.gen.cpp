// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Team09_DarkLight/Team09_DarkLightGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTeam09_DarkLightGameMode() {}
// Cross Module References
	TEAM09_DARKLIGHT_API UClass* Z_Construct_UClass_ATeam09_DarkLightGameMode_NoRegister();
	TEAM09_DARKLIGHT_API UClass* Z_Construct_UClass_ATeam09_DarkLightGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Team09_DarkLight();
// End Cross Module References
	void ATeam09_DarkLightGameMode::StaticRegisterNativesATeam09_DarkLightGameMode()
	{
	}
	UClass* Z_Construct_UClass_ATeam09_DarkLightGameMode_NoRegister()
	{
		return ATeam09_DarkLightGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Team09_DarkLight,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Team09_DarkLightGameMode.h" },
		{ "ModuleRelativePath", "Team09_DarkLightGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATeam09_DarkLightGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::ClassParams = {
		&ATeam09_DarkLightGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATeam09_DarkLightGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATeam09_DarkLightGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATeam09_DarkLightGameMode, 996006832);
	template<> TEAM09_DARKLIGHT_API UClass* StaticClass<ATeam09_DarkLightGameMode>()
	{
		return ATeam09_DarkLightGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATeam09_DarkLightGameMode(Z_Construct_UClass_ATeam09_DarkLightGameMode, &ATeam09_DarkLightGameMode::StaticClass, TEXT("/Script/Team09_DarkLight"), TEXT("ATeam09_DarkLightGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATeam09_DarkLightGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
