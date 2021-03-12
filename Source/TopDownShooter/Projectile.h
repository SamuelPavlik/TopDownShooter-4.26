// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;

UCLASS()
class TOPDOWNSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* ProjectileCollision;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	float Damage = -20.0f;

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DestroyProjectileEffect();

	UFUNCTION(BlueprintCallable)
	void DestroyProjectile(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 index, bool bSweep, const FHitResult& Hit);
};
