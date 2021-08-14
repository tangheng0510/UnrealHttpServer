// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UrealHttpServerServerTarget : TargetRules
{
    public UrealHttpServerServerTarget(TargetInfo Target) : base(Target) //根据你的项目名称更改此行
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("UrealHttpServer"); //根据你的项目名称更改此行

        bUseLoggingInShipping = true;
    }
}
