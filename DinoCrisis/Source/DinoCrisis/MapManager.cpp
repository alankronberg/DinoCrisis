// Fill out your copyright notice in the Description page of Project Settings.


#include "MapManager.h"
#include "HttpModule.h"

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMapManager::getMap(int id)
{
	//create the request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Bind response
	Request->OnProcessRequestComplete().BindUObject(this, &AMapManager::OnMapResponseRecieved);
	FString url = FString(TEXT("http://localhost:9001/map?id="));
	url.AppendInt(id);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->ProcessRequest();

}

void AMapManager::OnMapResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response->GetResponseCode() == 200) {
		UE_LOG(LogTemp, Warning, TEXT("Recieved response: %s"), *(Response->GetContentAsString()));
	}
}



// Called when the game starts or when spawned
void AMapManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

