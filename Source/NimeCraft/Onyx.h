// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Voxel.h"
#include "Onyx.generated.h"

/**
 *
 */
UCLASS()
class NIMECRAFT_API AOnyx : public AVoxel
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UMaterial> OnyxMat;
	AOnyx();

};
