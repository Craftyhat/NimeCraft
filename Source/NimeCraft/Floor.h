// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Voxel.h"
#include "Ground.h"
#include "Floor.generated.h"

#define FLOOR_X 5

constexpr int floorX = 70;
constexpr int floorY = 70;

UCLASS()
class NIMECRAFT_API AFloor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY()
	AVoxel* Floor[floorX][floorY];

	// Sets location rotation and spawn parameters for the floor.
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor1")
	// Voxel overall size measurement.
	float BaseVoxelMeasurement = 1.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
