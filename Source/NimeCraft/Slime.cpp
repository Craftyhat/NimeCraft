// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime.h"

ASlime::ASlime()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial>FindSlimeMat(TEXT("/Game/Voxel/Materials/M_Slime"));

	if (FindSlimeMat.Succeeded())
	{
		SlimeMat = FindSlimeMat.Object;

		BaseVoxelMesh->SetMaterial(0, SlimeMat);
	}
}
