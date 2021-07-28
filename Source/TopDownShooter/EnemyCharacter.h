#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class AEnemySpawner;
class ATopDownShooterGameModeBase;
class UBoxComponent;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeath);

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float CurrentBlendWeight = 0.f;

	UPROPERTY(EditAnywhere)
	UBoxComponent* DamageVolume;

	ABaseCharacter* HeroToDmg;

	FOnEnemyDeath OnEnemyDeath;

protected:
	UPROPERTY(EditAnywhere)
	float Damage = -20.0f;

	UPROPERTY(BlueprintReadWrite)
	bool bHeroInRange;

private:
	ATopDownShooterGameModeBase* GameMode;

public:
	AEnemyCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void DamageHero();

	void SetSpawner(AEnemySpawner* Spawner);

	virtual void Kill() override;

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyEnemyEffect();

	UFUNCTION(BlueprintCallable)
	void DamageHeroLogic();

private:
	void DestroyEnemy();

	//---------------------------------
	//UFUNCTION()
	//void OnHeroBeginOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, 
	//	UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);

	//UFUNCTION()
	//void OnHeroEndOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, 
	//	UPrimitiveComponent* OtherComp, int32 Index);
	//---------------------------------

	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* ThisComp, AActor* ActorToDmg, 
		UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);
};
