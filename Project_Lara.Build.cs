// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Lara : ModuleRules
{
    public Project_Lara(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { "NavigationSystem", "AIModule" });
    }
}
