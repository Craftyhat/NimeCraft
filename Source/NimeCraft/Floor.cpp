// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "Voxel.h"
#include "Ground.h"

// Sets default values
AFloor::AFloor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnLocation = FVector(-3000, -3000, 0);
	SpawnRotation = FRotator::ZeroRotator;

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.OverrideLevel = GetLevel();

	int VoxelCount = 0;
	int Length = 100;

	// 
	for (int y = 0; y < floorY; y++)
	{
		for (int x = 0; x < floorX; x++)
		{
			Floor[x][y] = GetWorld()->SpawnActor<AGround>(AGround::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

			Floor[x][y]->SetActorScale3D(FVector(BaseVoxelMeasurement, BaseVoxelMeasurement, BaseVoxelMeasurement));

			VoxelCount++;

			SpawnLocation.X += (BaseVoxelMeasurement * Length);
		}
		SpawnLocation.X -= (floorX * (BaseVoxelMeasurement * Length));
		SpawnLocation.Y += (BaseVoxelMeasurement * Length);
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-2, 10.f, FColor::Red, FString::Printf(TEXT("Voxel Count: %d"), VoxelCount));
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

