// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"

AGround::AGround()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial>FindGroundMat(TEXT("/Game/Voxel/Materials/M_Ground"));

	if (FindGroundMat.Succeeded())
	{
		GroundMat = FindGroundMat.Object;

		BaseVoxelMesh->SetMaterial(0, GroundMat);
	}
}
