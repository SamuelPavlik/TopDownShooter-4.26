// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

class UBoxComponent;

UCLASS()
class TOPDOWNSHOOTER_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "ActorSpawnerProperties")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = "ActorSpawnerProperties")
	UClass* ActorToSpawnClass;

	UPROPERTY(EditAnywhere, Category = "ActorSpawnerProperties")
	float HowOften = 1;

	UPROPERTY(VisibleAnywhere, Category = "ActorSpawnerProperties")
	int CurrOfActors = 0;

	UPROPERTY(EditAnywhere, Category = "ActorSpawnerProperties")
	int MaxOfActors = 5;

public:
	// Sets default values for this actor's properties
	AActorSpawner();

	virtual void SpawnActor();

	void Reset();

	void DecrActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
