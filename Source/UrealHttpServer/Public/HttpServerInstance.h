// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HttpServerInstance.generated.h"

/**
 * 
 */
UCLASS()
class UREALHTTPSERVER_API UHttpServerInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void AfterInit();
};
