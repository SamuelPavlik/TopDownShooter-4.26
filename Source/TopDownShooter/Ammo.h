// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "Ammo.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API UAmmo : public UCollectable
{
	GENERATED_BODY()
	
public:	
	virtual void Interact(AHeroCharacter*) override;

};
