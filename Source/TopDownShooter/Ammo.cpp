// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "HeroCharacter.h"

// Sets default values
void UAmmo::Interact(AHeroCharacter* Hero) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ammo"));
}

