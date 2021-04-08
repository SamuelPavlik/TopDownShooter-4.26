// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownShooter.h"

void AEnemyController::BeginPlay() {
	Super::BeginPlay();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AEnemyController::TrackPlayer, 0.1f, true);
}

void AEnemyController::TrackPlayer() {
	TArray<AActor*> FoundHeroes;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FRIENDLY, FoundHeroes);
	if (FoundHeroes.Num())
		MoveToActor(FoundHeroes[0]);
}
