// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HttpManager.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "UploadMapWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSuccessDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailureDelegate);

UCLASS()
class DINOCRISIS_API UUploadMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void uploadMap();

	void OnUploadResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



	UPROPERTY(BlueprintAssignable)
		FSuccessDelegate OnSuccessDelegate;

	UPROPERTY(BlueprintAssignable)
		FFailureDelegate OnFailureDelegate;
};
