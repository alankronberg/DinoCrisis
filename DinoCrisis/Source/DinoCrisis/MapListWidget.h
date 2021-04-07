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
	UPROPERTY(BlueprintReadOnly)
	int32 id;
	UPROPERTY(BlueprintReadOnly)
	FString name;
};
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FListDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMapDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FErrorDelegate);

UCLASS()
class DINOCRISIS_API UMapListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void getMapList();

	void OnMapListResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void downloadMap(int32 mapID);

	void OnDownloadMapResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintReadOnly)
	TArray<FMapStruct> maps;

	UPROPERTY(BlueprintReadWrite)
		bool refreshMapList = false;

	UPROPERTY(BlueprintAssignable)
		FListDelegate OnListDelegate;

	UPROPERTY(BlueprintAssignable)
		FMapDelegate OnMapDelegate;

	UPROPERTY(BlueprintAssignable)
		FMapDelegate OnErrorDelegate;
};
