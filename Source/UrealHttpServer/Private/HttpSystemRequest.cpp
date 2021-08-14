// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpSystemRequest.h"

FString UHttpSystemRequest::GetQueryParams(FString paramName)
{
	if (pRequest->QueryParams.Contains(paramName))
	{
		return pRequest->QueryParams[paramName];
	}

	return "";
}

const TMap<FString, FString>& UHttpSystemRequest::GetAllQueryParam()
{
	return pRequest->QueryParams;
}
