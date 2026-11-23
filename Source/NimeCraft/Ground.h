// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Voxel.h"
#include "Ground.generated.h"

/**
 *
 */
UCLASS()
class NIMECRAFT_API AGround : public AVoxel
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Ground")
	TObjectPtr<UMaterial> GroundMat;
	AGround();

public:


};
