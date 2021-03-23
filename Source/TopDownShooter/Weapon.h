// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Properties")
	float RoundsPerSec;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon Properties")
	int MaxClipAmmo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Properties")
	int CurrentClipAmmo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int CurrentClip;

private:
	bool Released = true;

	bool CanFire = true;

public:	
	// Sets default values for this actor's properties
	AWeapon();

	void PullTrigger();

	void ReleaseTrigger();

	bool Reload();

	void StopShooting();

	void AddClips(uint32 NumOfClips);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Fire();

	UFUNCTION(BlueprintImplementableEvent)
	void NoAmmoEffect();

	virtual void BeginPlay() override;

	virtual void Destroyed() override;

private:
	void FireFunc();

};
