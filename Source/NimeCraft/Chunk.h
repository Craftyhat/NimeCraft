// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Voxel.h"
#include "Cobble.h"
#include "Slime.h"
#include "Ground.h"
#include "Grass.h"
#include "Metal.h"
#include "Onyx.h"
#include "Chunk.generated.h"

constexpr int ChunkX = 5;
constexpr int ChunkY = 5;
constexpr int ChunkZ = 5;

UCLASS()
class NIMECRAFT_API AChunk : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY()
	AVoxel* Chunk[ChunkX][ChunkY][ChunkZ];

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	float BaseVoxelMeasurement = 1.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
