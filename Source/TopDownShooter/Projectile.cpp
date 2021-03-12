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
	//ProjectileCollision->SetupAttachment(RootComponent);
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::DestroyProjectile);
}

void AProjectile::DestroyProjectile(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 index, bool bSweep, const FHitResult& Hit) {
	if (IIDamagabley* Damagable = Cast<IIDamagabley>(OtherActor)) {
		if (!OtherActor->ActorHasTag(FRIENDLY)) {
			DestroyProjectileEffect();
			Damagable->AffectHealth(Damage);
			Destroy();
		}
	}
}