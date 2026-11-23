// Fill out your copyright notice in the Description page of Project Settings.


#include "Grass.h"

AGrass::AGrass()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial>FindGrassMat(TEXT("/Game/Voxel/Materials/M_Grass"));

	if (FindGrassMat.Succeeded())
	{
		GrassMat = FindGrassMat.Object;

		BaseVoxelMesh->SetMaterial(0, GrassMat);
	}
}
