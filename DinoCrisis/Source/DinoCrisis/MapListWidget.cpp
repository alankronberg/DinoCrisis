// Fill out your copyright notice in the Description page of Project Settings.


#include "MapListWidget.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"

void UMapListWidget::getMapList()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UMapListWidget::OnMapListResponseRecieved);
	Request->SetURL("http://localhost:9001/mapList");
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
	}
	for (int i = 0; i < maps.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("ID: %d  NAME: %s"), maps[i].id, *(maps[i].name));
	}
}
