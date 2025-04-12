// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Beats_From_The_Deep : ModuleRules
{
	public Beats_From_The_Deep(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara",						// Standard nodes
			"MetasoundFrontend", "MetasoundGraphCore", "MetasoundStandardNodes", "MetasoundEngine", // Metasound
																							// 			
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
