// Fill out your copyright notice in the Description page of Project
#include "EnemyCharacter.h"
#include "EnemySpawner.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "TopDownShooterGameModeBase.h"
#include "TopDownShooter.h"

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(ENEMY);
	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageVolume"));
	DamageVolume->SetupAttachment(GetRootComponent());
}

void AEnemyCharacter::SetSpawner(AEnemySpawner* SpawnerToSet) {
	this->Spawner = SpawnerToSet;
}

void AEnemyCharacter::Kill() {
	if (GameMode) {
		GameMode->IncrementScore();
	}

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	DetachFromControllerPendingDestroy();

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemyCharacter::DestroyEnemy, 3.0f, false, 3.0f);
}

void AEnemyCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnProjectileBeginOverlap);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("spine_01"), true, false);
	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnHeroBeginOverlap);
	DamageVolume->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnHeroEndOverlap);
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<ATopDownShooterGameModeBase>();	
}

void AEnemyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	CurrentBlendWeight = UKismetMathLibrary::FInterpTo_Constant(CurrentBlendWeight, 0.f, DeltaTime, 0.3f);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(TEXT("spine_01"), CurrentBlendWeight, false, false);
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
		DamageHero();
		GetWorldTimerManager().SetTimer(DamageHandle, this, &AEnemyCharacter::DamageHero, 1.5f, true);
	}
}

void AEnemyCharacter::OnHeroEndOverlap(UPrimitiveComponent*, AActor* ActorToDmg, UPrimitiveComponent*, int32) {
	if (ActorToDmg == HeroToDmg) {
		GetWorldTimerManager().ClearTimer(DamageHandle);
		HeroToDmg = NULL;
	}
}

void AEnemyCharacter::OnProjectileBeginOverlap(UPrimitiveComponent*, AActor* Projectile, UPrimitiveComponent*, int32, bool, const FHitResult&) {
	if (Projectile->ActorHasTag(PROJECTILE)) {
		CurrentBlendWeight = 0.3f;
	}
}

void AEnemyCharacter::DamageHeroLogic() {
	if (HeroToDmg) {
		HeroToDmg->AffectHealth(Damage);
	}
}
