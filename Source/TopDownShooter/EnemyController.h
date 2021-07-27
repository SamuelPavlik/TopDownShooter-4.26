// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:
	class AEnemyCharacter* EnemyPawn;

public:
	UFUNCTION(BlueprintCallable)
	void DamageHero();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	void TrackPlayer();

	UFUNCTION()
	void OnHeroBeginOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg,
		UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnHeroEndOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg,
		UPrimitiveComponent* OtherComp, int32 Index);
};
