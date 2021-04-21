// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "IDamagabley.h"
#include "TopDownShooter.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = ProjectileCollision;
}

void AProjectile::PostInitializeComponents() {
	Super::PostInitializeComponents();

	ProjectileCollision->OnComponentHit.AddDynamic(this, &AProjectile::OnEnemyHit);
}

void AProjectile::OnEnemyHit(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, FVector, const FHitResult&) {
	if (IIDamagabley* Damagable = Cast<IIDamagabley>(OtherActor)) {
		if (OtherActor->ActorHasTag(ENEMY)) {
			DestroyProjectileEffect();
			Damagable->AffectHealth(Damage);
			Destroy();
		}
	}
}