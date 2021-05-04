// Fill out your copyright notice in the Description page of Project Settings.


#include "UploadMapWidget.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UUploadMapWidget::uploadMap(FString mapName)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir()) + TEXT("/MapData.map");
	TArray<uint8> FileContent;
	FFileHelper::LoadFileToArray(FileContent, *FilePath);
	TArray<uint8> Content;

	Request->OnProcessRequestComplete().BindUObject(this, &UUploadMapWidget::OnUploadResponseRecieved);
	Request->SetURL("http://174.138.48.164:9001/uploadMap");
	Request->SetVerb("POST");
	Request->SetHeader(FString("Content-Type"), "multipart/form-data; boundary=zzzzzz");
	

	FString b1 = "\r\n--zzzzzz\r\n";
	FString b2 = "Content-Disposition: form-data; name=\"map\";  filename=\"MapData.map\"\r\n";

	FString b3 = "Content-Type: application/octet-stream\r\n\r\n";
	FString b4 = "Content-Disposition: form-data; name=\"name\"\r\n";
	FString b5 = "Content-Type: text\r\n\r\n";
	FString b6 = "\r\n--zzzzzz--\r\n";

	/// <summary>
	/// CHANGE THIS TO TAKE USER INPUT
	/// </summary>
	//FString mapName = "TEST MAP 9002";

	Content.Append((uint8*)TCHAR_TO_UTF8(*b1), b1.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*b2), b2.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*b3), b3.Len());
	Content.Append(FileContent);
	Content.Append((uint8*)TCHAR_TO_UTF8(*b1), b1.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*b4), b4.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*b5), b5.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*mapName), mapName.Len());
	Content.Append((uint8*)TCHAR_TO_UTF8(*b6), b6.Len());

	Request->SetContent(Content);

	Request->ProcessRequest();
	
}

void UUploadMapWidget::OnUploadResponseRecieved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Hit callback"));
	if (bWasSuccessful) {
		if (Request->GetStatus() == 200) {
			UE_LOG(LogTemp, Warning, TEXT("SUCCESSSSSS BITCH!!!"));
		}
	}
}
