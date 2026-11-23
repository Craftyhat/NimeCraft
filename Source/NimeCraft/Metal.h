// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Voxel.h"
#include "Metal.generated.h"

/**
 *
 */
UCLASS()
class NIMECRAFT_API AMetal : public AVoxel
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Metal")
	TObjectPtr<UMaterial> MetalMat;
	AMetal();

public:


};
