// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UrealHttpServerServerTarget : TargetRules
{
    public UrealHttpServerServerTarget(TargetInfo Target) : base(Target) //���������Ŀ���Ƹ��Ĵ���
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("UrealHttpServer"); //���������Ŀ���Ƹ��Ĵ���

        bUseLoggingInShipping = true;
    }
}
