// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"

void AEnemySpawner::SpawnActor() {
	if (CurrOfActors < MaxOfActors) {
		FVector SpawnLoc = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), 
			SpawnVolume->GetScaledBoxExtent());
		APawn* EnemyPawn = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), 
			ActorToSpawnClass, NULL, SpawnLoc);
		if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(EnemyPawn)) {
			Enemy->SetSpawner(this);
			CurrOfActors++;
		}
	}
}

