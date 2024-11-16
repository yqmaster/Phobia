using UnrealBuildTool;
using System.Collections.Generic;

public class PhobiaEditorTarget : TargetRules
{
	public PhobiaEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("Phobia");
	}
}
