// Fill out your copyright notice in the Description page of Project Settings.


#include "Cobble.h"

ACobble::ACobble()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterial>FindCobbleMat(TEXT("/Game/Voxel/Materials/M_Cobble"));

	if (FindCobbleMat.Succeeded())
	{
		CobbleMat = FindCobbleMat.Object;

		BaseVoxelMesh->SetMaterial(0, CobbleMat);
	}
}
