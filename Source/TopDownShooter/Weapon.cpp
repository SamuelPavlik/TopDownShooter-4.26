// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FTimerHandle Handle;
void AWeapon::FireFunc() {
	CanFire = true;
	if (!Released && CurrentClipAmmo > 0) {
		CurrentClipAmmo--;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ammo: %d"), CurrentClipAmmo));
		this->Fire();
		CanFire = false;
		GetWorldTimerManager().SetTimer(Handle, this, &AWeapon::FireFunc, 1.0f / RoundsPerSec, false);
	}
	else if (CurrentClipAmmo <= 0) {
		NoAmmoEffect();
	}
}

void AWeapon::PullTrigger() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ammo: %d"), CurrentClipAmmo));
	if (CurrentClipAmmo <= 0) {
		NoAmmoEffect();
		return;
	}

	Released = false;
	if (CanFire)
		FireFunc();
	return;
}

void AWeapon::ReleaseTrigger() {
	Released = true;
}

bool AWeapon::Reload() {
	if (CurrentClip <= 1) {
		return false;
	}
	CurrentClip--;
	CurrentClipAmmo = MaxClipAmmo;
	return true;
}

void AWeapon::StopShooting() {
	Released = true;
	CanFire = false;
	GetWorldTimerManager().ClearTimer(Handle);
}

void AWeapon::AddClips(uint32 NumOfClips) {
	CurrentClip += NumOfClips;
	CurrentClipAmmo = CurrentClipAmmo == 0 ? MaxClipAmmo : CurrentClipAmmo;
}

void AWeapon::BeginPlay() {
	Super::BeginPlay();
	
	CurrentClipAmmo = MaxClipAmmo;
	CurrentClip = 5;
}

void AWeapon::Destroyed() {
	Super::Destroyed();

	GetWorldTimerManager().ClearAllTimersForObject(this);
}
