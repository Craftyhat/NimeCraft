// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Voxel.h"
#include "Slime.generated.h"

/**
 *
 */
UCLASS()
class NIMECRAFT_API ASlime : public AVoxel
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UMaterial> SlimeMat;
	ASlime();


public:


};
