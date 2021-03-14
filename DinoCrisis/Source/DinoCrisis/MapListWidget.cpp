// Fill out your copyright notice in the Description page of Project Settings.


#include "MapListWidget.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UMapListWidget::getMapList()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UMapListWidget::OnMapListResponseRecieved);
	Request->SetURL("http://10.0.0.187:9001/mapList");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UMapListWidget::OnMapListResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	if (bWasSuccessful) {
		TArray<TSharedPtr<FJsonValue> > JsonArray;
		TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (FJsonSerializer::Deserialize(JsonReader, JsonArray))
		{
			for (int i = 0; i < JsonArray.Num(); i++) {
				TSharedPtr<FJsonObject> json = JsonArray[i]->AsObject();
				FMapStruct map;
				map.id = json->GetIntegerField(TEXT("id"));
				map.name = json->GetStringField(TEXT("name"));
				maps.Push(map);
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Before"));
		OnListDelegate.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("After"));
	}
}

void UMapListWidget::downloadMap(int32 mapID)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UMapListWidget::OnDownloadMapResponseRecieved);
	FString url = FString(TEXT("http://10.0.0.187:9001/map?id="));
	url.AppendInt(mapID);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UMapListWidget::OnDownloadMapResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	if (bWasSuccessful) {
		FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
		
		FFileHelper::SaveStringToFile(Response->GetContentAsString(), *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
		OnMapDelegate.Broadcast();
	}
}
