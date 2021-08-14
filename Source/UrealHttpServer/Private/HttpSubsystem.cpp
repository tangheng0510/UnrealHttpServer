// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpSubsystem.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerModule.h"
#include "Runtime/Online/HTTPServer/Public/HttpPath.h"
#include "Runtime/Online/HTTPServer/Public/IHttpRouter.h"
#include "HttpHandleObject.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(HttpSubsystem)

bool UHttpSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return this->ShouldCreate();
}

void UHttpSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UHttpSubsystem::Deinitialize()
{
	if (!isStart)
	{
		return;
	}

	FModuleManager::Get().UnloadModule("HTTPServer"); //编辑器下不会真的退出，这里卸载清理
	isStart = false;
}

void UHttpSubsystem::AddRoute(UHttpHandleObject* handle)
{
	auto HttpServerModule = &FHttpServerModule::Get();
	TSharedPtr<IHttpRouter> HttpRouter = HttpServerModule->GetHttpRouter(handle->GetPort());
	FHttpRouteHandle routeHandle = HttpRouter->BindRoute(FHttpPath(handle->GetPath()), this->GetHttpServerRequestVerbs(handle->GetMethod()), this->CreateHandler(handle));
	if (routeHandle.IsValid())
	{
		auto pathMap = mapHandles.Find(handle->GetPort());
		if (!pathMap)
		{
			mapHandles.Add(handle->GetPort(), {});
			pathMap = mapHandles.Find(handle->GetPort());
		}

		pathMap->Add(handle->GetPath(), routeHandle);
	}

	UE_LOG(HttpSubsystem, Log, TEXT("Add route port:%d  path:%s"), handle->GetPort(), *handle->GetPath());
}

void UHttpSubsystem::Rebind(UHttpHandleObject* handle)
{
	auto HttpServerModule = &FHttpServerModule::Get();
	TSharedPtr<IHttpRouter> HttpRouter = HttpServerModule->GetHttpRouter(handle->GetPort());
	auto pathMap = mapHandles.Find(handle->GetPort());
	if (pathMap)
	{
		if (pathMap->Contains(handle->GetPath()))
		{
			FHttpRouteHandle routeHandle = (*pathMap)[handle->GetPath()];
			HttpRouter->UnbindRoute(routeHandle);
			pathMap->Remove(handle->GetPath());
		}
	}

	this->AddRoute(handle);
}

EHttpServerRequestVerbs UHttpSubsystem::GetHttpServerRequestVerbs(UHTTP_METHOD method)
{
	switch (method)
	{
	case UHTTP_METHOD::UHTTP_METHOD_Get:
		return EHttpServerRequestVerbs::VERB_GET;
		break;
	case UHTTP_METHOD::UHTTP_METHOD_Post:
		return EHttpServerRequestVerbs::VERB_POST;
		break;
	default:
		break;
	}

	return EHttpServerRequestVerbs::VERB_NONE;
}

FHttpRequestHandler UHttpSubsystem::CreateHandler(UHttpHandleObject* object)
{
	return [object](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
	{
		auto Response = object->ProcessRequest(Request);
		if (Response == nullptr)
		{
			return false;
		}
		OnComplete(MoveTemp(Response));
		return true;
	};
}

void UHttpSubsystem::StartServer()
{
	if (isStart)
	{
		return;
	}

 	auto HttpServerModule = &FHttpServerModule::Get();
 	HttpServerModule->StartAllListeners();

	isStart = true;
}

bool UHttpSubsystem::ShouldCreate_Implementation() const
{
	return false;
}
