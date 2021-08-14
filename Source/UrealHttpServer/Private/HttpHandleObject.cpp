// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpHandleObject.h"
#include "Runtime/Online/HTTPServer/Public/HttpServerModule.h"
#include "Runtime/Online/HTTPServer/Public/HttpPath.h"

DEFINE_LOG_CATEGORY(HttpHandle)

FString UHttpHandleObject::DoWork_Implementation(UHttpSystemRequest* request)
{
	return "";
}

TUniquePtr<FHttpServerResponse> UHttpHandleObject::ProcessRequest(const FHttpServerRequest& rRequest)
{
	UHttpSystemRequest* request = NewObject<UHttpSystemRequest>();
	request->SetRequst(rRequest);

	FString response = this->DoWork(request);
	UE_LOG(HttpHandle, Log, TEXT("ProcessRequest request:%s  response:%s"), *this->GetPath(), *response);
	return FHttpServerResponse::Create(response, this->ContentType);
}
