// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHeroCharacter.h"
#include "Weapon.h"
#include "TopDownShooter.h"
#include "Components/SphereComponent.h"

AMenuHeroCharacter::AMenuHeroCharacter() {
	Tags.Add(FRIENDLY);
	ViewRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ViewRadius"));
	ViewRadius->SetupAttachment(GetRootComponent());
}

bool AMenuHeroCharacter::HasEmptyClip() {
	return Weapon->CurrentClipAmmo <= 0;
}

void AMenuHeroCharacter::ReloadWeapon() {
	if (Weapon->Reload()) {
		ReloadEffect();
	}
}

void AMenuHeroCharacter::AffectHealth(float) {}

void AMenuHeroCharacter::Shoot(bool bPressed) {
	static bool bPulled = false;
	
	if (bIsReloading) {
		return;
	}

	if (bPressed && !bPulled) {
		bPulled = true;
		Weapon->PullTrigger();
	}
	else if (!bPressed && bPulled) {
		bPulled = false;
		Weapon->ReleaseTrigger();
	}
}
