// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Collectable.generated.h"

class AHeroCharacter;
class USphereComponent;

UCLASS(Abstract, Blueprintable)
class TOPDOWNSHOOTER_API UCollectable : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionVolume;

public:	
	// Sets default values for this component's properties
	UCollectable();

protected:
	virtual void BeginPlay() override;

	virtual void Interact(AHeroCharacter*);

private:
	UFUNCTION()
	void OnHeroBeginOverlap(UPrimitiveComponent* ThisComp, AActor* Actor, UPrimitiveComponent* OtherComp, int32 Index, bool bFromSweep, const FHitResult& Hit);

};
