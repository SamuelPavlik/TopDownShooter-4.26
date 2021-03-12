// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamagabley.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIDamagabley : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNSHOOTER_API IIDamagabley
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AffectHealth(float Delta) = 0;

	virtual void Kill() = 0;

	virtual bool IsKilled() = 0;

};
