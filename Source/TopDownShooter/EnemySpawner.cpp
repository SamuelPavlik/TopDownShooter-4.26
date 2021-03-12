// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AEnemySpawner::AEnemySpawner() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);
}

void AEnemySpawner::SpawnEnemy() {
	if (CurrOfEnemies < MaxOfEnemies) {
		FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), 
			SpawnVolume->GetScaledBoxExtent());
		APawn* EnemyPawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), 
			EnemyToSpawnClass, NULL, SpawnLoc);
		if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(EnemyPawn)) {
			Enemy->SetSpawner(this);
			CurrOfEnemies++;
		}
	}
}

void AEnemySpawner::Reset() {
	CurrOfEnemies = 0;
}

void AEnemySpawner::DecrEnemies() {
	CurrOfEnemies--;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay() {
	Super::BeginPlay();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemySpawner::SpawnEnemy, HowOften, true);
}

