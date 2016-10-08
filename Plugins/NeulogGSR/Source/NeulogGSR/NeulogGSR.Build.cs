using UnrealBuildTool;

public class NeulogGSR : ModuleRules
{
	public NeulogGSR(TargetInfo Target)
	{
		PublicIncludePaths.Add("NeulogGSR/Public");
		PrivateIncludePaths.AddRange(new[]
		{
			"NeulogGSR/Private",
			"NeulogGSR/ThirdParty/serial/include/",
		});
		
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
		});
			
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
		});
	}
}
