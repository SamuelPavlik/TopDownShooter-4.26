// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MenuHeroCharacter.generated.h"

class AWeapon;
class USphereComponent;

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AMenuHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	USphereComponent* ViewRadius;

protected:

	UPROPERTY(BlueprintReadWrite)
	AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsReloading;

public:
	AMenuHeroCharacter();

	bool HasEmptyClip();

	void ReloadWeapon();

	virtual void AffectHealth(float) override;

	void Shoot(bool bPressed);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ReloadEffect();
};
