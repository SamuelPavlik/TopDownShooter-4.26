// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownShooter.h"
#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"

void AEnemyController::BeginPlay() {
	Super::BeginPlay();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemyController::TrackPlayer, 0.2f, true);
}

void AEnemyController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	EnemyPawn = Cast<AEnemyCharacter>(InPawn);
	if (EnemyPawn) {
		EnemyPawn->DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnHeroBeginOverlap);
		EnemyPawn->DamageVolume->OnComponentEndOverlap.AddDynamic(this, &AEnemyController::OnHeroEndOverlap);
	}
}

void AEnemyController::DamageHero() {
	EnemyPawn->DamageHero();
}

void AEnemyController::TrackPlayer() {
	TArray<AActor*> FoundHeroes;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FRIENDLY, FoundHeroes);
	if (FoundHeroes.Num())
		MoveToActor(FoundHeroes[0]);
}

FTimerHandle DamageHandle;
void AEnemyController::OnHeroBeginOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg,
	UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit) {
	ABaseCharacter* Hero = Cast<ABaseCharacter>(ActorToDmg);
	if (Hero && ActorToDmg->ActorHasTag(FRIENDLY)) {
		EnemyPawn->HeroToDmg = Hero;
		DamageHero();
		GetWorldTimerManager().SetTimer(DamageHandle, this, &AEnemyController::DamageHero, 1.5f, true);
	}
}

void AEnemyController::OnHeroEndOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, 
	UPrimitiveComponent* OtherComp, int32 Index) {
	if (ActorToDmg == EnemyPawn->HeroToDmg) {
		GetWorldTimerManager().ClearTimer(DamageHandle);
		EnemyPawn->HeroToDmg = NULL;
	}
}
