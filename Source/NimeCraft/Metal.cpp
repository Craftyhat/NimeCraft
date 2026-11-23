// Fill out your copyright notice in the Description page of Project Settings.


#include "Metal.h"

AMetal::AMetal()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial>FindMetalMat(TEXT("/Game/Voxel/Materials/M_Metal"));

	if (FindMetalMat.Succeeded())
	{
		MetalMat = FindMetalMat.Object;

		BaseVoxelMesh->SetMaterial(0, MetalMat);
	}
}
