// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class AEnemySpawner;
class ATopDownShooterGameModeBase;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* DamageVolume;

	UPROPERTY(EditAnywhere)
	float Damage = -20.0f;

	UPROPERTY(BlueprintReadWrite)
	AEnemySpawner* Spawner;

private:
	ABaseCharacter* HeroToDmg;

	ATopDownShooterGameModeBase* GameMode;

public:
	AEnemyCharacter();

	void SetSpawner(AEnemySpawner* Spawner);

	virtual void Kill() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyEnemyEffect();

private:
	void DestroyEnemy();

	UFUNCTION()
	void OnHeroBeginOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnHeroEndOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, UPrimitiveComponent* OtherComp, int32 Index);

	void DamageHero();
};
