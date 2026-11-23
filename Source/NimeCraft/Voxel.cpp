// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AVoxel::AVoxel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseVoxelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Voxel Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>FindVoxelMesh(TEXT("/Game/Voxel/BaseVoxel"));
	static ConstructorHelpers::FObjectFinder<UMaterial>FindVoxelMat(TEXT("/Game/Voxel/M_BaseVoxel"));
	static ConstructorHelpers::FObjectFinder<USoundWave>SoundRef(TEXT("/Game/Sounds_Music/Pickaxe_Sound.Pickaxe_Sound"));
	//MineSound = SoundRef.Object;

	if (FindVoxelMesh.Succeeded())
	{
		BaseVoxelMesh->SetStaticMesh(FindVoxelMesh.Object);
	}
	if (FindVoxelMat.Succeeded())
	{
		BaseVoxelMaterial = FindVoxelMat.Object;

		BaseVoxelMesh->SetMaterial(0, BaseVoxelMaterial);
	}
	
}

// Called when the game starts or when spawned
void AVoxel::BeginPlay()
{
	Super::BeginPlay();

}

void AVoxel::PlayerInteract()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Oww, I have been Hit?!")));

	Destroy();

	MineSound = LoadObject<USoundBase>(NULL, TEXT("/Game/Sounds_Music/Pickaxe_Sound.Pickaxe_Sound"));

	UGameplayStatics::PlaySound2D(this, MineSound);
}


// Called every frame
void AVoxel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

