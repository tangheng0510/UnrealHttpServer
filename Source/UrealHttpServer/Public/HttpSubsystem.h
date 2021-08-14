// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerRequest.h"
#include "Runtime/Online/HTTPServer/Public/HttpRouteHandle.h"
#include "HttpSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HttpSubsystem, Log, All);

enum class UHTTP_METHOD : uint8;
enum class EHttpServerRequestVerbs : uint16;
class UHttpHandleObject;
/**
 * 
 */
UCLASS(abstract, Blueprintable, BlueprintType)
class UREALHTTPSERVER_API UHttpSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	UFUNCTION(BlueprintCallable)
	void AddRoute(UHttpHandleObject* handle);

	UFUNCTION(BlueprintCallable)
	void Rebind(UHttpHandleObject* handle);

	EHttpServerRequestVerbs GetHttpServerRequestVerbs(UHTTP_METHOD method);
private:
	FHttpRequestHandler CreateHandler(UHttpHandleObject* object);
public:
	UFUNCTION(BlueprintNativeEvent)
	bool ShouldCreate() const;

	UFUNCTION(BlueprintCallable)
	void StartServer();

	bool isStart = false;

	TMap<int, TMap<FString, FHttpRouteHandle>> mapHandles;
};
