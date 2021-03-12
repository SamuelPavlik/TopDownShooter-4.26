// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;

UCLASS()
class TOPDOWNSHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "EnemySpawnerProperties")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = "EnemySpawnerProperties")
	UClass* EnemyToSpawnClass;

	UPROPERTY(EditAnywhere, Category = "EnemySpawnerProperties")
	float HowOften = 1;

	UPROPERTY(VisibleAnywhere, Category = "EnemySpawnerProperties")
	int CurrOfEnemies = 0;

	UPROPERTY(EditAnywhere, Category = "EnemySpawnerProperties")
	int MaxOfEnemies = 5;

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void SpawnEnemy();

	void Reset();

	void DecrEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
