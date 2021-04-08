// Fill out your copyright notice in the Description page of Project
#include "EnemyCharacter.h"
#include "EnemySpawner.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "TopDownShooterGameModeBase.h"
#include "TopDownShooter.h"

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(ENEMY);
	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageVolume"));
	DamageVolume->SetupAttachment(GetRootComponent());
	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnHeroBeginOverlap);
	DamageVolume->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnHeroEndOverlap);

}

void AEnemyCharacter::SetSpawner(AEnemySpawner* SpawnerToSet) {
	this->Spawner = SpawnerToSet;
}

void AEnemyCharacter::Kill() {
	if (GameMode)
		GameMode->IncrementScore();
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	DetachFromControllerPendingDestroy();

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemyCharacter::DestroyEnemy, 3.0f, false, 3.0f);
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<ATopDownShooterGameModeBase>();
}

void AEnemyCharacter::DestroyEnemy() {
	Spawner->DecrActors();
	DestroyEnemyEffect();
	Destroy();
}

FTimerHandle DamageHandle;
void AEnemyCharacter::OnHeroBeginOverlap(UPrimitiveComponent*, AActor* ActorToDmg, UPrimitiveComponent*, int32, bool, const FHitResult&) {
	ABaseCharacter* Hero = Cast<ABaseCharacter>(ActorToDmg);
	if (Hero && ActorToDmg->ActorHasTag(FRIENDLY)) {
		this->HeroToDmg = Hero;
		DamageHeroEffect();
		GetWorldTimerManager().SetTimer(DamageHandle, this, &AEnemyCharacter::DamageHeroEffect, 1.5f, true);
	}
}

void AEnemyCharacter::OnHeroEndOverlap(UPrimitiveComponent*, AActor* ActorToDmg, UPrimitiveComponent*, int32) {
	if (ActorToDmg == HeroToDmg) {
		GetWorldTimerManager().ClearTimer(DamageHandle);
		HeroToDmg = NULL;
	}
}

void AEnemyCharacter::DamageHero() {
	if (HeroToDmg) {
		HeroToDmg->AffectHealth(Damage);
	}
}
