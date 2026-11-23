// Fill out your copyright notice in the Description page of Project Settings.



#include "Chunk.h"
#include "Cobble.h"
#include "Slime.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnLocation = FVector(0, 0, 100);
	SpawnRotation = FRotator::ZeroRotator;

}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.OverrideLevel = GetLevel();

	bool Switcher = true;
	int VoxelCount = 0;
	int Size = 100;

	for (int z = 0; z < ChunkZ; z++)
	{
		for (int y = 0; y < ChunkY; y++)
		{
			for (int x = 0; x < ChunkX; x++)
			{

				//Chunk[x][y][z] = GetWorld()->SpawnActor<ASlime>(ASlime::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);


				if (z == 0)
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<ACobble>(ACobble::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
				else if (z == 1)
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<AOnyx>(AOnyx::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
				else if (z == 2)
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<AMetal>(AMetal::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
				else if (z == 3)
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<ASlime>(ASlime::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
				else if (z == 4)
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<AGrass>(AGrass::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}
				else
				{
					Chunk[x][y][z] = GetWorld()->SpawnActor<ASlime>(ASlime::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				}

				if (Chunk[x][y][z]) Chunk[x][y][z]->SetActorScale3D(FVector(BaseVoxelMeasurement, BaseVoxelMeasurement, BaseVoxelMeasurement));

				VoxelCount++;
				//Switcher = !Switcher;

				SpawnLocation.X += (BaseVoxelMeasurement * Size);
			}
			SpawnLocation.X -= (ChunkX * (BaseVoxelMeasurement * Size));
			SpawnLocation.Y += (BaseVoxelMeasurement * Size);
		}
		SpawnLocation.Y -= (ChunkY * (BaseVoxelMeasurement * Size));
		SpawnLocation.Z += (BaseVoxelMeasurement * Size);
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Voxel Count: %d"), VoxelCount));
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}