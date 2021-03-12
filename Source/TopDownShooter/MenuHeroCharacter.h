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
	
protected:
	UPROPERTY(EditAnywhere)
	USphereComponent* ViewRadius;

	UPROPERTY(BlueprintReadWrite)
	AWeapon* Weapon;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> ActorsToIgnore;

private:
	TArray<AActor*> EnemiesInView;

public:
	AMenuHeroCharacter();

	TArray<AActor*> GetTargets();

	virtual void AffectHealth(float) override;

public:
	virtual void Tick(float) override;

private:
	bool FacingEnemy();

	void Shoot(bool bPressed);
};
