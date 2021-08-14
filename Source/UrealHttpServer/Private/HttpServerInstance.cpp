// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpServerInstance.h"

void UHttpServerInstance::Init()
{
	//UClass* bpAsset = LoadClass<UClass>(NULL, TEXT("Blueprint'/Game/BP_HttpSystem.BP_HttpSystem'"));

	Super::Init();

	this->AfterInit();
}
