// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHeroController.h"
#include "MenuHeroCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMenuHeroController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (MenuHero->GetTargets().Num() > 0) {
		AActor* Closest = MenuHero->GetTargets()[0];
		float ClosDist = FVector::Distance(Closest->GetActorLocation(), MenuHero->GetActorLocation());
		for (AActor* Current : MenuHero->GetTargets()) {
			float CurrDist = FVector::Distance(Current->GetActorLocation(), MenuHero->GetActorLocation());
			if (CurrDist < ClosDist) {
				Closest = Current;
				ClosDist = CurrDist;
			}
		}
		SetFocus(Closest);
	}

	if (MenuHero->NeedsToReload())
		MenuHero->ReloadWeapon();
}

void AMenuHeroController::BeginPlay() {
	Super::BeginPlay();

	MenuHero = Cast<AMenuHeroCharacter>(GetPawn());
}