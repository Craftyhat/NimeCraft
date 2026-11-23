// Fill out your copyright notice in the Description page of Project Settings.


#include "Onyx.h"

AOnyx::AOnyx()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UMaterial>FindOnyxMat(TEXT("/Game/Voxel/Materials/M_Onyx"));

	if (FindOnyxMat.Succeeded())
	{
		OnyxMat = FindOnyxMat.Object;

		BaseVoxelMesh->SetMaterial(0, OnyxMat);
	}
}
