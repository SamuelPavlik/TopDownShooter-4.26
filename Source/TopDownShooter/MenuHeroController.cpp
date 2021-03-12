// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHeroController.h"
#include "MenuHeroCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMenuHeroController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (MenuHero->GetTargets().Num() > 0)
		SetFocus(MenuHero->GetTargets()[0]);
}

void AMenuHeroController::BeginPlay() {
	Super::BeginPlay();

	MenuHero = Cast<AMenuHeroCharacter>(GetPawn());
}