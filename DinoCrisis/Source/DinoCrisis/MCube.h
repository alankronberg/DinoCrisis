// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ProceduralMeshComponent.h"
#include "MCube.generated.h"


//USTRUCT()
//struct FPointData {
//	GENERATED_BODY()
//
//public:
//	UPROPERTY()
//	FVector points[8];
//
//	UPROPERTY()
//	float values[8];
//};

UCLASS()
class DINOCRISIS_API AMCube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMCube();

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* PMC;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner0;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner1;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner2;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner3;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner4;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner5;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner6;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* corner7;


	UPROPERTY()
	FPointData cornerData;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(VisibleAnywhere)
	int isoLevel = 0;

	UPROPERTY()
	float sideLength;

	

	UFUNCTION(BlueprintCallable)
	void incrementConfig();

	UFUNCTION(BlueprintCallable)
	void decrementConfig();

	UFUNCTION()
	void adjustValues();

	UPROPERTY(BlueprintReadOnly)
	int configNum;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateMesh();

	void MarchingCubes();

	FVector Midpoint(FVector point1, FVector point2);

	float halfSide;
	
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
