// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHeroController.h"
#include "MenuHeroCharacter.h"
#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void AMenuHeroController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (MenuHero->HasEmptyClip()) {
		MenuHero->Shoot(false);
		MenuHero->ReloadWeapon();
	}
	else if (IsFacingEnemy()) {
		MenuHero->Shoot(true);
	}
	else {
		MenuHero->Shoot(false);
	}
}

void AMenuHeroController::BeginPlay() {
	Super::BeginPlay();
	MenuHero = Cast<AMenuHeroCharacter>(GetPawn());

	if (USphereComponent* ViewRadius = MenuHero->ViewRadius) {
		ViewRadius->OnComponentBeginOverlap.AddDynamic(this, &AMenuHeroController::OnBeginOverlap);
		ViewRadius->OnComponentEndOverlap.AddDynamic(this, &AMenuHeroController::OnEndOverlap);
	}
}

bool AMenuHeroController::IsFacingEnemy() {
	FHitResult Hit;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetPawn());
	GetWorld()->LineTraceSingleByChannel(Hit, GetPawn()->GetActorLocation(),
		GetPawn()->GetActorRotation().Vector() * 4000.0f, ECollisionChannel::ECC_Camera, Params);

	if (UKismetSystemLibrary::IsValid(Hit.GetActor()) && Hit.GetActor()->ActorHasTag("Enemy")) {
		if (IIDamagabley* ToDamage = Cast<IIDamagabley>(Hit.GetActor())) {
			return !ToDamage->IsKilled();
		}
	}

	return false;
}

void AMenuHeroController::OnBeginOverlap(UPrimitiveComponent* ThisComp, AActor* Actor, 
	UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit) {
	OnEnemyChange(ThisComp);
}

void AMenuHeroController::OnEndOverlap(UPrimitiveComponent* ThisComp, AActor* Actor, UPrimitiveComponent* OtherComp, int32 Index) {
	OnEnemyChange(ThisComp);
}

void AMenuHeroController::OnEnemyChange(UPrimitiveComponent* ViewRadius) {
	TArray<AActor*> EnemiesInView;
	ViewRadius->GetOverlappingActors(EnemiesInView, AEnemyCharacter::StaticClass());
	if (EnemiesInView.Num() > 0) {
		AActor* Closest = EnemiesInView[0];
		float ClosDist = FVector::Distance(Closest->GetActorLocation(), MenuHero->GetActorLocation());
		for (AActor* Current : EnemiesInView) {
			float CurrDist = FVector::Distance(Current->GetActorLocation(), MenuHero->GetActorLocation());
			if (CurrDist < ClosDist) {
				Closest = Current;
				ClosDist = CurrDist;
			}
		}
		SetFocus(Closest);
	}
}
