// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MenuHeroController.generated.h"

class AMenuHeroCharacter;

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AMenuHeroController : public AAIController
{
	GENERATED_BODY()

private:
	AMenuHeroCharacter* MenuHero;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* ThisComp, AActor* Actor, UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* ThisComp, AActor* Actor, UPrimitiveComponent* OtherComp, int32 Index);

	void OnEnemyChange(UPrimitiveComponent* ViewRadius);
};
