// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerRequest.h"
#include "HttpSystemRequest.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UREALHTTPSERVER_API UHttpSystemRequest : public UObject
{
	GENERATED_BODY()

public:
	void SetRequst(const FHttpServerRequest& request)
	{
		pRequest = &request;
	}

	UFUNCTION(BlueprintCallable)
	FString GetQueryParams(FString paramName);

	UFUNCTION(BlueprintCallable)
	const TMap<FString, FString>& GetAllQueryParam();
private:
	const FHttpServerRequest* pRequest;
};
