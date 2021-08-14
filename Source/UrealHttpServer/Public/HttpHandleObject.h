// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerResponse.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerRequest.h"
#include "HttpSystemRequest.h"
#include "HttpHandleObject.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(HttpHandle, Log, All)

UENUM(BlueprintType)
enum class UHTTP_METHOD : uint8
{
	UHTTP_METHOD_Get,
	UHTTP_METHOD_Post,
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UREALHTTPSERVER_API UHttpHandleObject : public UObject
{
	GENERATED_BODY()
	
public:
	TUniquePtr<FHttpServerResponse> ProcessRequest(const FHttpServerRequest& rRequest);

	UFUNCTION(BlueprintNativeEvent)
	FString DoWork(UHttpSystemRequest* request);

	int GetPort() { return Port; }

	FString GetPath() { return Path; }

	UHTTP_METHOD GetMethod() { return Method; }
protected:
	UPROPERTY(EditDefaultsOnly)
	int Port;

	UPROPERTY(EditDefaultsOnly)
	FString Path;

	UPROPERTY(EditDefaultsOnly)
	FString ContentType;

	UPROPERTY(EditDefaultsOnly)
	UHTTP_METHOD Method;
};
