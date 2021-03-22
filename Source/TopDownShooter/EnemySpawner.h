// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorSpawner.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;

UCLASS()
class TOPDOWNSHOOTER_API AEnemySpawner : public AActorSpawner {
	GENERATED_BODY()

public:	
	virtual void SpawnActor() override;

	
};
