// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team09_DarkLight : ModuleRules
{
	public Team09_DarkLight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
