// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HttpManager.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "MapListWidget.generated.h"

USTRUCT(BlueprintType)
struct FMapStruct {
	GENERATED_BODY()

public:
	
	int32 id;
	FString name;
};
/**
 * 
 */
UCLASS()
class DINOCRISIS_API UMapListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void getMapList();

	void OnMapListResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	TArray<FMapStruct> maps;
};
