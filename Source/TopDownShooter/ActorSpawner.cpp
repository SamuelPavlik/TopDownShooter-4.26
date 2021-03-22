// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
AActorSpawner::AActorSpawner() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);
}

void AActorSpawner::SpawnActor() {
	if (CurrOfActors < MaxOfActors) {
		FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(),
			SpawnVolume->GetScaledBoxExtent());
		GetWorld()->SpawnActor(ActorToSpawnClass, &SpawnLoc);
		CurrOfActors++;
	}
}

void AActorSpawner::Reset() {
	CurrOfActors = 0;
}

void AActorSpawner::DecrActors() {
	CurrOfActors--;
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AActorSpawner::SpawnActor, HowOften, true);
}

