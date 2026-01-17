// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CYH_Net : ModuleRules
{
	public CYH_Net(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "UMG", "Niagara", "NetCore" });
	}
}
