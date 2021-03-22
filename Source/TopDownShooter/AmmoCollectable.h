// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "AmmoCollectable.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UAmmoCollectable : public UCollectable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "AmmoProperties")
	uint32 NumOfClips = 3;

public:
	virtual void Interact(AHeroCharacter*) override;
};
