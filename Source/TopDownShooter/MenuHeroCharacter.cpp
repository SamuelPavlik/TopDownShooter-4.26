// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHeroCharacter.h"
#include "EnemyCharacter.h"
#include "Weapon.h"
#include "TopDownShooter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"

AMenuHeroCharacter::AMenuHeroCharacter() {
	Tags.Add(FRIENDLY);
	ViewRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ViewRadius"));
	ViewRadius->SetupAttachment(GetRootComponent());
}

TArray<AActor*> AMenuHeroCharacter::GetTargets() {
	return EnemiesInView;
}

bool AMenuHeroCharacter::NeedsToReload() {
	return Weapon->CurrentClipAmmo <= 0;
}

void AMenuHeroCharacter::ReloadWeapon() {
	if (Weapon->Reload()) {
		ReloadEffect();
	}
}

void AMenuHeroCharacter::AffectHealth(float) {}

void AMenuHeroCharacter::Tick(float) {
	ViewRadius->GetOverlappingActors(EnemiesInView, AEnemyCharacter::StaticClass());
	Shoot(CanShoot());
}

bool AMenuHeroCharacter::CanShoot() {
	FHitResult Hit;

	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActors(ActorsToIgnore);
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		GetActorLocation(),
		GetActorRotation().Vector() * 4000.0f,
		ECollisionChannel::ECC_Camera,
		Params);

	if (UKismetSystemLibrary::IsValid(Hit.GetActor()) && Hit.GetActor()->ActorHasTag("Enemy")) {
		if (IIDamagabley* ToDamage = Cast<IIDamagabley>(Hit.GetActor())) {
			return !ToDamage->IsKilled() && !bIsReloading;
		}
	}

	return false;
}

void AMenuHeroCharacter::Shoot(bool bPressed) {
	static bool bPulled = false;
	if (bPressed && !bPulled) {
		bPulled = true;
		Weapon->PullTrigger();
	}
	else if (!bPressed && bPulled) {
		bPulled = false;
		Weapon->ReleaseTrigger();
	}
}
